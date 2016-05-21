#include <stdio.h>
#include <ctype.h>
int main()
{
    for (char str[1024] = {0}; gets(str);) {
        int char_count[26] = {0}, x; //26个字母出现字数的统计
        for (x = 0; str[x] != 0; ++x)
            if (isalpha(str[x]))  //是字母则统计
                ++char_count[(str[x] - 'a') % 32];
        int max = 0;    //出现频率最高的字母序号
        for (x = 0; x < 26; x++)
            if (char_count[x] > char_count[max])
                max = x;
        printf("出现最频繁的字母是 %c ,共出现了%d次\n\n", max + 'a', char_count[max]);
    }
    return 0;
}
