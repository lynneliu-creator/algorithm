#include<iostream>
#include<vector>
using namespace std;

#define  MAX 10000
//ʵ��
int N = 8;

int N1[3]= { 4,5,6 };
int N2[2] = { 2,3 };
int N3[2] = { 1,3 };
int N4[2] = { 3,6 };
int N5[2] = { 7,8 };


vector<int> B[8];//Bi��·�����ӵ�������·��


void Pre()//Ԥ����(*)
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

int bestx[MAX][9] = { 0 };;//��������
int x[9] = { 0,1,2,3,4,5,6,7,8 };//����
int MaxDensity = 4;//�����ܶ�
int ii = 0;

void swap(int &a, int &b) 
{
	int temp = a;
	a = b;
	b = temp;
}

int Density(int i)//x[i]Ϊ�¼ӵĽڵ㣬�����ڲ�۵���������*��
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
		for (int r = i; r <= N; r++)//��ѯ ���źõ����еĵ�·����δ���еĵ�·�������ĸ���
		{
			vector<int>::iterator result;
			result = find(B[b-1].begin(), B[b-1].end(), x[r]);//endָ��ĩβԪ�ص���һ��Ԫ��
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

void Backtrack(int t,int d0)//�����㷨
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
				
				swap(x[t], x[i]);//ͬһ�����ѡ���൱��ͬһλ�ò�ͬ������
				Backtrack(t + 1,d1);
				swap(x[t], x[i]);//����¸�����֦�ˣ��ͽ����ص�����ĸ��ڵ㣬�����¸������һ�������ļ�⡣
			}
		}
	}
}

int main()
{
	Pre();
	Backtrack(1,0);
	cout << "��С�ܶȣ�" << MaxDensity << endl;
	cout << "���Ž������" << ii << endl;
	cout << "���Ž����з�ʽ:";
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

