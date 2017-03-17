#include "contact.h"

void load_data(Pcon pcon) //���ļ��ж�ȡ
{
	PeoInfo peo;
	FILE *pfread = fopen("aaa","r");
	if (pfread == NULL)
	{
		perror("open for read");
		return;
	}
	while (fread(&peo,sizeof(PeoInfo),1,pfread))
	{
		check_capacity(pcon);
		pcon->peoinfo[pcon->size] = peo;
		pcon->size++;
	}
	fclose(pfread);
}
void save_data(Pcon pcon)//�������ݵ��ļ���
{
	int i = 0;
	FILE *pfwrite = fopen("aaa", "w");
	if (pfwrite == NULL)
	{
		perror("open for write");
		return;
	}
	for (i = 0; i< pcon->size; i++)
	{
		fwrite(&(pcon->peoinfo[i]), sizeof(PeoInfo), 1, pfwrite);
	}
	fclose(pfwrite);
}
void init(Pcon pcon) //��ʼ��
{
	pcon->peoinfo = (PeoInfo *)malloc(sizeof(PeoInfo)*INIT_NUM);
	if (pcon->peoinfo == NULL)
	{
		perror("��ʼ��");
		exit(EXIT_FAILURE);
	}
	memset(pcon->peoinfo, 0, INIT_NUM*sizeof(PeoInfo));
	pcon->capacity = INIT_NUM;
	pcon->size = 0;
	load_data(pcon);
}
void check_capacity(Pcon pcon) //����Ƿ���Ҫ����
{
	if (pcon->size == pcon->capacity)
	{
		int sz = pcon->capacity + INIT_NUM;
		PeoInfo* tmp = (PeoInfo *)realloc(pcon->peoinfo, sz);
		//��������ʧ��
		if (pcon->peoinfo == NULL)
		{
			perror("�ٿ���ʧ�ܣ�");
			return;
		}
		pcon->capacity += INIT_NUM;
		pcon->peoinfo = tmp;
	}
}
int find_name(Pcon pcon, const char *name)
{
	int i = 0;
	for (i = 0; i < pcon->size; i++)
	{
		if (strcmp(pcon->peoinfo[i].name, name) == 0)
			return i;
	}
	return -1;
}
void add_person(Pcon pcon)
{
	check_capacity(pcon);
	printf("������ϵ�˵�������");
	scanf("%s", pcon->peoinfo[pcon->size].name);
	printf("\n������ϵ�˵��Ա�");
	scanf("%s", pcon->peoinfo[pcon->size].sex);
	printf("\n������ϵ�˵����䣺");
	scanf("%d", &pcon->peoinfo[pcon->size].age);
	printf("\n������ϵ�˵ĵ绰��");
	scanf("%s", pcon->peoinfo[pcon->size].tele);
	printf("\n������ϵ�˵ĵ�ַ��");
	scanf("%s", pcon->peoinfo[pcon->size].addr);
	pcon->size++;
}

void del_person(Pcon pcon)
{
	char name[MAX_NAME];
	int index = 0;
	int start = 0;
	if (pcon->size == 0)
	{
		printf("��ϵ��Ϊ�գ�\n");
		return;
	}
	printf("������������");
	scanf("%s", name);
	index = find_name(pcon, name);
	if (index == -1)
	{
		printf("û�и���ϵ�ˣ�\n");
		return;
	}
	for (start = index; start < pcon->size - 1; start++)
	{
		pcon->peoinfo[start] = pcon->peoinfo[start + 1];
	}
	pcon->size--;
	printf("ɾ���ɹ� \n");
}
void find_person(Pcon pcon)
{
	char name[MAX_NAME];
	int index = 0;
	printf("��������ҵ�������");
	scanf("%s", name);
	index = find_name(pcon, name);
	if (index == -1)
	{
		printf("���ҵ��˲�����\n");
	}
	else
	{
		printf("������%s �Ա�%s ���䣺%d �绰��%s ��ַ��%s\n",
			pcon->peoinfo[index].name, pcon->peoinfo[index].sex, pcon->peoinfo[index].age,
			pcon->peoinfo[index].tele, pcon->peoinfo[index].addr);
	}
}
void alter_person(Pcon pcon)
{
	char name[MAX_NAME];
	int index = 0;
	printf("��������ĵ�������");
	scanf("%s", name);
	index = find_name(pcon, name);
	if (index == -1)
	{
		printf("���ĵ��˲�����\n");
	}
	else
	{
		printf("������ϵ�˵�������");
		scanf("%s", pcon->peoinfo[index].name);
		printf("\n������ϵ�˵��Ա�");
		scanf("%s", pcon->peoinfo[index].sex);
		printf("\n������ϵ�˵����䣺");
		scanf("%d", &pcon->peoinfo[index].age);
		printf("\n������ϵ�˵ĵ绰��");
		scanf("%s", pcon->peoinfo[index].tele);
		printf("\n������ϵ�˵ĵ�ַ��");
		scanf("%s", pcon->peoinfo[index].addr);
	}
}
void show_person(Pcon pcon)
{
	int i = 0;
	for (i = 0; i < pcon->size; i++)
	{
		printf("������%s �Ա�%s ���䣺%d �绰��%s ��ַ��%s\n",
			pcon->peoinfo[i].name, pcon->peoinfo[i].sex, pcon->peoinfo[i].age,
			pcon->peoinfo[i].tele, pcon->peoinfo[i].addr);
	}
}
void clear_person(Pcon pcon)
{
	pcon->size = 0;
}
void sort_name(Pcon pcon)
{
	int i = 0;
	int j = 0;
	PeoInfo tmp;
	for (i = 0; i < pcon->size - 1; i++)
	{
		for (j = i; j < pcon->size - 1; j++)
		{
			if (strcmp(pcon->peoinfo[j].name, pcon->peoinfo[j + 1].name)>0)
			{
				tmp = pcon->peoinfo[j];
				pcon->peoinfo[j] = pcon->peoinfo[j + 1];
				pcon->peoinfo[j + 1] = tmp;
			}
		}
	}
	printf("����ɹ���\n");
	show_person(pcon);
}