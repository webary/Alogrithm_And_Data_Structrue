#include<vector>
#include<iostream>
using namespace std;

//二分查找模板
template<typename T1,typename T2>
int binarySearch(const T1 &arr,const T2 &value,size_t len)
{
    int low = 0, high = len-1, mid;
    while(low <= high) {
        mid = low + ((high-low)>>1); //思考为什么不写作(high+low)/2;
        if(value-arr[mid]<1e-6 && arr[mid]-value<1e-6)//思考为何不写作arr[mid]!=value
            return mid;
        if(value<arr[mid])
            high = mid-1;	//如果写作high = mid;可以吗
        else
            low = mid+1;	//如果写作low = mid;可以吗
    }
    return -1;
}
//二分查找模板-如果有相等的元素，返回第一次出现的位置
template<typename T1,typename T2>
int binarySearchFirst(const T1 &arr,const T2 &value,size_t len)
{
    int low = 0, high = len-1, mid;
	if(arr[low]>value || arr[high]<value) //不在范围内
		return -1;
    while(low <= high) {
        mid = low + ((high-low)>>1); //思考为什么不写作(high+low)/2;
        if(value<=arr[mid])
            high = mid-1;	//如果写作high = mid;可以吗
        else
            low = mid+1;	//如果写作low = mid;可以吗
    }
    return (value-arr[low]<1e-6 && arr[low]-value<1e-6)?low:-1;
}

int main()
{
    int i;
    double arr[10] = {0,1,2,5,5,5,5,5,8,9};
    //for(i=0; i<10; i++)
    //    arr[i] = i;
    for(i=-1; i<11; i++)
        cout<<"the index of '"<<i<<"': "<<binarySearch(arr,i,10)<<endl;

	cout<<endl;
	vector<int> arr_i(arr,arr+10);
    for(i=-1; i<11; i++)
        cout<<"the index of '"<<i<<"': "<<binarySearchFirst(arr_i,i,arr_i.size())<<endl;
    return 0;
}
