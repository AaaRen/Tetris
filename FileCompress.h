#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Huffman.h"
using namespace std;
struct FileInfo
{
	FileInfo()
	: _count(0)
	{}
	/*FileInfo operator+(const FileInfo& FileInfoRight)//��ı�ԭ����ֵ
	{
	this->_count += FileInfoRight._count;
	return *this;
	}*/
	FileInfo operator+(const FileInfo& FileInfoRight)
	{
		FileInfo  temp(*this);
		temp._count += FileInfoRight._count;
		return temp;
	}
	bool operator <(const FileInfo& FileInfoRight)const
	{
		return _count < FileInfoRight._count;
	}
	bool operator >(const FileInfo& FileInfoRight)const
	{
		return _count > FileInfoRight._count;
	}
	bool operator != (const FileInfo& FileInfoRight)const
	{
		return _count != FileInfoRight._count;
	}
	std::string _strCode;//��ŵ�ǰ�ַ�ѹ����ı���
	unsigned char _ch;//��ǰ�ַ�
	size_t _count;//ͳ���ַ�����
};
class FileCompress
{
public:
	FileCompress() //���캯��
	{
		for (size_t idx = 0; idx < 256; ++idx)
		{
			_fileinfo[idx]._ch = idx;
			_fileinfo[idx]._count = 0;
		}
	}
	// һ ���ļ��ж�ȡ��ͳ���ַ�����
	// �� ��ȡ������Ϣ: ���������������ӹ��������ֻ�ȡ������Ϣ
	// �� �Ȱ�ѹ���������Ϣд��ͷ�����ļ���׺������ͬ���ַ�������һ���ַ�һ�У����ַ���_count��ֵ(Ϊ�˻�ԭ��������)
	// �� ���ļ�����ѹ����д��
	void Compress(const std::string& strFilePath);
	void UnCompress(const std::string& strFilePath);
private:
	//ͳ����Ϣ
	void CountFileInfo(FILE *fp);
	//��������������������
	void FillCode();
	//���������ȡ���룬������
	void _GenerateHuffmanCode(HuffmanTreeNode<FileInfo>*& pRoot);

	//д��ͷ��
	void WriteHead(FILE* Fwrite, const std::string& strFilePath);
	//����ͷ�������ַ���char*
	void GetHead(FILE *fp, std::string &FilePostfixName);
	//��ȡһ����Ϣ,���ַ���char*
	void ReadLine(FILE *fp, unsigned char *buf);
	//��ȡһ����Ϣ,��string
	std::string ReadLine1(FILE* fp);
	//����ͷ������string
	void GetHead1(FILE* fp, std::string& strPostFix);
	//��ȡ�ļ�����׺
	void GetPostfixFileName(const std::string& strFilePath, std::string& PostfixFileName);
	//��ȡ�ļ�����ǰ׺
	void GetPrefixFileName(const std::string& strFilePath, std::string& PrefixFileName);

	//�ļ����ݽ���ѹ��д��
	void CompressCore(FILE* Fread, FILE* Fwrite);
	//���ļ����ݽ�ѹ
	void UnCompressCore(FILE * Fread, FILE * FWrite);
private:
	FileInfo _fileinfo[256];
};