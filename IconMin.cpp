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
		cout << "ʹ�ñ�ֵΪ " << i.value << " ��Ǯ�� " << i.num << "��" << endl;
	}
}



void main()
{
	int n;
	double Y;
	cout << "����Ǯ������nΪ��";
	cin >> n;
	cout << endl;
	cout << "������Ǯ��yΪ��";
	cin >> Y;
	cout << endl;

	SelectIcon(Y,n); //���ĺ�������
	OutIcon();


}