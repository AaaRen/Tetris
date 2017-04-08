#include"Head.h"


//������Ϸ����
void DrawGameWindow()
{
	//�Ȼ���Χǽ
	setcolor(RED); 
	setlinestyle(PS_SOLID,NULL,0);
	setfillcolor(BLUE);
	//��������Χǽ
	for (int x = WALL_SQUARE_WIDTH; x <= GAME_WALL_WIDTH; x += WALL_SQUARE_WIDTH)
	{
		fillrectangle(x - WALL_SQUARE_WIDTH, 0, x, WALL_SQUARE_WIDTH); //��
		fillrectangle(x - WALL_SQUARE_WIDTH, GAME_WALL_HTGH - WALL_SQUARE_WIDTH, x, GAME_WALL_HTGH);//��
	}
	//��������Χǽ
	for (int y = WALL_SQUARE_WIDTH; y <= GAME_WALL_HTGH; y += WALL_SQUARE_WIDTH)
	{
		fillrectangle(0, y, WALL_SQUARE_WIDTH, y + WALL_SQUARE_WIDTH);//��
		fillrectangle(GAME_WALL_WIDTH - WALL_SQUARE_WIDTH, y, GAME_WALL_WIDTH, y + WALL_SQUARE_WIDTH);//��
	}

	//�����ұ�ͳ�Ʒ�������ض���

	//�����ָ���
	setcolor(WHITE);
	setlinestyle(PS_DASH,2);
	line(GAME_WALL_WIDTH + 20, 0, GAME_WALL_WIDTH + 20, GAME_WALL_HTGH);

	//��������
	LOGFONT font;
	gettextstyle(&font);
	settextstyle(18, 0, _T("����"));
	font.lfQuality = ANTIALIASED_QUALITY;//�������Ч��Ϊ����� 
	//1��ʾԤ����״
	outtextxy(GAME_WALL_WIDTH + 80, 30, _T("Ԥ��"));

	outtextxy(GAME_WALL_WIDTH + 80, 170, _T("����"));
	
	outtextxy(GAME_WALL_WIDTH + 65, 250, _T("����˵��"));
	outtextxy(GAME_WALL_WIDTH + 40, 290, _T("w a s d���Ʒ���"));
	outtextxy(GAME_WALL_WIDTH + 40, 335, _T("�ո� ��ͣ"));
	
	//��ʾ����
	setcolor(RED);
	outtextxy(GAME_WALL_WIDTH + 90, 200, '0');
}

//����Ϸ����ʾ���ΪrockIdx�ķ���
void DisplayRock(int rockIdx,  RockLocation_t*  LocatePtr, bool displayed)
{
	int color;//�������ɫ
	int boardFalg = 0;
	int xRock = 0;
	int yRock = 0;
	unsigned short rockCode = RockArray[rockIdx].rockShapeBits;
	//���displayedΪtrue�Ļ������������ɫ����Ϊwhite��game_board��Ӧ��λ������Ϊ1��
	//���displayedΪfalse�Ļ������������ɫ����Ϊblack��game_board��Ӧ��λ������Ϊ0��
	displayed ? (color = WHITE, boardFalg = 1) : (color = BLACK, boardFalg = 0);
	
	setcolor(color);
	setlinestyle(PS_SOLID);//����Ϊʵ�ߣ�
	xRock = LocatePtr->left;
	yRock = LocatePtr->top;

	int count = 0;//ÿ4�����У���¼����ƫ����
	unsigned short mask = 1;
	for (int i = 1; i <= 16; ++i)
	{
		
		mask = 1 << (16 - i);
		if ((rockCode & mask) != 0) //�����Ϊ0�Ļ����ͻ���С����
		{
			//ʵ�ߵ�����Ϊ2
			rectangle(xRock , yRock, xRock + ROCK_SQUARE_WIDTH, yRock + ROCK_SQUARE_WIDTH);
		}
		if (i % 4 == 0) //����
		{
			yRock = yRock + ROCK_SQUARE_WIDTH;	
			xRock = xRock = LocatePtr->left;
		}
		else
		{
			xRock += ROCK_SQUARE_WIDTH;
		}
	}
}

