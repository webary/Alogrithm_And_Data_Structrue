#include <stdio.h>
#include <ctype.h>
#include <string.h>

main()
{
    int x; //数组下标变量，详情看代码
    int char_count[26]; //26个字母出现字数的统计
    for( x= 0; x < 26; x++)
        char_count[x] = 0;
    char str[1024];
    while(gets(str)) {
        for(x = 0; str[x]!=0; ++x)
            if(isalpha(str[x])) //是字母则统计
        ++char_count[(str[x]-'a')%32];
        //找出出现频率最高的字母
        int max=0;    //出现频率最高的字母序号
        for(x = 0; x < 26; x++)
            if(char_count[x] > char_count[max])
                max = x;
        printf("出现在频繁的字母是 %c ,共出现了%d次\n\n", max+'a',char_count[max]);
		memset(str,0,sizeof(str));
		memset(char_count,0,sizeof(char_count));
    }
    return 0;


}
