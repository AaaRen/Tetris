#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<fstream>
#include<string>
#include<stack>
using namespace std;
struct Seat // ����
{
	Seat(int x = 0, int y = 0)
	: _x(x)
	, _y(y)
	{}
	int _x;
	int _y;
};
//1����ͼ�����ݱ������ļ��У������Ǵ��ļ��ж�ȡ
//2�������Թ���ͼ�Ŀռ�ʹ�ö�̬���ٵĶ�ά����
//3���������н������ڵ�ͼ�ϱ��������߷�
class Maze
{
public:
	Maze(const string& filename)
	{
		string strBuff;
		string strData;
		fstream fin(filename);

		getline(fin,strBuff);//��ȡ��һ��

		strData = strBuff.substr(0, strBuff.find_first_of(','));//��ȡrow
		_row = atoi(strData.c_str()); 

		strData = strBuff.substr(strBuff.find_first_of(',')+1);//��ȡcol
		_col= atoi(strData.c_str());

		//��̬��������
		_map = new int*[_row];
		for (int i = 0; i < _row; ++i)
		{
			_map[i] = new int[_col];
		}

		// ��ȡ���ݷ��ڶ�̬������
		int RowIdx = 0, ColIdx = 0;
		while (!fin.eof())
		{
			getline(fin,strData);
			char* start = (char*)strData.c_str();
			while (*start)
			{
				if (*start >= '0' && *start <= '3')
					_map[RowIdx][ColIdx++] = *start - '0';
				start++;
			}
			RowIdx += 1;//����
			ColIdx = 0;
		}
		fin.close();
	}
	bool IsPass(const Seat& s)   // �жϵ�ǰ·���Ƿ���ͨ·
	{
		if (s._x < 0 || s._y < 0 || s._y >= _col|| s._x >= _row) //��ʾ�����յ�
			return true;
		if (_map[s._x][s._y] == 1)
			return true;
		else
			return false;
	}
	bool PassMaze(const Seat& Entry) // �ݹ����Թ�
	{
		//��ǰ�����ڶ�ά�������� �ݹ��������
		if (Entry._x < 0 || Entry._x >= _row ||
			Entry._y < 0 || Entry._y >= _col)
			return true;

		if (IsPass(Entry)) //�жϵ�ǰ�������Ƿ�ͨ
		{
			_map[Entry._x][Entry._y] = 2; //ͨ·�ó�2

			//��ǰ
			Seat front(Entry._x -1,Entry._y);
			if (PassMaze(front))
				return true;
			//����
			Seat left(Entry._x, Entry._y -1);
			if (PassMaze(left))
				return true;
			//����
			Seat right(Entry._x, Entry._y + 1);
			if (PassMaze(right))
				return true;

			_map[Entry._x][Entry._y] = 3; // ��Ǳ�ʾ�߲�ͨ
		}
			return false;
	}
	bool PazzMaze2(std::stack<Seat>&s, const Seat& Entry)// ��ջѭ��ʵ��
	// ͨ·����ջ��
	{
		
		if (IsPass(Entry))
		{
			s.push(Entry);
			while (!s.empty())
			{
				Seat Cur = s.top();
				//������������
				if (Cur._x < 0 || Cur._x >= _row ||
					Cur._y < 0 || Cur._y >= _col)
				{
					s.pop();
					return true;
				}
					
				_map[Cur._x][Cur._y] = 2;
				//ǰ
				Seat Front(Cur._x-1, Cur._y);
				if (IsPass(Front))
				{
					s.push(Front);
					continue;
				}
				//��
				Seat Left(Cur._x, Cur._y-1);
				if (IsPass(Left))
				{
					s.push(Left);
					continue;
				}
				//��
				Seat Right(Cur._x, Cur._y+1);
				if (IsPass(Right))
				{
					s.push(Right);
					continue;
				}
				_map[Entry._x][Entry._y] = 3;//��ʾ��ͨ·��Ȼ��pop
				s.pop();
			}
		}
			
	}
	void PrintMap()   // ��ӡ��ͼ
	{
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; j++)
			{
				cout << _map[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	~Maze()
	{
		for (int idx = 0; idx < _row; ++idx)
		{
			delete[] _map[idx];
		}
		delete[] _map;
	}

private:
	int **_map;
	int _row;
	int _col;
};

void Test()
{
	Maze maze("map.txt");
	maze.PrintMap();
	Seat seat(9,6);
	stack<Seat> s;
	maze.PassMaze(seat);
	maze.PrintMap();
	maze.PazzMaze2(s,seat);
	maze.PrintMap();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
