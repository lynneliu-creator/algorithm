#include<iostream>
#include<vector>
#include<math.h>
#include<ctime>

using namespace std;

#define p 2    
#define w 1

typedef struct SelectIcon
{
	double value;
	int num;
}icon;



vector<icon> Icon;

void SelectIcon(double y,int n)
{
	if(y>0&&n>=0)
	{
		double v = pow(p, n - 1);
		if (y >= v)
		{
			icon i;
			i.num = y / v;
			i.value = v;
			y -= i.num*i.value;
			Icon.push_back(i);
		}
		n--;
		SelectIcon(y, n);
	}
}

void OutIcon()
{
	while (Icon.size() > 0)
	{
		icon i = Icon.back();
		Icon.pop_back();
		cout << "使用币值为 " << i.value << " 的钱币 " << i.num << "个" << endl;
	}
}



void main()
{
	int n;
	double Y;
	cout << "设置钱币种类n为：";
	cin >> n;
	cout << endl;
	cout << "设置总钱数y为：";
	cin >> Y;
	cout << endl;

	SelectIcon(Y,n); //核心函数调用
	OutIcon();


}