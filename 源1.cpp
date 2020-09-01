#include<iostream>
using namespace std;

const  int MAX = 100;

struct coins {
	int value;//��ֵ
	int weight;//����
}coin[MAX];


int n = 4;
int y = 12;
int m[MAX][MAX];//����¼����¼����������
int s[MAX][MAX];//��Ǻ�������¼���Ӳ����ֵ


void Data() {
	cout << "��Ʒ������4" << endl;
	cout << "����Ʒ�ļ�ֵ��1 4 6 8" << endl;
	coin[1].value = 1;
	coin[2].value = 4;
	coin[3].value = 6;
	coin[4].value = 8;
	cout << "����Ʒ��������1 2 4 6" << endl;
	coin[1].weight = 1;
	coin[2].weight = 2;
	coin[3].weight = 4;
	coin[4].weight = 6;
	cout << "�ܼ�ֵy��12" << endl;
	cout << "***************************************************" << endl;
}

void Coin()
{
	int i, j;
	for (i = 1; i <= y; i++)  	//i=1ʱ
	{
		m[1][i] = i * coin[1].weight;
		s[1][i] = 1;
	}
	for (i = 2; i <= n; i++)
	{
		for (j = 1; j <= y; j++)
		{
			if (coin[i].value <= j)
			{
				if (m[i - 1][j] > (m[i - 1][j - coin[i].value] + coin[i].weight))
				{
					m[i][j] = m[i - 1][j - coin[i].value] + coin[i].weight;
					s[i][j] = i;
				}
				else
				{
					m[i][j] = m[i - 1][j];
					s[i][j] = s[i-1][j];
				}
			}
			else
			{
				m[i][j] = m[i - 1][j];
				s[i][j] = s[i - 1][j];
			}				
		}
	}
}


void Out()
{
	int x[MAX];//��¼��Ӳ��ʹ�ô���
	int val = y;
	int j = n;
	cout << "������������" << m[j][val] << endl;
	for (int i = 1; i <= n; i++) 
	{
		x[i] = 0;
	}

	while (val!= 0)
	{
		j = s[j][val];
		x[j] = 1;
		val = val - coin[j].value;
		while (s[j][val] == j)
		{
			val = val - coin[j].value;
			x[j] += 1;
		}
	}
	cout << "��Ǯ����Ϊ��";
	for (int i = 1; i <= n; i++)
	{
		cout << x[i] <<"����"<< i << "��Ӳ��  ";
	}
	
}



int main()
{
	int i, j;
	Data();
	Coin();
	Out();
	cout << endl;
	cout << "����¼����¼��������������" << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= y; j++)
		{
				cout << m[i][j]<<"   ";
		}
		cout << endl;
	}

	cout << "��Ǻ��������ѡ�е�����Ӳ����ţ���" << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= y; j++)
		{
			cout << s[i][j] << "   ";
		}
		cout << endl;
	}

}