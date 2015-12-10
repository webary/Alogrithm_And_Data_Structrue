// by MoreWindows( http://blog.csdn.net/MoreWindows )
#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;
//------------------------快速排序----------------------------
void quick_sort(int s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
				j--;
			if(i < j)
				s[i++] = s[j];

			while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
				i++;
			if(i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quick_sort(s, l, i - 1); // 递归调用
		quick_sort(s, i + 1, r);
	}
}
//------------------------归并排序----------------------------
//将有二个有序数列a[first...mid]和a[mid...last]合并。
void mergearray(int a[], int first, int mid, int last, int temp[])
{
	int i = first, j = mid + 1;
	int m = mid,   n = last;
	int k = 0;

	while (i <= m && j <= n)
	{
		if (a[i] < a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}

	while (i <= m)
		temp[k++] = a[i++];

	while (j <= n)
		temp[k++] = a[j++];

	for (i = 0; i < k; i++)
		a[first + i] = temp[i];
}
void mergesort(int a[], int first, int last, int temp[])
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		mergesort(a, first, mid, temp);    //左边有序
		mergesort(a, mid + 1, last, temp); //右边有序
		mergearray(a, first, mid, last, temp); //再将二个有序数列合并
	}
}
bool MergeSort(int a[], int n)
{
	int *p = new int[n];
	if (p == NULL)
		return false;
	mergesort(a, 0, n - 1, p);
	return true;
}
//------------------------堆排序---------------------------
inline void Swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}
//建立最小堆
//  从i节点开始调整,n为节点总数 从0开始计算 i节点的子节点为 2*i+1, 2*i+2
void MinHeapFixdown(int a[], int i, int n)
{
	int j, temp;

	temp = a[i];
	j = 2 * i + 1;
	while (j < n)
	{
		if (j + 1 < n && a[j + 1] < a[j]) //在左右孩子中找最小的
			j++;

		if (a[j] >= temp)
			break;

		a[i] = a[j];     //把较小的子结点往上移动,替换它的父结点
		i = j;
		j = 2 * i + 1;
	}
	a[i] = temp;
}
//建立最小堆
void MakeMinHeap(int a[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		MinHeapFixdown(a, i, n);
}
void MinheapsortTodescendarray(int a[], int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		Swap(a[i], a[0]);
		MinHeapFixdown(a, 0, i);
	}
}
const int MAXN = 5000000;
int a[MAXN];
int b[MAXN], c[MAXN], d[MAXN];
int main()
{
	int i;
	srand(time(NULL));
	for (i = 0; i < MAXN; ++i)
		a[i] = rand() * rand(); //注rand()产生的数在0到0x7FFF之间

	for (i = 0; i < MAXN; ++i)
		d[i] = c[i] = b[i] = a[i];

    clock_t ibegin, iend;

	printf("--当前数据量为%d--By MoreWindows(http://blog.csdn.net/MoreWindows)--\n", MAXN);
	//快速排序
	printf("快速排序:  ");
	ibegin = clock();
	quick_sort(a, 0, MAXN - 1);
	iend = clock();
	printf("%d毫秒\n", iend - ibegin);


	//归并排序
	printf("归并排序:  ");
	ibegin = clock();
	MergeSort(b, MAXN);
	iend = clock();
	printf("%d毫秒\n", iend - ibegin);

	//堆排序
	printf("堆排序:  ");
	ibegin = clock();
	MakeMinHeap(c, MAXN);
	MinheapsortTodescendarray(c, MAXN);
	iend = clock();
	printf("%d毫秒\n", iend - ibegin);

	//STL中的堆排序
	printf("STL中的堆排序: ");
	ibegin = clock();
	make_heap(d, d + MAXN);
	sort_heap(d, d + MAXN);
	iend = clock();
	printf("%d毫秒\n", iend - ibegin);
	return 0;
}
