/**************************************************************
分治法求解最大子序列和
***************************************************************/
#include<iostream>
#include<vector>
#include<climits>
using namespace std;

inline int max3(int a,int b,int c) {
    a = a>b ? a : b;
    return a>c?a:c;
}
//分治法实现，复杂度为 O(nlogn)
int maxSum( const int * a, int left, int right ) {
    if( left == right )  // Base case
        return a[left];
    int center = left + ((right-left)>>1);
    int maxLeftSum  = maxSum( a, left, center );
    int maxRightSum = maxSum( a, center + 1, right );
    //如果这个最大和字串跨越了中点...
    //找到中点左边最大和
    int maxLeftBorderSum = -INT_MAX, leftBorderSum = 0;
    for( int i = center; i >= left; i-- ) {
        leftBorderSum += a[ i ];
        if( leftBorderSum > maxLeftBorderSum )
            maxLeftBorderSum = leftBorderSum;
    }
    //找到中点右边最大和
    int maxRightBorderSum = -INT_MAX, rightBorderSum = 0;
    for( int j = center + 1; j <= right; j++ ) {
        rightBorderSum += a[ j ];
        if( rightBorderSum > maxRightBorderSum )
            maxRightBorderSum = rightBorderSum;
    }
    //取三个和的最大值作为该串的最大子串和
    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}
/**Kadane 算法实现  复杂度为 O(n)
	如果当前和为负数，后面的数值加上当前和则必然小于原数值，则应将当前和丢弃。
	从第一项开始遍历求和，该子串只可能存在于一个分组以内，且系为该分组的前缀
**/
int maxSummary(int A[], int n) {
    int mmax = A[0], cursum = 0;
    for(int i = 0; i < n; ++i) {
        cursum = cursum<0 ? A[i] : A[i]+cursum;
        mmax = cursum>mmax ? cursum : mmax;
    }
    return mmax;
}
//如果需要记录子串的位置
int maxSummary(int A[], int n, int pos[2]) {
    int mmax = -INT_MAX, cursum = -1;//-1表示还未开始统计
    for(int i = 0; i < n; ++i) {
        if(cursum < 0) {
            cursum = A[i];
            pos[0] = i;
        } else
            cursum += A[i];
        if(cursum > mmax) {
            mmax = cursum;
            pos[1] = i+1;
        }
    }
    return mmax;
}
int main() {
    int a[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int b[] = {-2, -4, -3, -5, -1};
    int pos[2] = {0};
    cout<<maxSum(a,0,8)<<endl;
    cout<<"最大子串和为: "<<maxSummary(a,9,pos)<<endl;
    cout<<"最大和子串为: ";
    for(int i=pos[0]; i<pos[1]; ++i)
        cout<<a[i]<<" ";
    cout<<endl;
}
