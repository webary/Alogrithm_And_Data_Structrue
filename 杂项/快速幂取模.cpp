#include <iostream>
using namespace std;

bool gb_InvalidPara = 0; //[1]
///普通方法求 a^b
double pow(double a, int b)
{
    gb_InvalidPara = 0;  //[2]
    if(a < 1e-5 && a > -1e-5) { //[3]
        if(b <= 0) //[4]
            gb_InvalidPara = 1;
        return 0; //[5]
    }
    double ans = 1;
    int exponent = b >= 0 ? b : -b; //[6]
    for(int i = 0; i < exponent; ++i) //[7]
        ans *= a;
    return b >= 0 ? ans : 1 / ans; //[8]
}
/** 解析
 * [1]:用一个全局bool变量标识pow函数计算结果是否有效,只有0^0无效
 * [2]:大多数情况都是有效的,所以先标记结果有效,无效时重新赋值
 * [3]:判断底数是否为0,注意浮点数判等方式
 * [4]:底数和指数同为0时,0^0无效,标记结果状态为无效
 * [5]:只要底数为0就返回0
 * [6]:指数可能为正,0,负,如果为负数,则a^b转化为求1/(a^(-b))
 * [7]:利用循环不断累乘计算结果
 * [8]:结合第6步完成指数不同符号的情况
**/

///用递归快速求取 a^b
//求取指数为自然数的乘方
double powerWithUnsignedE(double a, unsigned exponent)
{
    if(exponent == 0) //[1]
        return 1.0;
    double result = powerWithUnsignedE(a, exponent >> 1); //[2]
    if(exponent & 1)    //[3]
        return result * result * a;
    return result * result;
}
double quickPow_recursive(double a, int b)
{
    gb_InvalidPara = 0;  //[4]
    if(a < 1e-5 && a > -1e-5) { //[5]
        if(b == 0) //[6]
            gb_InvalidPara = 1;
        return 0; //[7]
    }
    unsigned exponent = b >= 0 ? b : -b; //[8]
    if(exponent >= 0)
        return powerWithUnsignedE(a, exponent);
    return 1.0 / powerWithUnsignedE(a, -exponent); //[9]
}
/** 解析
 * [1]:指数为0时直接返回1(注:能运行到这里说明底数已经不为0)
 * [2]:求得a^(e/2),exponent >> 1是exponent/2的快速版本
 * [3]:判断指数是否为奇数,是则需要多乘一次底数,因为e/2会向下取整
 * [4]:大多数情况都是有效的,所以先标记结果有效,无效时重新赋值
 * [5]:判断底数是否为0,注意浮点数判等方式
 * [6]:指数也为0时,0^0无效,标记状态为无效
 * [7]:只要底数为0就返回0
 * [8]:指数可能为正,0,负,如果为负数,则a^b转化为求1/(a^(-b))
 * [9]:如果指数小于0,则按照上一步的公式计算结果
**/

///非递归快速求取 a^b :快速幂算法
double quickPow(double a, int b)
{
    gb_InvalidPara = 0;  //[1]
    if(a < 1e-5 && -a < 1e-5) { //[2]
        if(b == 0) //[3]
            gb_InvalidPara = 1;
        return 0; //[4]
    }
    double ans = 1;
    unsigned exponent = b >= 0 ? b : -b;  //[5]
    while(exponent > 0) {  //[6]
        if(exponent & 1)  //[7]
            ans *= a;
        a *= a;  //[8]
        exponent >>= 1;  //[9]
    }
    return b >= 0 ? ans : 1 / ans;  //[10]
}
/** 解析
 * [1]:大多数情况都是有效的,所以先标记结果有效,无效时重新赋值
 * [2]:判断底数是否为0,注意浮点数判等方式
 * [3]:指数也为0时,0^0无效,标记状态为无效
 * [4]:只要底数为0就返回0
 * [5]:指数可能为正,0,负,如果为负数,则a^b转化为求1/(a^(-b))
 * [6]:如果指数仍大于0,继续累乘
 * [7]:if(exponent % 2 == 1) 即指数为奇数时,结果乘以该位的权重
 * [8]:权重增加
 * [9]:exponent = exponent / 2 即指数除以2
 * [10]:结合第5步计算最终结果
**/

///快速幂取模算法: 求取 a^b mod c (a>0; c>0; a,b可能很大)
unsigned quickPowMod(unsigned a, unsigned b, unsigned c)
{
    unsigned ans = 1;
    for(a %= c; b > 0; b >>= 1) {
        if(b & 1)
            ans = (ans * a) % c;
        a = (a * a) % c;
    }
    return ans;
}
/** 解析:该算法涉及到了取模运算,所有参数均为正整数.
 * 利用公式(a * b) % c = ((a%c)*(b%c))%c
 * (a^b)%c = (a*(a^(b-1))%c = ( (a%c)*((a^(b-1))%c) )%c ...
 * 因此在快速幂的基础上,每一步都使用取模就可以得到快速幂取模算法
**/
int main()
{
    cout << pow(2, 1000) << endl;
    cout << quickPow(2, 1000) << endl;
    return 0;
}
