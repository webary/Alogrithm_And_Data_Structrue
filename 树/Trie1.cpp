#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
struct node
{
    int next[26];
    int cnt;
    void init()
    {
        cnt=0;
        memset(next,-1,sizeof(next));
    }
}T[1000000];
int le;
void insert(char *s)
{
    int i=0,p=0;
    while(s[i]) //对单词的每个字母处理
    {
        int x=s[i]-'a';  //得到是第几个字母，0~25
        if(T[p].next[x]==-1)  //判断当前字母是否存储
        {
            T[le].init();  //如果没存储初始化这个字母
            T[p].next[x]=le++; //将总使用过的字母数加一，并把这个字母附给对应的字母后面
        }
        p=T[p].next[x];  //找到下一个字母位置
        T[p].cnt++; //这个字母为尾的单词数计数加一
        i++;
    }
}
void query(char *s)
{
    int i=0,p=0;
    while(s[i])
    {
        int x=s[i]-'a';
        if(T[p].next[x]==-1)
        {
            puts("0");
            return ;
        }
        p=T[p].next[x];
        i++;
    }
    printf("%d\n",T[p].cnt);
}
int main()
{
    int n,m;
    char str[20];
    while(~scanf("%d",&n))
    {
        le=1;
        T[0].init();
        while(n--)
        {
        scanf("%s",str);
        insert(str);
        }
        scanf("%d",&m);
        while(m--)
        {
        scanf("%s",str);
        query(str);
        }
    }
}
