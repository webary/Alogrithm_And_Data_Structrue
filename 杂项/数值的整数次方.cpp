/** 题目要求：
 实现函数double Power(double base, int exponent),求base的enponent次方。
 不得使用库函数,不需要考虑大数问题。
**/
/** 解题思路：
 1.最直接的方法是用循环累乘。但是这种方法效率很低，因此改为递归求解
   请留意这里所说的递归效率更高是因为用了一个数学公式，但是通常情况
   下循环的解法要比递归效率高(常见的是求斐波那契数列)。
 2.特殊情况考虑:
    (1)指数可能为0或负数(为负数时要求倒数)
    (2)底数可能为0
    (3)底数和指数可能同时为0(此时切忌盲目求倒数-防止除0操作)
    (4)为了进一步提高效率,用>>替换除以2,用(n&1)替换取余
**/
#include<stdio.h>
//判断两个浮点数是否相等
bool equal(double num1, double num2)
{
    if (num1 - num2 < 1e-7 && num1 - num2 > -1e-7)
        return 1;
    return 0;
}
bool gb_InvalidPara = 0;    //标识参数是否有误
//求取指数为自然数的乘方
double powerWithUnsignedE(double base, unsigned exponent)
{
    if (exponent == 0)
        return 1.0;
    if (exponent == 1)
        return base;
    double result = powerWithUnsignedE(base, exponent >> 1);
    if ((exponent & 1) == 0) //幂是偶数,注意不要掉了括号
        return result * result;
    return result * result * base;
}
//求一个数的任意整数次幂
double Power(double base, int exponent)
{
    gb_InvalidPara = 0;
    if (equal(base, 0.0)) { //底数为0
        if (exponent == 0) //指数为0
            gb_InvalidPara = 1;
        return 0.0;
    }
    if (exponent >= 0)
        return powerWithUnsignedE(base, exponent);
    return 1.0 / powerWithUnsignedE(base, -exponent);
}

int main()
{
    double base;
    unsigned exp;
    puts("请输入底数和指数：");
    while (scanf("%lf%d", &base, &exp) == 2)
        printf("%g ^ %d = %s%.15g\n", base, exp, gb_InvalidPara ? "参数无效！0_" : "", Power(base, exp));
    return 0;
}
