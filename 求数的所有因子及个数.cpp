#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

///求取一个数的所有因子
//法1：从1遍历到n看能不能整除
vector<int> getFactor(int n)
{
    if(n < 2)
        return vector<int>(1, n);
    vector<int> res;
    res.reserve(n / 2);
    for(int i = 1; i <= n; ++i)
        if(n % i == 0)
            res.push_back(i);
    return res;
}
//法2：只计算1到sqrt(n),然后直接除就一定可以得到所有因子
vector<int> getFactor2(int n)
{
    if(n < 2) //特殊输入直接返回本身
        return vector<int>(1, n);
    vector<int> res;
    res.reserve(n / 2); //这句可以省略,优点是以免多次移动内存
    int end = sqrt(n);
    for(int k = 1; k <= end; ++k) //只统计1到sqrt(n)之间的数能否整除
        if(n % k == 0)
            res.push_back(k);
    //如果n正好可以开方,那么因子个数就是奇数个
    int i = (end * end == n) ? (res.size() - 2) : (res.size() - 1);
    for(; i >= 0; --i)
        res.push_back(n / res[i]);
    return res;
}

///求一个数的因子个数.(不需要得到每个因子)

int prime[670000]; //1000万以内的素数个数为66万+.数组较大,需要设置为全局,否则可能栈溢出
//[素数打表]求得N以内的所有素数,并返回素数个数
int getPrimeNum(int N=10000000)
{
    prime[0] = 2;
    int m, c = 1, i, j; //c记录当前素数个数
    for(i = 3; i <= N; i += 2) { //这里只判断奇数，跳过偶数
        m = (int)sqrt(i + 0.1); //加0.1是防止部分编译器对sqrt()报出不明确的错误
        for(j = 0; prime[j] <= m; ++j)
            if(i % prime[j] == 0)
                break;
        if(prime[j] > m)
            prime[c++] = i;
    }
    return c;
}
//得到n的因子个数(注:也可以在主函数中首先进行一次素数打表,再接收多组输入输出结果)
int getFactorNums(int n)
{
    getPrimeNum(n); //计算n以内的所有素数
    int cnt = 0, nums = 1; //上一次的幂,当前积累的因子个数
    for(int i = 0; n >= prime[i] && n > 1; ++i) { //对每个素数取余,余数为0则继续
        for(cnt = 0; n % prime[i] == 0; ++cnt) //统计该素数对应的幂
            n /= prime[i];
        nums *= (cnt + 1); //这个要通过一个公式求得,见下方
    }
    return nums;
}
/*
 * 720 = 2^4 * 3^2 * 5 ,故通过排列组合可得因子个数为(4+1)*(2+1)*(1+1)=30
 */
 
int main()
{
    int n;
    while(cin >> n) {
        vector<int> factor = getFactor2(n);
for(auto &elem : factor)
            cout << elem << " ";
        cout << endl << "素数个数为：" << getFactorNums(n) << endl;
    }
    return 0;
}

//注：一般情况下，说数的因子，并不考虑负数，所以上面并未考虑负数的情况
