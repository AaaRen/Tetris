#include"contact.h"

void menu()
{
	printf("*************ͨѶ¼*****************\n");
	printf("******1.���********2.ɾ��**********\n");
	printf("******3.����********4.�޸�**********\n");
	printf("******5.��ʾ********6.���**********\n");
	printf("******7.����********0.�˳�**********\n");
}
enum OP
{
	EXIT,
	ADD,
	DEL,
	FIND,
	ALTER,
	SHOW,
	CLAER,
	SORT
};

int main()
{
	int input = 1;
	Contact con;
	init(&con);
	do
	{
		menu();
		printf("��ѡ��");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			add_person(&con);
			break;
		case DEL:
			del_person(&con);
			break;
		case FIND:
			find_person(&con);
			break;
		case ALTER:
			alter_person(&con);
			break;
		case SHOW:
			show_person(&con);
			break;
		case CLAER:
			clear_person(&con);
			break;
		case SORT:
			sort_name(&con);
			break;
		case EXIT:
			save_data(&con);
			break;
		default:
			break;
		}
	} while (input);
	system("pause");
	return 0;
}