#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

typedef string keyType; //单词
typedef int valueType; //词频
typedef map<keyType, valueType> MapType; //這里可以将unordered_map改为map测试
//排序过程中使用的比较函数,即保证按词频排序
template<typename T1, typename T2>
int cmp(const pair<T1, T2>& x, const pair<T1, T2>& y)
{
    return x.second > y.second;
}
//将map按值排序
template<typename T1, typename T2>
void sortMapByValue(const MapType& tMap, vector<pair<T1, T2> >& tVector)
{
    tVector.reserve(tMap.size()); //将ap中的数据复制到vector中并排序
    for(auto &elem : tMap)
        tVector.push_back(make_pair(elem.first, elem.second));
    sort(tVector.begin(), tVector.end(), cmp<T1, T2>);
}

int main(int argc, char* argv[])
{
    MapType wordCount;
    keyType tmpKey;
    ifstream fileIn;
    if(argc > 1) //如果是从命令行打开,并输入了参数,则接收命令行的参数
        fileIn.open(argv[1]);
    else  //否则直接从"words.txt"读取输入
        fileIn.open("words.txt");
    int t_start = clock();
    while(fileIn >> tmpKey) //不断读取一个key,存入wordCount
        ++wordCount[tmpKey];
    fileIn.close();
    cout << wordCount.size() << "个单词保存至map中耗时: " << clock() - t_start
         << "ms" << endl;
    vector<pair<keyType, valueType> > sortVec;
    sortMapByValue(wordCount, sortVec);
    cout << "排序耗时" << clock() - t_start << "ms\n" << endl << "top 20：\n";
    for(int i = 0; i < 20; ++i)
        cout << sortVec[i].first << " \t" << sortVec[i].second << endl;
    cin.get();
    return 0;
}
