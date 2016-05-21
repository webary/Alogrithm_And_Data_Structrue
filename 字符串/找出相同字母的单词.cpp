/************************************************************************
程序实现对一个文件中的所有单词进行处理，找出含有相同字母组合的单词。
其实应当对一个大的单词表进行处理。
1.分析出每个单词是要排序的，这样才能标识出这个字母组合
2.其实对处理一个字典的单词表比较有意义
3.数据用的《算法4》网站上的数据，wordlist，2MB的一个文件
/************************************************************************/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <ctime>
using namespace std;
//用stl算法里的sort函数形成signature
string sortIt(string str)
{
    sort(str.begin(), str.end());
    return str;
}
int main()
{
    string filename;
    ifstream fin;
    do {
        cout << "Please input the file path: ";
        getline(cin, filename);
        fin.open(filename.c_str());
        if (fin.is_open())
            break;
        cout << "can't open the file,please try again!" << endl;
    } while (1);

    string word;
    map<string, set<string> > myTree;
    clock_t t1 = clock();
    while (fin >> word) //读入速度约48万/秒
        myTree[sortIt(word)].insert(word);
    fin.close();
    cout << "time elapsed: " << clock() - t1 << "ms, press enter to show all:\n";
    cin.get();
    for (auto& it : myTree) {
        cout << it.first << ":\t";
        for (auto& set_it : it.second)
            cout << set_it << "\t";
        cout << endl;
    }
    cin.get();
    return 0;
};
