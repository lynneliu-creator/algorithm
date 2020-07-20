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

void CreatePoint(int n)       //生成n个位置随机的点
{
	srand(unsigned(time(0)));//生成时间种子

	cout << "生成的"<<n<<"个点分别是：" << endl;
	for (int i = 1; i <=n; i++)
	{
		point[i].x = rand()%(MAX-MIN+1)+MIN;
		point[i].y = rand()%(MAX-MIN+1)+MIN;
		cout << "( " << point[i].x << " , " << point[i].y << " )    ";
		if (i % 5 == 0)
			cout << endl;
	}
}
//对X、Y快速排序
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

//两个点之间的距离求解
double Distance(int x1, int y1, int x2, int y2)
{
  return  sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

double Mindistance(P p[],int low,int high)
{
	if (high-low==1) //2点的情形   
	{
		minpoint[0].x = p[low].x;
		minpoint[0].y = p[low].y;
		minpoint[1].x = p[high].x;
		minpoint[1].y = p[high].y;
		return Distance(p[low].x, p[low].y, p[high].x, p[high].y);
	}

	if (high - low == 2) //3点的情形   
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

	if (high - low > 2)    //递归
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

		//找到两侧距mid不超过MinDis的点
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

		YQuicksort(midpoint, 1, j);     //对窄缝里的点进行Y排序
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
	cout << "请输入随机点的个数：";
	cin >> n;
	while (n ==1)
	{
		cout << "请重新输入n" << endl;
		cout << "请输入随机点的个数：";
		cin >> n;
	}
	cout << endl;
	//freopen("data.txt", "r", stdin);//读入数据
	//freopen("data.txt", "w", stdout);//写入数据
	CreatePoint(n);
	clock_t start_time = clock();//开始计时
	XQuicksort(point,1,n);
	d=Mindistance(point,1,n);
	clock_t finish_time = clock();//计时结束
	double duration = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
	cout << endl;
	cout << "最近点对是： ( " << minpoint[0].x << " , " << minpoint[0].y << " )  ";
	cout<< " ( " << minpoint[1].x << " , " << minpoint[1].y << " ) " << endl;
	cout << "最近距离是：" << d << endl;
	cout << "算法耗时：" << duration<<"s." << endl;
	//fclose(stdin);
	//fclose(stdout);
	//cout << "数据已写入data.txt" << endl;
	return 0;
}
