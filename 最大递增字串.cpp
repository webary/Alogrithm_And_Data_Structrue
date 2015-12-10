/**************************************************************
分治法求解最大子序列和
***************************************************************/
#include<iostream>
#include<vector>
#include<climits>
using namespace std;

const int arrSize = 100000000;
static int data[arrSize]={1,1};
void getData(){
        for(int i = 2; i < arrSize; i++)
            data[i] = (data[i-1]+data[i-2])%1000000007;
}
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
    for(int i=10000000; i<10000010; ++i)
    	cout<<getNthNumber(i)<<" ";
}
