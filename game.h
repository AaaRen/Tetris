#include"Head.h"
#define _CRT_SECURE_NO_WARNINGS 1
bool MoveAble(int rockIndex, RockLocation_t* currentLocatePtr, int f_direction);
void SetGameBoardFlag(int rockIdx, RockLocation_t* curRockLocation);
void UserHitKeyBoard(char userHit, int* RockIndex, RockLocation_t* curRockLocation);
void FullLine();
void UpdateSocres(int scores);
void DelCurLine(int rowIdx);
bool IsGameOver();


void PlayGame()
{
	char userHit = 0;//�û��û�����
	int curRockIndex = 0;//��ǰ�����rockArray�±�
	int nextRockIndex = 0;//�´�
	RockLocation_t curRockLocation;
	curRockLocation.left = initRockLocation.left;
	curRockLocation.top = initRockLocation.top;
	DWORD oldtime = 0;
	srand((unsigned int)time(NULL));
	curRockIndex = rand() % rockTypeNum;
	nextRockIndex = rand() % rockTypeNum;
	//����Ԥ������ʼ������
	//�ڳ�ʼλ�ú�Ԥ������ʾ������״
	DisplayRock(curRockIndex, &initRockLocation, 1);
	DisplayRock(nextRockIndex, &preRockLocation, 1);
	bool moveAbled = false;
	while (true)
	{
		//�жϵ�ǰ�����Ƿ����(�ж��ܷ�������)��������,�ж��Ƿ�����,���ж��Ƿ������Ϸ�� �ı�game_board ,�����´γ�ʼ���ķ��飬�Լ������µ�Ԥ������
		//
		moveAbled = MoveAble(curRockIndex, &curRockLocation, DIRECT_DOWN);
		if (!moveAbled) //�ж��Ƿ���أ��������Ʊ�ʾ���
		{
			//�޸�game_board��ֵ
			SetGameBoardFlag(curRockIndex, &curRockLocation);
			FullLine(); 
			if (IsGameOver())
			{
				MessageBox(NULL, _T("��Ϸ����"), _T("GAME OVER"), MB_OK);
				exit(0);
			}		
			//Ϊ�´�����ģ�鿪ʼ׼��
			DisplayRock(nextRockIndex, &preRockLocation, false);//�����ɵķ���
			curRockIndex = nextRockIndex;
			nextRockIndex = rand() % rockTypeNum; //�����µ�Ԥ������
			DisplayRock(curRockIndex, &initRockLocation, 1);
			DisplayRock(nextRockIndex, &preRockLocation, 1);
			FlushBatchDraw();
			//�޸�curRockLocation��ֵ
			curRockLocation.left = initRockLocation.left;
			curRockLocation.top = initRockLocation.top; 
		}

		if (kbhit()) //����û������� �ʹ�����
		{
			userHit = getch();
			UserHitKeyBoard(userHit, &curRockIndex, &curRockLocation);
		}

	    //û�� ���Զ�����һ����λ :������else����Ϊ���ܰ���������������
		DWORD newtime = GetTickCount();
		if (newtime - oldtime >= (unsigned int)(300) && moveAbled == TRUE)
		{
			oldtime = newtime;
			DisplayRock(curRockIndex, &curRockLocation, false);
			curRockLocation.top += ROCK_SQUARE_WIDTH; //����һ��  
		}
		//AutomaticDownMove(curRockIndex, &curRockLocation);
		//�����·���
		DisplayRock(curRockIndex, &curRockLocation, 1);
		FlushBatchDraw();
		Sleep(20);
	}
}



void UserHitKeyBoard(char userHit, int* RockIndex, RockLocation_t* curRockLocation)
{
	switch (userHit)
	{
	case 'W':
	case 'w'://��
		if (MoveAble(RockArray[*RockIndex].nextRockIndex, curRockLocation, DIRECT_UP))
		{
			DisplayRock(*RockIndex, curRockLocation, false);
			*RockIndex = RockArray[*RockIndex].nextRockIndex;
		}
		break;
	case 'S':
	case 's'://��
		if (MoveAble(*RockIndex, curRockLocation, DIRECT_DOWN))
		{
			DisplayRock(*RockIndex, curRockLocation, false);
			curRockLocation->top += 2 * (ROCK_SQUARE_WIDTH);
			if (!MoveAble(*RockIndex, curRockLocation, DIRECT_DOWN))
			{
				curRockLocation->top += ROCK_SQUARE_WIDTH;
			}
		}
		break;
	case 'A':
	case 'a': //��
		if (MoveAble(*RockIndex, curRockLocation, DIRECT_LEFT))
		{
			DisplayRock(*RockIndex, curRockLocation, false);
			curRockLocation->left -= ROCK_SQUARE_WIDTH;
		}
		break;
	case 'D':
	case 'd': //��
		if (MoveAble(*RockIndex, curRockLocation, DIRECT_RIGHT))
		{
			DisplayRock(*RockIndex, curRockLocation, FALSE);
			curRockLocation->left += ROCK_SQUARE_WIDTH;
		}
		break;
	case ' ': //��ͣ
		while (1)
		{
			userHit = getch();
			if (userHit == ' ')
				break;
		}
		break;
	default:
		break;
	}
}

//�ж��Ƿ����У�����������Ȼ�����÷�
void FullLine()
{
	bool linefull = true;
	int idx = yROCK_SQUARE_NUM;//�����һ�����ϲ���
	int count = 0;
	while (count != xROCK_SQUARE_NUM ) //��������
	{
		linefull = true;
		count = 0;
		for (int i = 1; i <= xROCK_SQUARE_NUM; ++i)
		{
			if (game_board[idx][i] == 0)
			{
				linefull = false;
				count++;
			}
		}
		if (linefull) //���У�������ǰ�У����·���
		{
			DelCurLine(idx);
			game_socres += 3;
			UpdateSocres(game_socres);
			idx++;//��Ϊ����Ҫ��1
		}
		idx--;
	}
}
void UpdateSocres(int scores)
{
	setcolor(RED);
	TCHAR s[10];
	_stprintf(s, _T("%d"), scores);
	outtextxy(GAME_WALL_WIDTH + 90, 200, s);
}
//������ǰ��
void DelCurLine(int rowIdx)
{
	//������ǰ��
	setcolor(BLACK);
	for (int i = 1; i < xROCK_SQUARE_NUM; ++i)
	{
		rectangle(WALL_SQUARE_WIDTH + (i - 1)*ROCK_SQUARE_WIDTH, (rowIdx - 1)*ROCK_SQUARE_WIDTH + WALL_SQUARE_WIDTH,
				  WALL_SQUARE_WIDTH + i*ROCK_SQUARE_WIDTH, rowIdx*ROCK_SQUARE_WIDTH + WALL_SQUARE_WIDTH);
	}
	//�������������
	int cnt = 0;
	while (cnt != xROCK_SQUARE_NUM) //ֱ�������ǿ��е�Ϊֹ  
	{
		cnt = 0;
		for (int i = 1; i <= xROCK_SQUARE_NUM; i++)
		{
			game_board[rowIdx][i] = game_board[rowIdx - 1][i];

			//���������һ��  
			setcolor(BLACK);
			rectangle(WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*i - ROCK_SQUARE_WIDTH ,
				WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*(rowIdx - 1) - ROCK_SQUARE_WIDTH ,
				WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*i,
				WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*(rowIdx - 1));

			//��ʾ�����һ��  
			if (game_board[rowIdx][i] == 1)
			{
				setcolor(WHITE);
				rectangle(WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*i - ROCK_SQUARE_WIDTH ,
					WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*rowIdx - ROCK_SQUARE_WIDTH ,
					WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*i,
					WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*rowIdx);
			}

			if (game_board[rowIdx][i] == 0)
				cnt++;            //ͳ��һ���ǲ��� ���ǿո�  
		}//for  
		rowIdx--;
	}
}

//�Ƿ�����ƶ�����
bool MoveAble(int rockIndex, RockLocation_t* currentLocatePtr, int f_direction)
{
	int mask;
	int rockX;
	int rockY;

	rockX = currentLocatePtr->left;
	rockY = currentLocatePtr->top;

	mask = (unsigned short)1 << 15;
	for (int i = 1; i <= 16; i++)
	{
		//����������Ϊ1�� ��Ϊ�����ϵĵ�  
		if ((RockArray[rockIndex].rockShapeBits & mask) != 0)
		{
			//�ж��ܷ��ƶ�(��ɨ�輴���ƶ���λ�� �Ƿ������õ�Χǽ���ص�)  
			//��������(����������)  
			if (f_direction == DIRECT_UP)
			{
				//��Ϊ������´��������һ���������״��������ֱ���жϴ˷����λ���Ƿ��Ѿ���ռ 
				//�ж���һ������
				if (game_board[(rockY - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1]
					[(rockX - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1] == 1)
					return false;
			}
			//��������·����ƶ�  
			else if (f_direction == DIRECT_DOWN)
			{
				if (game_board[(rockY - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 2]
					[(rockX - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1] == 1)
					return false;
			}
			else //��������ҷ����ƶ�  
			{   //f_direction��DIRECT_LEFTΪ-1��DIRECT_RIGHTΪ1����ֱ�Ӽ�f_direction�����жϡ�  
				if (game_board[(rockY - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1]
					[(rockX - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1 + f_direction] == 1)
					return false;
			}
		}

		//ÿ4�� ���� ת����һ�м���  
		i % 4 == 0 ? (rockY += ROCK_SQUARE_WIDTH, rockX = currentLocatePtr->left)
			: rockX += ROCK_SQUARE_WIDTH;

		mask >>= 1;
	}

	return true;

}
//����Ϸgame_board���ñ�Ǳ�ʾ�Ѿ�ռ��
void SetGameBoardFlag(int rockIdx, RockLocation_t* curRockLocation)
{
	int mask;
	int rockX;
	int rockY;

	rockX = curRockLocation->left;
	rockY = curRockLocation->top;

	mask = (unsigned int)1 << 15;
	for (int i = 1; i <= 16; i++)
	{
		//����������Ϊ1�� ��Ϊ�����ϵĵ�  
		if ((RockArray[rockIdx].rockShapeBits & mask) != 0)
		{
			game_board[(rockY - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1]
				[(rockX - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1] = 1;
		}

		//ÿ4�� ���� ת����һ�м�����  
		i % 4 == 0 ? (rockY += ROCK_SQUARE_WIDTH, rockX = curRockLocation->left)
			: rockX += ROCK_SQUARE_WIDTH;

		mask >>= 1;
	}
}
//�ж���Ϸ�Ƿ����
bool IsGameOver()
{
	bool topLineHaveRock = false;//�����Ƿ��з���
	bool bottomLineHaveRock = false;

	for (int i = 1; i < xROCK_SQUARE_NUM; ++i)
	{
		if (game_board[1][i] == 1)
			topLineHaveRock = true;
		if (game_board[yROCK_SQUARE_NUM][i] == 1)
			bottomLineHaveRock = true;
	}
	if (bottomLineHaveRock && topLineHaveRock)
		return true;
	else 
		return false;
}