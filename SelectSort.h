#include<iostream>

//ֱ��ѡ�������ҵ����ֵ����Сֵ�� �ŵ����һ��
//���ȶ���
void SelectionSort(int arr[],size_t size)
{
	for (size_t idx = 0; idx < size -1; ++idx) //�������� ,��һ�����������һ�� ��һ��Ԫ��
	{
		int maxpos = 0;
		int find = arr[maxpos];
		for (size_t i = 1; i < size - idx; ++i) //�����ֵ����Сֵ
		{			
			if (arr[i] > find)
			{
				find = arr[i];
				maxpos = i;
			}
		}
		if (maxpos != (size - idx - 1)) //�ж��ǲ���λ������ �Ͳ��ý���
			std::swap(arr[maxpos],arr[size - idx -1]);
	}
}


//�ҵ���С�����򣩻���󣨽��� �ŵ���ʼλ��
void SelectionSort2(int arr[],size_t size) //����,����Сֵ�ŵ�ǰ��
{
	for (size_t i = 0; i < size - 1; ++i) //��һ������
	{
		int pos = i; //���������Сֵ
		for (size_t j = i + 1; j < size; ++j)
		{
			if (arr[pos] > arr[j])
			{
				pos = j;
			}
		}
		if (i != pos)
			std::swap(arr[i],arr[pos]);
	}
}
// �Ż��汾��ͬʱ�ң��ҵ���Сֵ�����ֵ���ŵ���ʼ��ĩβ
void SelectionSort_P(int arr[],size_t size)
{
	int left = 0;
	int right = size - 1;
	int max = left;
	int min = right;
	while (left < right)
	{
		max = left;
		min = right;
		for (int i = left; i <= right;++ i)
		{
			if (arr[max] < arr[i])
				max = i;
			if (arr[min] > arr[i])
				min = i;
		}
//���������������1 ���ֵ-> left  && ���ֵ right ,ע�⽻��������
//			      2 ���ֵ-> left || ��Сֵ right,ע�⽻����λ�ÿ��ܸı���
// ����������������Ȱ���Сֵ����������ߣ��������������ֵ�Ļ����Ͱ���Сֵ��ֵ�����ֵ(��Ϊ��Сֵ��left������)
//					
		std::swap(arr[left], arr[min]);
		if (left == max)
			max = min;
		std::swap(arr[max], arr[right]);
		left++;
		right--;
	}
}

//������: ����-> ��� ����->С��
// ���� 1������
//		2�ѶѶ� �����һλ����λ�ã�������
void HeapAdjust(int arr[], int root, size_t size) //�Ӹ��ڵ����µ���
{
	size_t parent = root;
	size_t child = 2 * parent + 1; //Ĭ�Ϻ�����СֵΪ����,�Һ��ӿ��ܲ�����
	while (child < size)//���ڵ�ı䣬�������������������������
	{
		//�����ĺ���
		if (child + 1 < size && arr[child] < arr[child + 1])
		{
			child = child + 1;
		}

		if (arr[parent] < arr[child])
		{
			std::swap(arr[parent], arr[child]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}
void HeapSort(int arr[],size_t size) //����
{
	//1�����ѣ������һ����Ҷ�ӽڵ㿪ʼ����
	int idx = (size - 2) >> 1;
	while (idx >= 0)
	{
		HeapAdjust(arr,idx,size);
		idx--;
	}
	// �Ѷ������һ������
	int last = size;
	while (last > 1) //���ʣ��һ��Ԫ�أ����ý���
	{
		std::swap(arr[0], arr[last -1]);
		last--;
		HeapAdjust(arr,0,last);
	}
}