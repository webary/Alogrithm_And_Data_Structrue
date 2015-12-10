#include<iostream>
#include<vector>
#include<climits>
#include<cstring>
using namespace std;

int maxlen;
int maxindex;
char visit[256];
void output(const char * arr);
/* LNRS 动态规划 + hash 记录下标 */
int dp[100];
void LNRS_dp_hash(const char * arr, int size=0) {
	if(size==0)
		size = strlen(arr);
    memset(visit, -1, sizeof(visit)); //visit数组是-1的时候代表这个字符没有在集合中
    memset(dp, 0, sizeof(dp));
    maxlen = maxindex = 0;
    dp[0] = 1;
    visit[arr[0]] = 0;
    for(int i = 1; i < size; ++i) {
        if(visit[arr[i]] == -1) { //表示arr[i]这个字符以前不存在
            dp[i] = dp[i-1] + 1;
            visit[arr[i]] = i; /* 记录字符下标 */
        } else {
            dp[i] = i - visit[arr[i]];
        }
        if(dp[i] > maxlen) {
            maxlen = dp[i];
            maxindex = i + 1 - maxlen;
        }
    }
    output(arr);
}
/* LNRS 动态规划+hash，时间复杂度O(n) 空间复杂度O(1)算法*/
void LNRS_dp_hash_ultimate(const char * arr, int size=0) {
	if(size==0)
		size = strlen(arr);
    memset(visit, -1, sizeof(visit));
    maxlen = maxindex = 0;
    visit[arr[0]] = 0;
    int curlen = 1;
    for(int i = 1; i < size; ++i) {
        if(visit[arr[i]] == -1) {
            ++curlen;
            visit[arr[i]] = i; /* 记录字符下标 */
        } else {
            curlen = i - visit[arr[i]];
        }
        if(curlen > maxlen) {
            maxlen = curlen;
            maxindex = i + 1 - maxlen;
        }
    }
    output(arr);
}

void output(const char* arr)
{
	for(int i=0;i<maxlen;++i)
		cout<<arr[i+maxindex];
	cout<<endl;
}

int main()
{
	LNRS_dp_hash_ultimate("123453678");
	return 0;
}
