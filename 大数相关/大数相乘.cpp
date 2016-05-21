#include <cstring>
#include <iostream>
using namespace std;

char* bigNumMultiply(const char *a, const char *b)
{
    if(a == NULL || b == NULL)
        return NULL;
    int len_a = strlen(a), len_b = strlen(b);
    static char res[1000]; //定义为静态用于返回后仍有效
    int value[1000] = {0}, i, j; //中间计算结果(未进位前的数)可能比较大,用int存
    for (i = 0; i < len_a; i++)
        for (j = 0; j < len_b; j++)
            value[i + j + 1] += (a[i] - '0') * (b[j] - '0');
    for (i = len_a + len_b - 1; i >= 0; i--) // 这里实现进位操作
        if (value[i] > 9) {
            value[i - 1] += value[i] / 10; //大于9则进位
            value[i] %= 10; //变为字符的数字
        }
    for(i = 0; value[i] == 0; ++i) //跳过前面的0
        ;
    for(j = i; i < len_a + len_b; ++i) //加上'0'得到字符版的数字
        res[i - j] = value[i] + '0';
    res[i - j] = 0; //标志字符串结束
    return res;
}

int main()
{
    char a[500], b[500];
    while(cin >> a >> b) {
        cout << bigNumMultiply(a, b) << endl;
    }
    return 0;
}
