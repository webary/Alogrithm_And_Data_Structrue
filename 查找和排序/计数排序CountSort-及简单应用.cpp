/**
 * 计数排序完成O(n)时间复杂度的排序算法,注意下面没有考虑有负数的情况,
 * 如果要考虑负数,需要加上一个偏移值
 */
#include<iostream>
using namespace std;

//计数排序算法代码,arr是待排数组,len是待排数组长度,k是数组中元素的上界
//这个代码实现也是《算法导论》上推荐写法
void countSort(int arr[], int len, int k)
{
    if(arr == NULL || len <= 0 || k <= 0)
        return ;
    int *C = new int[k](), i; //C[]保存计数数据,加括号可以直接初始化为0
    int *B = new int[len](); //B[]用来保存排序结果
    for(i = 0; i < len; ++i)
        ++C[arr[i]];
    for(i = 1; i < k; ++i) //确定不比该位置大的数据个数
        C[i] += C[i - 1];
    for(i = len - 1; i >= 0; --i) {
        --C[arr[i]]; //可能有相同的数据
        B[C[arr[i]]] = arr[i]; //把arr[i]放在最终位置上
    }
    for(i = 0; i < len; ++i) //复制排序好的数到源数组
        arr[i] = B[i];
    delete[] C; //释放主动分配的内存
    delete[] B;
}

//基于范围的排序方法,此处限定了只能对上界为65536的数排序
void rangeSort(int arr[], int len)
{
    if(arr == NULL || len <= 0)
        return ;
    int data[65536] = {0}, i, j;
    for(i = 0; i < len; ++i)
        ++data[arr[i]];
    for(i = j = 0; i < len;)
        if(data[j]--)
            arr[i++] = j ;
        else
            j++;
}

//找出成绩表中前k的分数(满分为100),并从大到小输出
void sortAndGetTopK(int score[], int len, int k, int res[])
{
    if(score == NULL || res == NULL || len <= 0 || k <= 0)
        return ;
    int data[101] = {0}, i, j; //分数最大为100,所以数组大小定义为101
    for(i = 0; i < len; ++i)
        ++data[score[i]];
    for(i = 0, j = 100; i < k; ) //因为要找最大的k个,所以倒着找
        if(data[j]--)
            res[i++] = j ;
        else
            --j;
}

int main()
{
    int a[] = {6, 5, 7, 9, 3, 8, 2, 4, 0, 1};
    int n = sizeof(a) / sizeof(a[0]);
    //countSort(a,n,10);
    rangeSort(a, n);
    for(int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
    //计数排序简单应用:找出成绩表中前k的分数值
    int score[] = {67, 34, 89, 93, 82, 99, 16, 100, 77, 91}, top[5];
    int len_s = sizeof(score) / sizeof(score[0]);
    sortAndGetTopK(score, len_s, 5, top);
    cout << "\n成绩列表为：";
    for(auto &elem : score)
        cout << elem << " ";
    cout << endl << "top k成绩为：";
    for(auto &elem : top)
        cout << elem << " ";
    cout << endl;
    return 0;
}
