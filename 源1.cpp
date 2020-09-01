#include<iostream>
using namespace std;

const  int MAX = 100;

struct coins {
	int value;//价值
	int weight;//重量
}coin[MAX];


int n = 4;
int y = 12;
int m[MAX][MAX];//备忘录，记录最轻总重量
int s[MAX][MAX];//标记函数，记录最大硬币面值


void Data() {
	cout << "物品总数：4" << endl;
	cout << "各物品的价值：1 4 6 8" << endl;
	coin[1].value = 1;
	coin[2].value = 4;
	coin[3].value = 6;
	coin[4].value = 8;
	cout << "各物品的重量：1 2 4 6" << endl;
	coin[1].weight = 1;
	coin[2].weight = 2;
	coin[3].weight = 4;
	coin[4].weight = 6;
	cout << "总价值y：12" << endl;
	cout << "***************************************************" << endl;
}

void Coin()
{
	int i, j;
	for (i = 1; i <= y; i++)  	//i=1时
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
	int x[MAX];//记录各硬币使用次数
	int val = y;
	int j = n;
	cout << "最轻总重量：" << m[j][val] << endl;
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
	cout << "付钱方法为：";
	for (int i = 1; i <= n; i++)
	{
		cout << x[i] <<"个第"<< i << "个硬币  ";
	}
	
}



int main()
{
	int i, j;
	Data();
	Coin();
	Out();
	cout << endl;
	cout << "备忘录（记录最轻总重量）：" << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= y; j++)
		{
				cout << m[i][j]<<"   ";
		}
		cout << endl;
	}

	cout << "标记函数（标记选中的最大的硬币序号）：" << endl;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= y; j++)
		{
			cout << s[i][j] << "   ";
		}
		cout << endl;
	}

}