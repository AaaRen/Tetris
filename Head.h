#ifndef _HEAD_H_
#define _HEAD_H_

#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS 1

//�������صĲ���
#define WALL_SQUARE_WIDTH 10 //Χǽ����Ŀ��
#define xWALL_SQUARE_NUM 30 //x�᷽��ķ������Ŀ
#define yWALL_SQUARE_WIDTH 46 //y�᷽��ķ������Ŀ
#define GAME_WALL_WIDTH  (WALL_SQUARE_WIDTH*xWALL_SQUARE_NUM) //��Ϸ����Ŀ�� 300	
#define GAME_WALL_HTGH (WALL_SQUARE_WIDTH*yWALL_SQUARE_WIDTH) //��Ϸ����ĸ߶� 460

#define WINDOW_WIDTH 480 // ��Ϸ�ܴ��ڿ�� 480 
#define WINDOW_HIGH 460  // ��Ϸ�ܴ��ڸ߶� 460

//�������˹�������ز���
#define ROCK_SQUARE_WIDTH (2*WALL_SQUARE_WIDTH) //����˹����Ĵ�С��Χǽ������ 20
#define xROCK_SQUARE_NUM  ((GAME_WALL_WIDTH -20)/ROCK_SQUARE_WIDTH) // ��Ϸ��x��ŵķ�����Ŀ��14 
#define yROCK_SQUARE_NUM  ((GAME_WALL_HTGH -20)/ROCK_SQUARE_WIDTH)  // ��Ϸ��y��ŵķ�����Ŀ��22


//�����ƶ��������ز���
#define DIRECT_UP    3  
#define DIRECT_DOWN  2      
#define DIRECT_LEFT  -1  
#define DIRECT_RIGHT 1 


/*���ݽṹ-���Ա�(�ṹ������)*/
typedef struct ROCK
{
	//������ʾ�������״(ÿһ���ֽ���8λ����ÿ4λ��ʾ�����е�һ��)  
	unsigned short rockShapeBits;
	int          nextRockIndex;  //��һ�����飬�������е��±�  
} RockType;

//������ͼ�δ����е�λ��(����λ4*4�������Ͻ�����)  
typedef struct LOCATE
{
	int left;
	int top;
} RockLocation_t;

//ȫ�ֱ���-��Ϸ���״̬����(����ʾ��ǰ������Щλ���з���)  
//0��ʾû�У�1��ʾ��(��������к����У��γ�һ��Χǽ�������жϷ����Ƿ��ܹ��ƶ�)  
int game_board[yROCK_SQUARE_NUM + 2][xROCK_SQUARE_NUM + 2] = { 0 };
int game_socres = 0; //ȫ�ַ���

// �Ѷ���˹�����19����ŵ�������
int rockTypeNum = 19;
RockType RockArray[19] = { (0, 0) };

//Ԥ�����ķ����λ��
RockLocation_t preRockLocation = {GAME_WALL_WIDTH+70,70};
//ÿ�����ɳ�ʼ�������λ��
RockLocation_t initRockLocation = { (WALL_SQUARE_WIDTH + 100), WALL_SQUARE_WIDTH };
//������ʾ��λ��


//�����ļ��еĺ���
// ���������Լ���������Draw.h��
void DrawGameWindow();
void DisplayRock(int rockIdx, RockLocation_t*  LocatePtr, bool displayed);
//��ʼ��InitԴ�ļ�
void InitGame();

//game.h
void PlayGame();
bool IsGameOver();


#endif