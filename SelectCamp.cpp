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
	cout << "总的宿营天数是：" << j << endl;
	cout << "宿营地编号为(默认第一个宿营地编号为1)：";
	for (int i = 0; i < j; i++)
	{
		cout << SelectC[i]+1 << "  ";
	}
}
void main()
{
	double L;
	int n;
	cout << "设置考察路线长度为（最好超过30千米）：" << endl;
	cin >> L;
	cout << "设置考察路线上的宿营地个数为：" << endl;
	cin >> n;
	cout << "设置这些宿营地距出发点的距离长度分别是（规定宿营地距出发点的距离递增，且响铃两个宿营地间的距离不超过30千米）：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> Camp[i];
	}

	SelectCamp(L, n);
	Out();
}