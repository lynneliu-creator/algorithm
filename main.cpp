#include<iostream>
#include<vector>
using namespace std;

#define  MAX 10000
//实例
int N = 8;

int N1[3]= { 4,5,6 };
int N2[2] = { 2,3 };
int N3[2] = { 1,3 };
int N4[2] = { 3,6 };
int N5[2] = { 7,8 };


vector<int> B[8];//Bi电路板连接的其他电路板


void Pre()//预处理(*)
{
	B[0] = { 3 };
	B[1] = { 3 };
	B[2] = { 1,2,6 };
	B[3] = { 5,6 };
	B[4] = { 4,6 };
	B[5] = { 4,5,3 };
	B[6] = { 8 };
	B[7] = { 7 };

}

int bestx[MAX][9] = { 0 };;//最优排列
int x[9] = { 0,1,2,3,4,5,6,7,8 };//排列
int MaxDensity = 4;//排列密度
int ii = 0;

void swap(int &a, int &b) 
{
	int temp = a;
	a = b;
	b = temp;
}

int Density(int i)//x[i]为新加的节点，求相邻插槽的连线数（*）
{
	
	int count = 0;
	int flag = 0;
	
	for (int j=1;j<i; j++)
	{
		if ((j == 4) || (j == 5) || (j == 6))
		{
			flag++;
		}
		int b = x[j];
		for (int r = i; r <= N; r++)//查询 已排好的列中的电路板与未排列的电路板相连的个数
		{
			vector<int>::iterator result;
			result = find(B[b-1].begin(), B[b-1].end(), x[r]);//end指向末尾元素的下一个元素
			if (result != B[b-1].end())
			{
				count++;
			}

		}
	}
	if ((flag==1)||(flag==2))
	{
		count--;
	}
	return count;
}

void Backtrack(int t,int d0)//回溯算法
{
	if (t == N)
	{
		for (int i = 1; i < N+1; i++)
		{
			bestx[ii][i] = x[i];
		}
	
		bestx[ii][0] = d0;
		if (d0 < MaxDensity)
		{
			MaxDensity = d0;
		}
		
		ii++;

	}
	else
	{
		for (int i = t; i <= N; i++)
		{
			int d1 = Density(i);
			if (d0 > d1)
			{
				d1 = d0;
			}
			if (d1<=MaxDensity)
			{
				
				swap(x[t], x[i]);//同一层结点的选择，相当于同一位置不同的人坐
				Backtrack(t + 1,d1);
				swap(x[t], x[i]);//如果下个结点剪枝了，就交换回到最近的父节点，进行下父结点下一个子树的检测。
			}
		}
	}
}

int main()
{
	Pre();
	Backtrack(1,0);
	cout << "最小密度：" << MaxDensity << endl;
	cout << "最优解个数：" << ii << endl;
	cout << "最优解排列方式:";
	for (int i = 0; i < ii; i++) 
	{
		if (bestx[i][0] == MaxDensity) 
		{
			for (int j = 1; j <= N; j++)
			{
				cout << bestx[i][j] << " ";
			}
			cout << endl;
		}
		
	}
	
	cout << endl;

	return 0;
}

