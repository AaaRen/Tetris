

// Ԥ�����
#ifndef __GAME_H__    // ��ֹ�ظ�game.h���ظ�����
#define __GAME_H__
#define  LINE 3   // �еĴ�С
#define  ROWS 3   // �еĴ�С
#define _CRT_SECURE_NO_WARNINGS 1 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void init(char board[][ROWS]);

void print_board(char board[][ROWS]);

void p_game(char board[][ROWS]);

void npc_game(char board[][ROWS]);

char check_win(char board[][ROWS]);

int check_full(char board[][ROWS]);


#endif