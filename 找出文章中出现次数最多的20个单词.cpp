#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <unordered_map>
using namespace std;

typedef string keyType; //单词
typedef int valueType; //词频
typedef unordered_map<keyType, valueType> MapType; //这里可以改为map测试时间性能

//将map按值排序
template<typename T1, typename T2>
void sortMapByValue(const MapType& tMap, vector<pair<T1, T2> >& tVector)
{
    tVector.reserve(tMap.size()); //将ap中的数据复制到vector中并排序
    for (auto &elem : tMap)
        tVector.push_back(make_pair(elem.first, elem.second));
    sort(tVector.begin(), tVector.end(), [](pair<T1, T2>& x, pair<T1, T2>& y) {
        return x.second > y.second; //保证按词频排序
    });
}
//从文章中读取每一行并拆分单词保存到map中
void splitWordsAndSave(MapType& myMap, istream& inStream)
{
    string line, word, alpha(53, '-'); //将数组先初始化为连字符
    string::size_type pos = 0, posEnd = 0;
    for (int i = 0; i < 26; ++i) { //[0,25]为'A'-'Z',[26,51]为'a'-'z'
        alpha[i] = 'A' + i;
        alpha[i + 26] = 'a' + i;
    }
    while (getline(inStream, line)) {
        pos = 0;
        while (pos != string::npos) {
            pos = line.find_first_of(alpha, pos);
            if (string::npos == pos)
                break;
            posEnd = line.find_first_not_of(alpha, pos);
            word = line.substr(pos, posEnd - pos);
            if (word[0] != '-')
                ++myMap[word];  //保存该单词
            pos = posEnd;
        }
    }
}

int main()
{
    MapType wordCount;
    keyType tmpKey;
    time_t t_start = clock();
    ifstream fin("artical.txt");
    splitWordsAndSave(wordCount, fin); //如果想手工输入将参数改为(wordCount,cin)
    cout << wordCount.size() << " words save to map took "
         << clock() - t_start << "ms" << endl;
    vector<pair<keyType, valueType> > vec;
    sortMapByValue(wordCount, vec);
    cout << "sort took " << clock() - t_start << "ms" << endl << "top 20 words:\n";
    for (size_t i = 0; i < 20 && i < vec.size(); ++i)
        cout << vec[i].first << " \t" << vec[i].second << endl;
    cin.get();
    return 0;
}
