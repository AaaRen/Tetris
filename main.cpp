#include"Head.h"
#include"Draw.h"
#include"Init.h"
#include"game.h"

int main()
{
	initgraph(WINDOW_WIDTH,WINDOW_HIGH);

	DrawGameWindow();
	//ʹ�� API �����޸Ĵ�������  
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, _T("����˹����"));
	InitGame();
	PlayGame();
	getchar();
	closegraph();
	system("pause");
	return	0;
}