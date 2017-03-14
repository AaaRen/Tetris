#include"FileCompress.h"


void FileCompress::Compress(const std::string& strFilePath)
{
	FILE *Fread = fopen(strFilePath.c_str(), "rb");
	if (NULL == Fread)
	{
		std::cout << strFilePath << " Not Found !" << std::endl;
		return;
	}
	CountFileInfo(Fread);

	FillCode();

	std::string CompressFileName;
	GetPrefixFileName(strFilePath, CompressFileName);
	CompressFileName += ".hgz";

	FILE *FWrite = fopen(CompressFileName.c_str(), "wb");
	if (NULL == FWrite)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}

	WriteHead(FWrite, strFilePath);
	CompressCore(Fread, FWrite);

	fclose(Fread);
	fclose(FWrite);

}
//��ѹ��
//1 ��֤ �Ƿ�Ϊ.hzp
//2 ��ȡ�ļ��ײ������¹�����������
//3 ��ȡѹ����Ϣ�����ù�������������д��
void FileCompress::UnCompress(const std::string& strFilePath)
{
	std::string strPost = strFilePath.substr(strFilePath.find_last_of('.'));
	if (strPost.compare(".hgz") != 0)
	{
		cout << "�޷���ѹ�����ļ�" << endl;
		return;
	}
	FILE* Fread = fopen(strFilePath.c_str(),"rb");
	if (NULL == Fread)
	{
		return;
	}
	std::string UnCompressFileName;
	GetPrefixFileName(strFilePath, UnCompressFileName);
	std::string postFixName;
	GetHead1(Fread, postFixName);
	//GetHead(Fread, postFixName);
	UnCompressFileName += postFixName;

	FILE* FWrite = fopen(UnCompressFileName.c_str(), "wb");
	if (NULL == FWrite)
	{
		return;
	}

	UnCompressCore(Fread,FWrite);

	fclose(FWrite);
	fclose(Fread);

}
void FileCompress::UnCompressCore(FILE * Fread,FILE * Fwrite) //
{
	HuffmanTree<FileInfo> ht(_fileinfo, sizeof(_fileinfo) / sizeof(_fileinfo[0]), FileInfo());
	HuffmanTreeNode<FileInfo>* pRoot = ht.GetRoot();
	HuffmanTreeNode<FileInfo>* pCur = pRoot;
	unsigned char ReadBuf[1024];
	unsigned char WriteBuf[1024];
	size_t WritePos = 0;
	if (pRoot == NULL)
		return;
	size_t FileLen = pRoot->_weight._count;//��¼һ���ж��ٸ��ļ���Ϣ
	while (true)
	{
		size_t ReadSize = fread(ReadBuf, 1, 1024, Fread);
		if (ReadSize == 0)
			break;
		for (size_t idx = 0; idx < ReadSize && FileLen != 0; ++idx) //���һ������ 
		{
			int BitPos = 8; //��¼һ���ֽ�
			while (BitPos >0) //��ȡһ���ֽ�
			{
				--BitPos;
				if (ReadBuf[idx] & (1 << BitPos))
					pCur = pCur->_pRight;
				else
					pCur = pCur->_pLeft;
				if (NULL == pCur->_pLeft && NULL == pCur->_pRight)
				{
					WriteBuf[WritePos++] = pCur->_weight._ch;
					pCur = pRoot;
					if (1024 == WritePos)
					{
						fwrite(WriteBuf, 1, 1024, Fwrite);
						WritePos = 0;
					}
					--FileLen;
				}
				//���ܴ����Ѿ���ȡ���ˣ�
				if (0 == FileLen && WritePos < 1024 && WritePos > 0)
				{
					fwrite(WriteBuf, 1, WritePos, Fwrite);
					break;
				}
			}
		}
	}
	if (FileLen != 0) //���ǵ����ַ�,����"aaa" û�й�����������
	{
		while (FileLen--)
		{
			WriteBuf[WritePos++] = pRoot->_weight._ch;
			if (1024 == WritePos)
			{
				fwrite(WriteBuf, 1, 1024, Fwrite);
				WritePos = 0;
			}
		}
		fwrite(WriteBuf, 1, WritePos, Fwrite);
	}
}
//ͳ����Ϣ
void FileCompress::CountFileInfo(FILE *fp)
{
	assert(fp);
	unsigned char ReadBuf[1024];
	while (true)
	{
		size_t ReadSize = fread(ReadBuf, 1, 1024, fp);
		if (ReadSize == 0)
			break;
		for (size_t idx = 0; idx < ReadSize; ++idx)
		{
			_fileinfo[ReadBuf[idx]]._count++;
		}
	}
}
//��������������������
void FileCompress::FillCode()
{
	FileInfo invalid;
	HuffmanTree<FileInfo> hf(_fileinfo, sizeof(_fileinfo) / sizeof(_fileinfo[0]), invalid);
	HuffmanTreeNode<FileInfo>* proot = hf.GetRoot();
	_GenerateHuffmanCode(proot);
}
//���������ȡ���룬������
void FileCompress::_GenerateHuffmanCode(HuffmanTreeNode<FileInfo>*& pRoot)
{
	if (pRoot)
	{
		_GenerateHuffmanCode(pRoot->_pLeft);
		_GenerateHuffmanCode(pRoot->_pRight);


		HuffmanTreeNode<FileInfo>* pCur = pRoot;
		HuffmanTreeNode<FileInfo>* pParent = pCur->_pParent;
		std::string strCode;
		if (NULL == pCur->_pLeft && NULL == pCur->_pRight)
		{
			while (pParent)
			{
				if (pParent->_pLeft == pCur)
					strCode += '0';
				if (pParent->_pRight == pCur)
					strCode += '1';

				pParent = pParent->_pParent;
				pCur = pCur->_pParent;
			}
			std::reverse(strCode.begin(), strCode.end());
			_fileinfo[pRoot->_weight._ch]._strCode = strCode;
		}
	}
}

//д��ͷ��
void FileCompress::WriteHead(FILE* Fwrite, const std::string& strFilePath)
{
	// ѹ���ļ�ͷ��ʽ:
	// ��չ��
	// ��������
	// ������ ...
	std::string strHead;
	GetPostfixFileName(strFilePath, strHead);
	strHead += '\n';

	size_t LineCount = 0;//���� ��������		
	std::string strCode; //��¼�ַ�������Ϣ
	unsigned char ItoaBuf[30];
	size_t idx = 0;
	while (idx < sizeof(_fileinfo) / sizeof(_fileinfo[0]))
	{
		if (_fileinfo[idx]._count)
		{
			strCode += _fileinfo[idx]._ch;
			strCode += ':';
			_itoa(_fileinfo[idx]._count, (char *)ItoaBuf, 10);
			//sprintf((char *)ItoaBuf, "%lld", _fileinfo[idx]._count);
			strCode += (char *)ItoaBuf;
			strCode += '\n';

			LineCount++;
		}
		idx++;
	}
	_itoa(LineCount, (char *)ItoaBuf, 10);
	//sprintf((char *)ItoaBuf, "%d", LineCount);
	strHead += (char *)ItoaBuf;
	strHead += '\n';

	strHead += strCode;

	fwrite(strHead.c_str(), 1, strHead.length(), Fwrite);
}

//����ͷ����Ϣ,���ַ��� unsigned char*
void FileCompress::GetHead(FILE *fp, std::string &FilePostfixName)
{
	assert(fp);
	unsigned char buf[1024];
	//��ȡ��׺��
	ReadLine(fp,buf);
	FilePostfixName += (char *)buf;

	//��ȡ����
	ReadLine(fp, buf);
	size_t lineCount = atoi((char *)buf);
	while (lineCount--)
	{
		ReadLine(fp, buf);
		_fileinfo[*buf]._count = atoi((char *)(buf + 2));
	}
}
//��ȡһ����Ϣ,���ַ��� unsigned char*
void FileCompress::ReadLine(FILE *fp, unsigned char *buf)
{
	assert(fp);
	size_t n = 0;
	int index = 0;
	while (fread(buf + index, 1, 1, fp) > 0)
	{
		if (index != 0 && buf[index] == '\n') // ���һ������index��=0 ������ֻ��һ��\n
			break;

		index++;
	}
	buf[index] = '\0';
}
std::string FileCompress::ReadLine1(FILE* fp)
{
	std::string strLine;
	if (feof(fp))
		return strLine;
	unsigned char c = getc(fp);
	while ('\n' != c || strLine.length() == 0) //���һ��������������\n:������ȡ��Ϣ
	{
		strLine += c;
		if (feof(fp))//���ļ��Ƿ��ǽ�β
			return strLine;
		c = getc(fp);
	}
	return strLine;
}
//����ͷ������string
void FileCompress::GetHead1(FILE* fp, std::string& strPostFix)
{
	strPostFix += ReadLine1(fp);
	int linCount = atoi(ReadLine1(fp).c_str());
	std::string strCode;
	unsigned char temp;
	while (linCount--)
	{
		strCode = ReadLine1(fp);
		temp = strCode[0];   //��ת�����޷��ŵ�char
		_fileinfo[temp]._count = atoi(strCode.substr(2).c_str());

	}
}
//��ȡ�ļ�����׺
void FileCompress::GetPostfixFileName(const std::string& strFilePath, std::string& PostfixFileName)
{
	PostfixFileName = strFilePath.substr(strFilePath.find_last_of('.'));
}
//��ȡ�ļ���
void FileCompress::GetPrefixFileName(const std::string& strFilePath, std::string& PrefixFileName)
{
	// test.txt
	// f:\\ab\\c\\test.txt
	size_t begin = strFilePath.find_last_of("/\\");
	if (begin == std::string::npos)
	{
		begin = 0;
	}
	size_t end = strFilePath.find_last_of('.');
	PrefixFileName += strFilePath.substr(begin, end - begin);
}

void FileCompress::CompressCore(FILE* Fread, FILE* Fwrite)
{
	fseek(Fread, 0, SEEK_SET); // �Ѷ��ļ�ָ��ָ��ʼ
	unsigned char value = 0;
	unsigned char ReadBuf[1024];
	unsigned char WriteBuf[1024];
	size_t BitPos = 0;
	size_t WritePos = 0;
	while (true)
	{
		size_t ReadSize = fread(ReadBuf, 1, 1024, Fread);
		if (ReadSize == 0)
			break;
		for (size_t readidx = 0; readidx < ReadSize; ++readidx)
		{
			std::string &strCode = _fileinfo[ReadBuf[readidx]]._strCode;
			//���ַ�ѹ������д���ļ�
			if (strCode == "")
				return;
			for (size_t idx = 0; idx < strCode.length(); ++idx)
			{
				value <<= 1;//����һλ�ŵ��ж�ǰ�棬��Ϊ����һλ�൱��д��0
				if (strCode[idx] == '1')
					value |= 1;

				if (8 == ++BitPos)
				{
					WriteBuf[WritePos++] = value;

					if (WritePos == 1024)
					{
						fwrite(WriteBuf, 1, 1024, Fwrite);
						WritePos = 0;
					}
					BitPos = 0;
					value = 0;
				}
			}
		}
	}

	// ���� BitPos С��8 
	if ((BitPos > 0 && BitPos < 8) || WritePos < 1024)
	{
		value <<= (8 - BitPos);
		WriteBuf[WritePos++] = value;
		fwrite(WriteBuf, 1, WritePos, Fwrite);
	}
}

