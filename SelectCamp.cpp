#include<iostream>
using namespace std;


#define MAX 100

double Camp[MAX];
double SelectC[MAX];
int j = 0;

void SelectCamp(double length, int n)
{
	double L = 0;
	int i = 0;
	while (length - L > 30)
	{
		if ((Camp[i] - L) > 30)
		{
			i--;
			SelectC[j] = i;
			L = Camp[i];
			j++;
			i++;
		}
		else
		{
			i++;
		}
	}
}

void Out()
{
	cout << "�ܵ���Ӫ�����ǣ�" << j << endl;
	cout << "��Ӫ�ر��Ϊ(Ĭ�ϵ�һ����Ӫ�ر��Ϊ1)��";
	for (int i = 0; i < j; i++)
	{
		cout << SelectC[i]+1 << "  ";
	}
}
void main()
{
	double L;
	int n;
	cout << "���ÿ���·�߳���Ϊ����ó���30ǧ�ף���" << endl;
	cin >> L;
	cout << "���ÿ���·���ϵ���Ӫ�ظ���Ϊ��" << endl;
	cin >> n;
	cout << "������Щ��Ӫ�ؾ������ľ��볤�ȷֱ��ǣ��涨��Ӫ�ؾ������ľ��������������������Ӫ�ؼ�ľ��벻����30ǧ�ף���" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> Camp[i];
	}

	SelectCamp(L, n);
	Out();
}