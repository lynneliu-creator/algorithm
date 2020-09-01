#include<iostream>
using namespace std;

const  int MAX=100;

struct goods{
	int value;//��ֵ
	int weight;//����
	int c;//���
}goods[MAX];


int n,W,V;
int m[MAX][MAX][MAX];//�Ż�����
int s[MAX][MAX][MAX];//��Ǻ���

//������Ʒ����n
//������Ʒ�ļ�ֵv������w�����c
//����������W�����������V
void DataIn() {
	cout << "��������Ʒ������";
	cin >> n;
	cout << endl;
	cout << "���������Ʒ�ļ�ֵ��";
	for (int i = 1; i <= n; i++)
		cin >> goods[i].value;
	cout << endl;
	cout << "���������Ʒ��������";
	for (int i = 1; i <=n; i++)
		cin >> goods[i].weight;
	cout << endl;
	cout << "���������Ʒ�������";
	for (int i = 1; i <= n; i++)
		cin >> goods[i].c;
	cout << endl;
	cout << "����������������W��";
	cin >> W;
	cout << "���������������V��";
	cin >> V;
}


//�Ż�+���
void Knapsack() 
{
		int i,j,k;
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= W; j++)
			{
				for (k = 1; k <= V; k++)
				{
					if ((goods[i].weight <= j) && (goods[i].c <= k))
					{
						if (m[i - 1][j][k] > (m[i - 1][j - goods[i].weight][k - goods[i].c] + goods[i].value))
						{
							m[i][j][k] = m[i - 1][j][k];
							s[i][j][k] = 0;
						}
						else
						{
							m[i][j][k]=m[i - 1][j - goods[i].weight][k - goods[i].c] + goods[i].value;
							s[i][j][k] = 1;
						}
					}
					else
					{
						m[i][j][k] = m[i - 1][j][k];
						s[i][j][k] = 0;
					}
				}
			}
		}
}


void Out()
{
	int i = n;
	int j = W;
	int k = V;
	cout << "ѡ�����Ʒ�ֱ��ǵ�"<<endl;
	while(i&&j&&k)
	{
		if (s[i][j][k] == 1) 
		{
			cout << i<<"  " ;
			j -= goods[i].weight;
			k -= goods[i].c;
		}
		i--;
	}
	cout << "��" << endl;;
}



int main() 
{
    int i, j, k;
	DataIn();
	Knapsack();
	cout << "����ѡ��ʱ��ֵ���Ϊ��" << m[n][W][V]<< endl;
	Out(); 
	cout << endl;
	/*
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= W; j++)
		{
			for (k = 1; k <= V; k++)
			{
				cout << s[i][j][k]<<"   ";
			}
			cout << endl;
		}
		cout << endl;
	}
	*/
}
