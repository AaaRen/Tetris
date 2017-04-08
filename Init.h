#include"Head.h"

static void ShapeStrToBit(unsigned char *rockShapeStr, unsigned short& rockShapeBit);
static void ReadRcok();
void InitGame()
{
	//��ȫ����Ϸ��Ϸ���ʼ�����߽��ʼ��Ϊ1
	for (int i = 0; i < xROCK_SQUARE_NUM + 2; i++)
	{
		game_board[0][i] = 1;  //�ϱ߽�
		game_board[yROCK_SQUARE_NUM + 1][i] = 1; //�±߽�
	}
	for (int i = 0; i < yROCK_SQUARE_NUM + 2; i++)
	{
		game_board[i][0] = 1 ; //��߽�
		game_board[i][xROCK_SQUARE_NUM + 1] = 1; //�ұ߽�
	}
	//��ȡ����˹���� 
	ReadRcok();

}

//���ļ��ж�ȡ�������״�洢��rockArray��
void ReadRcok()
{
	FILE* fp = fopen("RockShape.ini","r");
	if (NULL == fp)
	{
		printf("���ļ�ʧ��\n");
		return;
	}
	unsigned char readBuf[1024]; //fp��ȡ���ַ���readbuf��
	unsigned short rockShapeBit = 0;//��ŷ�����״��ռ16����λ
	unsigned char rockShapeStr[16];//��ŷ����ַ���
	int ShapeStrIdx = 0;
	int rockNum = 0;//ͳ�Ʒ���ĸ����Լ���ŷ�������RockArray���±�
	int rocknext = 0;//������������һ����״
	int rockShapeStart = 0;//ͬһ���͵���״
	while (true)
	{
		size_t readSize = fread(readBuf, 1, 1024, fp);
		if (readSize == 0)
			break;
		//����readbuf
		for (size_t idx = 0; idx < readSize; ++idx)
		{
			//���ַ���ŵ�rockShapeStr��
			while (ShapeStrIdx < 16 && idx < readSize)
			{
				if (readBuf[idx] == '@' || readBuf[idx] == '#')
				{
					rockShapeStr[ShapeStrIdx] = (unsigned char)readBuf[idx];
					++ShapeStrIdx;
				}
				++idx; //����idx == readSize�� 
				if (readBuf[idx] == '*')//�޸���һ�η����nextֵ
				{
					idx += 5;
					RockArray[--rockNum].nextRockIndex = rockShapeStart;
					rockNum++;
					rockShapeStart = rockNum;
					rocknext = rockShapeStart ;
				}
			}
			//����û������
			if (ShapeStrIdx < 16)
			{
				break;
			}
			else //����shapestr
			{
				ShapeStrIdx = 0;//��0
				//��rockShapeStr תΪrockShapeBit
				ShapeStrToBit(rockShapeStr, rockShapeBit);
				rocknext++;
				RockArray[rockNum].rockShapeBits = rockShapeBit;
				RockArray[rockNum].nextRockIndex = rocknext;
				rockNum++;
			}
		}
	}
	fclose(fp);
}
//�����ļ��ж�ȡ���ַ���(����Ĭ��Ϊ16)ת���� unsigned short
void ShapeStrToBit(unsigned char *rockShapeStr, unsigned short& rockShapeBit)
{
	rockShapeBit = 0;
	for (size_t idx = 0; idx < 16; ++idx)
	{
		if (rockShapeStr[idx] == '@') //1
		{
			rockShapeBit |= (1 << (16 - idx - 1));
		}
		// #Ϊ0 ����Ҫ����
	}
}