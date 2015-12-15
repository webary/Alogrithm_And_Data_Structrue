/**************************************************************
求费波纳茨数列的第N项（0<N<100000000）,如果结果很多，对1000000007取模
***************************************************************/
#include<iostream>
#include<vector>
#include<climits>
using namespace std;

const int arrSize = 100000000;
static int data[arrSize]={1,1}; //约400MB
void getData(){
        for(int i = 2; i < arrSize; i++)
            data[i] = (data[i-1]+data[i-2])%1000000007;
}
//第一种方式，用数组存储
int getNthNumber(int n) {
        if(data[3]==0)
            getData();
        if(n<arrSize)
            return data[n-1];
        int left=data[arrSize-2],right=data[arrSize-1],i,tmp;
        for(i = 1000000; i < n; i++){
            tmp = right;
            right = (left+right);
            if(right>1000000007) right %= 1000000007;
            left = tmp;
        }
        return right;
}
//第二种方式，用循环临时求得
int getNthNumber2(int n) {
        int left=1,right=1,i,tmp;
        for(i = 2; i < n; i++){
            tmp = right;
            right = (left+right)%1000000007;
            left = tmp;
        }
        return right;
}
int main() {
    int N;
    while(cin>>N)
    	cout<<getNthNumber(n)<<endl;
    return 0;
}
