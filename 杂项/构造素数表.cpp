#include<stdio.h>
#include<cmath> //sqrt()
#include<ctime> //clock()

//最简单的素数求法,效率较低
bool isPrime(int n)
{
    if (n < 2)
        return 0;
    int k = sqrt(n), i;
    for (i = 2; i <= k; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int prime[670000];  //1000万以内的素数个数为66万+;
//数组较大，需要设置为全局，否则可能栈溢出
int getPrimeNum(int N = 1000000)
{
    prime[0] = 2;
    int m, c = 1, i, j; //c记录当前素数个数
    for (i = 3; i <= N; i += 2) { //这里只判断奇数，跳过偶数
        m = (int)sqrt(i + 0.1); //加0.1是为了防止部分编译器对sqrt()函数的调用报出不明确的错误
        for (j = 0; prime[j] <= m; ++j)
            if (i % prime[j] == 0)
                break;
        if (prime[j] > m)
            prime[c++] = i;
    }
    return c;
}
int main()
{
    int count, N[4] = {100000, 1000000, 5000000, 10000000};
    for (int i = 0; i < 4; i++) {
        clock_t start = clock();//保存开始计算时的时间
        count = getPrimeNum(N[i]);  //得到N[i]以内的素数表并返回素数个数
        printf("%4d 万以内素数个数：%6d, 计算用时：%4d毫秒\n",
               N[i] / 10000, count, clock() - start);
    }
    return 0;
}
