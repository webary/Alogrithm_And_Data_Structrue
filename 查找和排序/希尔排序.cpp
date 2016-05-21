#include<cstdlib>
#include<iostream>
using namespace std;

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))
//int a[5]= {3,2,5,4,1};
int a[9] = {25,84,21,47,15, 27,68,35,20};

//输出数组a的每一个值
void output(int arr[], int n)
{
    for(int i=0; i<n; i++) {
        cout<<arr[i]<<"  ";
    }
    cout<<endl;
}

//交换两个变量的值，利用引用传递参数
template <typename T>
void inline swapT(T& n1,T& n2)
{
    T temp = n1;
    n1 = n2;
    n2 = temp;
}
//c++形式的希尔排序函数，可以接受各种类型的数组
template <typename T>
void shellSort(T arr[],int arrSize)	//对数组进行希尔排序
{
    for(int gap = arrSize/2; gap>0; gap/=2)
        for(int i=0; i<arrSize-gap; i++)
            for(int j=i; j>=0 && arr[j]>arr[j+gap]; j-=gap) {
                swapT(arr[j],arr[j+gap]);
            }
}
//附:c语言版的希尔排序函数，只能排序int数组
void shellSort_c(int arr[],int arrSize)	//对数组进行希尔排序
{
    for(int gap = arrSize/2; gap>0; gap/=2) //步长变为前一次的一半
        for(int i=0; i<arrSize-gap; i++)
            for(int j=i; j>=0 && arr[j]>arr[j+gap]; j-=gap) { //插入排序思想
                int temp = arr[j];
                arr[j] = arr[j+gap];
                arr[j+gap] = temp;
            }
}
//对数组进行特定步长（步长为step）的一轮希尔排序
void shellSort_OneStep_c(int arr[],int arrSize,int step)
{
    int gap = step;
    for(int i=0; i<arrSize-gap; i++)
        for(int j=i; j>=0 && arr[j]>arr[j+gap]; j-=gap) {
            int temp = arr[j];
            arr[j] = arr[j+gap];
            arr[j+gap] = temp;
        }
}

int main()
{
    shellSort(a,LEN(a));
    cout<<"希尔排序后数组序列为："<<endl;
    output(a,LEN(a));

    cout<<"\n对下列数组进行一趟固定步长的希尔排序后："<<endl;
    int arr[] = {49,38,65,97,76, 13,27,49,55,04};
    output(arr,LEN(arr));
    shellSort_OneStep_c(arr,LEN(arr),5);
    output(arr,LEN(arr));
    return 0;
}
