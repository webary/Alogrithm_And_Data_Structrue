#include<iostream>
#include<time.h>
#include<windows.h>
/*
  斐波那契数列
   H(1)=H(0)=1;
   H(N)= H(N-1)+H(N-2);
*/
using namespace std;

/* 普通版普通版 */
int feibona(int ac)
{
    if (ac == 0|| ac ==1)  return 1;
    int f1 = 1, f2 = 1;
    for(int i=1;i<ac;++i)
	{
		f2 += f1;
		f1 = f2-f1;
	}
    return f2;//feibona(ac-1) +feibona(ac-2);
}

/* 使用元编程 完全特化版 方法如下*/
template <int N>
struct data {
    //采用枚举
    enum { res = data<N - 1>::res + data<N - 2>::res };
};

template <>
struct data<1> {
    //采用枚举
    enum { res = 1L };
};

template <>
struct data<0> {
    //采用枚举
    enum { res = 1L };
};


int main(int argc, char * args[])
{
    time_t  a ,b;
    a = clock(); //开始记录时间
    cout << data<46L>::res << endl;
    b = clock(); //开始记录时间
    system("echo 采用元编程所消耗的时间");
    cout << (double)(b - a) / CLK_TCK<<"s"<<endl;
    a = clock();
    cout << feibona(46L) << endl;
    b = clock();
    system("echo 采用普通的算法所消耗的时间");
    cout << (double)(b - a) / CLK_TCK << "s" << endl;
    cin.get();
    return 0;
}
