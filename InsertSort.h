#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
using namespace std;
//ֱ�Ӳ�����������
//1���浱ǰԪ�� 2�Ƚ�Ԫ�أ��ҵ������λ�ã�����Ԫ�� 3����Ԫ�� 
void InsertSort(int arr[],size_t size)
{
	for (size_t idx = 1; idx < size; ++idx)
	{
		int temp = arr[idx];
		size_t pos = idx - 1;
		while (pos >=0 && arr[pos] > temp)
		{
			//����,�Ӻ���ǰ����
			arr[pos + 1] = arr[pos];
			--pos;
		}
		arr[pos + 1] = temp; 
	}
}
//�ö��ֲ����Ż��������
//�ڲ���Ԫ��ʱ �ö��ֲ������Ż�[]
void InsertSort_P(int arr[],size_t size)
{
	for (size_t idx = 1; idx < size; ++idx)
	{
		int temp = arr[idx];		
		int left = 0;
		int right = idx -1;
		int mid = 0;
		//���Ҳ����λ��
		while (left <= right)
		{
			mid = left + ((right - left) >> 1);
			if (temp < arr[mid]) //��ȵĻ������������
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;			
			}
		}
		//����ѭ����leftΪ�����λ��
		size_t pos = left;
		for (size_t index = idx -1; index >= pos ; --index)
		{
			arr[index + 1] = arr[index];
			if (index == 0)
				break;
		}
		arr[pos] = temp;
	}
}

//ϣ������
void ShellSort(int arr[],size_t size)
{
	int gsp = size;
	while (gsp > 1)
	{
		gsp = gsp / 3 + 1;
		for (size_t idx = gsp; idx < size; ++idx)
		{
			int temp = arr[idx];
			int pos = idx - gsp;
			while (pos >= 0 && arr[pos] > temp)
			{
				//����,�Ӻ���ǰ����
				arr[pos + gsp] = arr[pos];
				pos = pos - gsp;
			}
			arr[pos + gsp] = temp;
		}
		
	}
}
