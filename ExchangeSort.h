#include<iostream>

//ð�����������Ƚϣ������(��С)ֵ�ŵ�ĩβ
void BubbleSort(int arr[],size_t size)
{
	for (size_t i = 0; i < size;++i) //�����������
	{
		for (size_t j = 0; j < size - i - 1; ++j) //�����Ƚϣ�ע������Խ��
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j],arr[j+1]);
			}
		}
	}
}
//ð�������Ż�������һ����־����
void BubbleSort_P(int arr[], size_t size)
{
	bool flag = true;
	for (size_t i = 0; i < size; ++i) //�����������
	{
		for (size_t j = 0; j < size - i - 1; ++j) //�����Ƚϣ�ע������Խ��
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				flag = false;
			}
		}
		if (flag)
			break;
	}
}


//��������  ���ȶ�����
// ���η�����һ��keyֵ������key�ķ���key֮��С�ڷ���key֮ǰ	    
//		 keyΪ�������һλ,begin��ǰ�Ҵ���key�ģ�end�Ӻ���С��key��Ȼ�󽻻�
//һ�ο�������
int Partition(int arr[], int begin, int end)//[]������
{
	int key = arr[begin]; //�������ߣ��ȴ����ұ߿�ʼ��
	while (begin < end)
	{
		while (begin < end && arr[end] > key)
			end--;
		if (begin < end)
		{
			arr[begin] = arr[end];
			begin++;
		}
		while (begin < end && arr[begin] < key)
			begin++;
		if (begin < end)
		{
			arr[end] = arr[begin];
			end--;
		}			
	}
	arr[begin] = key;
	return begin;
	
}
void QuickSort(int arr[],int left,int right)
{
	if (left < right)
	{
		int key = Partition(arr, left, right);
		QuickSort(arr, left, key - 1);
		QuickSort(arr, key + 1,right);
	}
}