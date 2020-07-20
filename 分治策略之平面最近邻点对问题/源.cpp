#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
using namespace std;

const int MAX = 10000;
const int MIN = -10000;

typedef struct {
	int x;
	int y;
}P;

P point[MAX],minpoint[MAX], leftpoint[MAX], rightpoint[MAX], midpoint[MAX];
double MinDis;

void CreatePoint(int n)       //����n��λ������ĵ�
{
	srand(unsigned(time(0)));//����ʱ������

	cout << "���ɵ�"<<n<<"����ֱ��ǣ�" << endl;
	for (int i = 1; i <=n; i++)
	{
		point[i].x = rand()%(MAX-MIN+1)+MIN;
		point[i].y = rand()%(MAX-MIN+1)+MIN;
		cout << "( " << point[i].x << " , " << point[i].y << " )    ";
		if (i % 5 == 0)
			cout << endl;
	}
}
//��X��Y��������
int XPartition(P p[], int low, int high)
{
	int i, j;
	i = low;
	j = high;
	p[0].x= p[i].x;
	p[0].y= p[i].y;
	do
	{
		while ((p[j].x >= p[0].x) && (i < j))
			j--;
		p[i].x = p[j].x;
		p[i].y = p[j].y;
		while ((p[i].x<= p[0].x) && (i < j))
			i++;
		p[j].x = p[i].x;
		p[j].y = p[i].y;
	} while (i != j);
	p[i].x = p[0].x;
	p[i].y = p[0].y;
	return i;
}

void XQuicksort(P p[], int low, int high)
{
	int i;
	if (low < high)
	{
		i = XPartition(p, low, high);
		XQuicksort(p, low, i - 1);
		XQuicksort(p, i + 1, high);
	}
	
}

int YPartition(P p[], int low, int high)
{
	int i, j;
	i = low;
	j = high;
	p[0].x = p[i].x;
	p[0].y = p[i].y;
	do
	{
		while ((p[j].y >= p[0].y) && (i < j))
			j--;
		p[i].x = p[j].x;
		p[i].y = p[j].y;
		while ((p[i].y <= p[0].y) && (i < j))
			i++;
		p[j].x = p[i].x;
		p[j].y = p[i].y;
	} while (i != j);
	p[i].x = p[0].x;
	p[i].y = p[0].y;
	return i;
}

void YQuicksort(P p[], int low, int high)
{
	int i;
	if (low < high)
	{
		i = YPartition(p, low, high);
		YQuicksort(p, low, i - 1);
		YQuicksort(p, i + 1, high);
	}
}

//������֮��ľ������
double Distance(int x1, int y1, int x2, int y2)
{
  return  sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

double Mindistance(P p[],int low,int high)
{
	if (high-low==1) //2�������   
	{
		minpoint[0].x = p[low].x;
		minpoint[0].y = p[low].y;
		minpoint[1].x = p[high].x;
		minpoint[1].y = p[high].y;
		return Distance(p[low].x, p[low].y, p[high].x, p[high].y);
	}

	if (high - low == 2) //3�������   
	{
		double d1 = Distance(p[low].x, p[low].y, p[low+1].x, p[low + 1].y);
		double d2 = Distance(p[low + 1].x, p[low+1].y, p[high].x, p[high].y);
		double d3 = Distance(p[low].x, p[low].y, p[high].x, p[high].y);
		if ((d1 < d2)&&(d1 < d3))
		{
				minpoint[0].x = p[low].x;
				minpoint[0].y = p[low].y;
				minpoint[1].x = p[low + 1].x;
				minpoint[1].y = p[low + 1].y;
				return d1;
		}
		else if ((d2<d3)&&(d2<d1))
		{
			minpoint[0].x = p[low + 1].x;
			minpoint[0].y = p[low + 1].y;
			minpoint[1].x = p[high].x;
			minpoint[1].y = p[high].y;
			return d2;
		}
		else
		{
				minpoint[0].x = p[low].x;
				minpoint[0].y = p[low].y;
				minpoint[1].x = p[high].x;
				minpoint[1].y = p[high].y;
				return d3;

		}
	}

	if (high - low > 2)    //�ݹ�
	{
		int mid = (low + high) / 2;
		double LeftMin, RightMin;
		LeftMin = Mindistance(p, low, mid);
		leftpoint[0].x = minpoint[0].x;
		leftpoint[0].y = minpoint[0].y;
		leftpoint[1].x = minpoint[1].x;
		leftpoint[1].y = minpoint[1].y;


		RightMin = Mindistance(p, mid + 1, high);
		rightpoint[0].x = minpoint[0].x;
		rightpoint[0].y = minpoint[0].y;
		rightpoint[1].x = minpoint[1].x;
		rightpoint[1].y = minpoint[1].y;
	
		if (LeftMin > RightMin)
		{
			minpoint[0].x = rightpoint[0].x;
			minpoint[0].y = rightpoint[0].y;
			minpoint[1].x = rightpoint[1].x;
			minpoint[1].y = rightpoint[1].y;
			MinDis = RightMin;
		}
		else
		{
			minpoint[0].x = leftpoint[0].x;
			minpoint[0].y = leftpoint[0].y;
			minpoint[1].x = leftpoint[1].x;
			minpoint[1].y = leftpoint[1].y;
			MinDis = LeftMin;
		}

		//�ҵ������mid������MinDis�ĵ�
		int j = 1;
		double middis;

		for (int i = mid; (p[mid].x - p[i].x <= MinDis) && (i >= low); i--)
		{
			midpoint[j].x = p[i].x;
			midpoint[j].y = p[i].y;
			j++;
		}
		for (int i = mid+1; (p[i].x - p[mid].x <MinDis) && (i <= high); i++)
		{
			midpoint[j].x = p[i].x;
			midpoint[j].y = p[i].y;
			j++;
		}
		j--;

		YQuicksort(midpoint, 1, j);     //��խ����ĵ����Y����
		for (int i = 1; i <= j; i++)      
			for (int k = i + 1; k <= j; k++)
			{
				if (midpoint[k].y - midpoint[i].y >= MinDis)
					break;
				else
				{
					middis = Distance(midpoint[i].x, midpoint[i].y, midpoint[k].x, midpoint[k].y);
					if (middis < MinDis)
					{
						minpoint[0].x = midpoint[i].x;
						minpoint[0].y = midpoint[i].y;
						minpoint[1].x = midpoint[k].x;
						minpoint[1].y = midpoint[k].y;
						MinDis = middis;
					}
				}
			}
	}

		return MinDis;
}








int main()
{
	int n;double d;
	cout << "�����������ĸ�����";
	cin >> n;
	while (n ==1)
	{
		cout << "����������n" << endl;
		cout << "�����������ĸ�����";
		cin >> n;
	}
	cout << endl;
	//freopen("data.txt", "r", stdin);//��������
	//freopen("data.txt", "w", stdout);//д������
	CreatePoint(n);
	clock_t start_time = clock();//��ʼ��ʱ
	XQuicksort(point,1,n);
	d=Mindistance(point,1,n);
	clock_t finish_time = clock();//��ʱ����
	double duration = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
	cout << endl;
	cout << "�������ǣ� ( " << minpoint[0].x << " , " << minpoint[0].y << " )  ";
	cout<< " ( " << minpoint[1].x << " , " << minpoint[1].y << " ) " << endl;
	cout << "��������ǣ�" << d << endl;
	cout << "�㷨��ʱ��" << duration<<"s." << endl;
	//fclose(stdin);
	//fclose(stdout);
	//cout << "������д��data.txt" << endl;
	return 0;
}
