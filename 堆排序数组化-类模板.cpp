#include <iostream>
#include <vector>
using namespace std;

enum HeapType {HT_MaxHeap, HT_MinHeap}; //定义堆的类型:可以是大根堆或小根堆

template<typename T>
class HeapSort {
    vector<T> data;  //堆中的数据
    bool heapSelect; //堆类型
public:
    //传递数组名和大小来初始化堆
    HeapSort(const T a[], size_t n, HeapType tp): data(a, a + n), heapSelect(tp)
    {
        init();
    }
    //传递数组名来初始化堆,载入全部元素
    template<size_t n>
    HeapSort(const T(&a)[n], HeapType tp): data(a, a + n), heapSelect(tp)
    {
        init();
    }
    //在堆上执行堆排序
    void sort()
    {
        for (int i = data.size() - 1; i > 0; i--) {
            swap(data[i], data[0]);
            fixDown(0, i);
        }
    }
    //在堆中加入新的数据nNum
    void addNumber(const T &num)
    {
        data.push_back(num);
        fixUp();
    }
    //在堆中删除数
    T deleteNumber()
    {
        int n = data.size();
        if (n == 0)
            return -1;
        swap(data[0], data[n - 1]);
        fixDown(0, n - 1);
        T temp = data[n - 1];
        data.erase(data.end() - 1);
        return temp;
    }
    //显示当前数组中的数
    void print(const char *str = 0)
    {
        if (str != NULL && str[0] != '\0')
            cout << str << endl;
        for (auto &elem : data)
            cout << elem << " ";
        cout << endl;
    }
protected:
    //建立最小堆
    void init()
    {
        int n = data.size();
        for (int i = n / 2 - 1; i >= 0; i--) //从第一个有孩子结点的结点开始向前
            fixDown(i, n);
    }
    //向上调整(插入新结点后执行)
    void fixUp()
    {
        int i = data.size() - 1;
        for (int j = (i - 1) / 2; j >= 0 && i != 0 && cmpInFixUp(data[i], data[j]);
                i = j, j = (i - 1) / 2)
            swap(data[i], data[j]);
    }
    //从i节点开始向下调整,n为节点总数,使i为根结点的子树满足大/小根堆的定义
    void fixDown(int i, int n)
    {
        T temp = data[i];
        for (int j = 2 * i + 1; j < n; i = j, j = 2 * i + 1) {
            if (j + 1 < n && cmpInFixDown(data[j], data[j + 1]))
                j++;
            if (cmpInFixDown(data[j], temp, true))
                break;
            data[i] = data[j]; //把较小的子结点往上移动,替换它的父结点
        }
        data[i] = temp;
    }
    //在向下调整时的比较(与堆类型有关)
    bool cmpInFixDown(const T& x, const T& y, bool orEqual = false)
    {
        return heapSelect == HT_MinHeap ? (orEqual ? x >= y : x > y)
               : (orEqual ? x <= y : x < y);
    }
    //在向上调整时的比较(与堆类型有关)
    bool cmpInFixUp(const T& x, const T& y)
    {
        return heapSelect == HT_MinHeap ? x < y : x > y;
    }
};

int main()
{
    int a[] = {9, 12, 17, 30, 50, 20, 60, 65, 4, 19};
    int b[] = {5, 8, 12, 19, 28, 20, 15, 22};

    HeapSort<int> minHeap1(b, HT_MinHeap); //用数组建立小根堆
    minHeap1.print("建堆完成后:"); //输出建堆完成后的序列

    minHeap1.addNumber(3);
    minHeap1.print("插入3调整后:"); //插入3之后调整堆完成后的序列

    minHeap1.sort();  //利用小根堆进行堆排序：小根堆排序后结果是递减的
    minHeap1.print("堆排完成后:"); //输出排序后数组

    cout << endl;

    HeapSort<int> maxHeap1(a, HT_MaxHeap); //用数组建立大根堆
    maxHeap1.print("建堆完成后:");

    maxHeap1.sort();  //利用大根堆进行堆排序：大根堆排序后结果是递增的
    maxHeap1.print("堆排完成后:"); //输出排序后数组

    return 0;
}


///下面是C形式的堆排序数组化
//新加入i结点 其父结点为(i - 1) / 2
void MinHeapFixup(int a[], int i)
{
    for (int j = (i - 1) / 2; (j >= 0 && i != 0) && a[i] > a[j]; i = j, j = (i - 1) / 2)
        swap(a[i], a[j]);
}
//从i节点开始调整,n为节点总数 从0开始计算 i节点的子节点为 2*i+1, 2*i+2
void MinHeapFixdown(int a[], int i, int n)
{
    int j, temp = a[i];
    j = 2 * i + 1;
    while (j < n) {
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
//小根堆的堆排序
void MinHeapSort(int a[], int n)
{
    for (int i = n - 1; i >= 1; i--) {
        swap(a[i], a[0]);
        MinHeapFixdown(a, 0, i);
    }
}
//在最小堆中加入新的数据nNum
void MinHeapAddNumber(int a[], int n, int nNum)
{
    a[n] = nNum;
    MinHeapFixup(a, n);
}
//在小根堆中删除数
void MinHeapDeleteNumber(int a[], int n)
{
    swap(a[0], a[n - 1]);
    MinHeapFixdown(a, 0, n - 1);
}
//下面是C形式的调用方式
int main2()
{
    int b[] = {5, 18, 2, 19, 28, 20, 15, 22};
    MakeMinHeap(b, 8); //建堆
    for (auto &elem : b)
        cout << elem << " ";
    cout << endl;
    MinHeapSort(b, 8); //执行堆排序
    for (auto &elem : b)
        cout << elem << " ";
    cout << endl;
    return 0;
}
