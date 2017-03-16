

#include"game.h"

void menu()
{
	printf("**********������ ������*************\n");
	printf("********** 1 ��ʼ��Ϸ  *************\n");
	printf("********** 0 �˳���Ϸ   ************\n");
	printf("************************************\n");
}
enum op
{
	EXIT,
	PLAY
};
void start_game(char board[][ROWS])
{
	char result = 0;
	init(board);
	print_board(board);
	do
	{
		p_game(board);
		result = check_win(board);
		if (result != 'Q')
			break;
		npc_game(board);
		result = check_win(board);
	} while (result == 'Q');
	if (result == 'X')
		printf("���Ӯ��\n");
	else if (result == 'O')
		printf("����Ӯ��\n");
	else if (result == 'P')
		printf("ƽ��\n");
}
int main()
{
	char board[LINE][ROWS];
	int input = 1;	
	do
	{
		menu();
		printf("������ѡ��");
		scanf("%d", &input);
		switch (input)
		{
		case PLAY:
			start_game(board);
			break;
		case EXIT:
			break;
		default:
			printf("�������!!!\n");
			break;
		}
	} while (input);

	system("pause");
	return 0;
}