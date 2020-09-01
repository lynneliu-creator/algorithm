
#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

const int MAX = 20000;
int n, k;


void CreateS(double S[],int n)       //生成n个彼此不相等的随机数，放入数组S，从下标1开始
{
	srand(unsigned(time(0)));
	cout << "生成的" << n << "个互不相等的数分别是：" << endl;
	for (int i = 0; i < n; i++)
	{
		bool flag = 0;
		S[i] = rand()*1./(RAND_MAX/20000.);
		for (int j = 1; j < i; j++)                 //判断生成的数是否重复
			if (S[i] == S[j])
			{
				i--;
				flag = 1;
				break;
			}
		if(flag==0)
		cout << S[i] << " ";
		if (i % 5 == 4)
			cout << endl;
	}
}

void InsertSort(double s[],int low,int high)       //直接插入排序
{
	int i, j;
	double k;
	for (i = low+1; i <high; i++)
	{
		if (s[i] < s[i - 1])
		{
			k = s[i];
			for (j = i - 1; k < s[j]; j--)
			{
				s[j + 1] = s[j];
			}
			s[j + 1] = k;			
		}
	}
}



double Select(double s[],int low,int high, int k)  //求数组S中下标low到high中的第k个数
{
	double *M=new double[MAX];
	//每五个数找中位数
	if (high - low == 1)
		return s[low];
	if ((high - low < 5)&&(high-low>1))
	{
		InsertSort(s, low, high);
		return s[low + k-1];
	}
	int t=0;
	int i, j;
	for (i = low; (j = i + 4)&&(j<high); i += 5)
	{
		InsertSort(s, i, j);
		//把中位数放入M
		M[t] = s[i + 2];
		t++;

	}
	//选M的中位数m
	double m= Select(M,0, t,t/2);
	delete[] M;
	//用m划分出S1和S2
	double *S1 = new double[MAX];
	double *S2=new double[MAX];
	int s1=0, s2=0;
	for (i = low; i < high; i++)
	{
		if (s[i] < m)
		{
			S1[s1] = s[i];
			s1++;
		}
		 if (s[i] > m)
		{
			S2[s2] = s[i];
			s2++;
		}
	}
	//子问题递归
	if (k == s1+1)
	{
		return m;
	}
	else if (k <=s1)
	{
		return Select(S1, 0, s1, k);
	}
	else if(k>s1+1)
	{
		return Select(S2, 0, s2, k - s1 - 1);
	}
	delete[] S1;
	delete[] S2;
}


int main()
{
	double num;
	double *S = new double[MAX];
	cout << "请输入互不相等的随机数的个数：";
	cin >> n;
	cout << endl;
	CreateS(S,n);
	cout << "请输入所要查找的k（k表示第k小的数）;";
	cin >> k;
	clock_t start_time = clock();//开始计时
	num=Select(S, 0,n,k);
	clock_t finish_time = clock();//计时结束
	double duration = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
	cout << "第" << k << "小的数是：" << num << endl;
	cout << "算法耗时：" << duration << "s." << endl;
	cout << "-----------------------检验算法的正确性----------------------------" << endl;
	cout << "此时数组中的数为：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << S[i] << " ";
		if (i % 5 == 4)
			cout << endl;
	}
	cout<<"直接插入排序所有的数：" << endl;
	InsertSort(S, 0, n);
	for (int i = 0; i <n; i++)
	{
		cout << S[i] << " ";
		if (i % 5 == 4)
			cout << endl;
	}
	delete[] S;
	return 0;
}

