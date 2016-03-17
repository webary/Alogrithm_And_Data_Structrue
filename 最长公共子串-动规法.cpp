//最长公共子串，动态规划实现
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//返回最长公共子串,如果有多个一样长的子串,都返回
string getLongestCommonString(const string &s, const string &t)
{
    int len_s = s.length(), len_t = t.length();
    //动归法主要是找到状态转移公式, 经常也会用到空间换时间的方法
    //这里就是定义一个二维vector存储中间状态
    vector<vector<string> >num(len_s, vector<string>(len_t));
    int maxlen = 0;
    string lcs;
    for(int i = 0; i < len_s; i++)
        for (int j = 0; j < len_t; j++)
            if(s[i] == t[j]) {
                if (i == 0 || j == 0)
                    num[i][j] = s[i];
                else
                    num[i][j] = num[i - 1][j - 1] + s[i];
                //找到当前局部最长子串,并记录最大长度
                if(num[i][j].length() > maxlen) { //有更长的串则替换当前最长
                    maxlen = num[i][j].length();
                    lcs = num[i][j];
                } else if(num[i][j].length() == maxlen) //可以保存多个最长串
                    lcs += "\n" + num[i][j];
            }
    return lcs; //返回最长公共子串
}
//返回两个串的最长公共子串的长度
int getLCSLength(const string &s, const string &t)
{
    int len_s = s.length(), len_t = t.length();
    vector<vector<int> >num(len_s, vector<int>(len_t, 0));
    int maxLen = 0;
    for(int i = 0; i < len_s; i++)
        for (int j = 0; j < len_t; j++)
            if(s[i] == t[j]) {
                if (i == 0 || j == 0)
                    num[i][j] = 1;
                else
                    num[i][j] = num[i - 1][j - 1] + 1;
                if(num[i][j] > maxLen) //有更长的串则替换当前最长
                    maxLen = num[i][j];
            }
    return maxLen; //返回最长公共子串
}

int main()
{
    string s, t;
    cout << "请输入两个字符串s, t: ";
    while(cin >> s >> t) {
        cout << "最长公共子串为: " << getLongestCommonString(s, t) << endl
             << "最长公共子串长度为: " << getLCSLength(s, t) << endl;
        cout << "\n请输入两个字符串s, t: ";
    }
    return 0;
}
