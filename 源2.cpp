
#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

const int MAX = 20000;
int n, k;


void CreateS(double S[],int n)       //����n���˴˲���ȵ����������������S�����±�1��ʼ
{
	srand(unsigned(time(0)));
	cout << "���ɵ�" << n << "��������ȵ����ֱ��ǣ�" << endl;
	for (int i = 0; i < n; i++)
	{
		bool flag = 0;
		S[i] = rand()*1./(RAND_MAX/20000.);
		for (int j = 1; j < i; j++)                 //�ж����ɵ����Ƿ��ظ�
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

void InsertSort(double s[],int low,int high)       //ֱ�Ӳ�������
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



double Select(double s[],int low,int high, int k)  //������S���±�low��high�еĵ�k����
{
	double *M=new double[MAX];
	//ÿ���������λ��
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
		//����λ������M
		M[t] = s[i + 2];
		t++;

	}
	//ѡM����λ��m
	double m= Select(M,0, t,t/2);
	delete[] M;
	//��m���ֳ�S1��S2
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
	//������ݹ�
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
	cout << "�����뻥����ȵ�������ĸ�����";
	cin >> n;
	cout << endl;
	CreateS(S,n);
	cout << "��������Ҫ���ҵ�k��k��ʾ��kС������;";
	cin >> k;
	clock_t start_time = clock();//��ʼ��ʱ
	num=Select(S, 0,n,k);
	clock_t finish_time = clock();//��ʱ����
	double duration = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
	cout << "��" << k << "С�����ǣ�" << num << endl;
	cout << "�㷨��ʱ��" << duration << "s." << endl;
	cout << "-----------------------�����㷨����ȷ��----------------------------" << endl;
	cout << "��ʱ�����е���Ϊ��" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << S[i] << " ";
		if (i % 5 == 4)
			cout << endl;
	}
	cout<<"ֱ�Ӳ����������е�����" << endl;
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

