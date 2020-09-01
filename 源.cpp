#include<iostream>
using namespace std;

const  int MAX=100;

struct goods{
	int value;//价值
	int weight;//重量
	int c;//体积
}goods[MAX];


int n,W,V;
int m[MAX][MAX][MAX];//优化函数
int s[MAX][MAX][MAX];//标记函数

//设置物品个数n
//设置物品的价值v、重量w、体积c
//总重量限制W、总体积限制V
void DataIn() {
	cout << "请输入物品总数：";
	cin >> n;
	cout << endl;
	cout << "请输入各物品的价值：";
	for (int i = 1; i <= n; i++)
		cin >> goods[i].value;
	cout << endl;
	cout << "请输入各物品的重量：";
	for (int i = 1; i <=n; i++)
		cin >> goods[i].weight;
	cout << endl;
	cout << "请输入各物品的体积：";
	for (int i = 1; i <= n; i++)
		cin >> goods[i].c;
	cout << endl;
	cout << "请输入总重量限制W：";
	cin >> W;
	cout << "请输入总体积限制V：";
	cin >> V;
}


//优化+标记
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
	cout << "选择的物品分别是第"<<endl;
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
	cout << "个" << endl;;
}



int main() 
{
    int i, j, k;
	DataIn();
	Knapsack();
	cout << "最优选择时价值最大为：" << m[n][W][V]<< endl;
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
