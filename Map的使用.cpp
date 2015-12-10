#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
typedef string keyType;
typedef int valueType;
typedef unordered_map<keyType,valueType> MapType;//這里可以将unordered_map改为map测试

template<typename T1,typename T2>
int  cmp(const pair<T1,T2>& x,const pair<T1,T2>& y) {
    return x.second > y.second;
}

template<typename T1,typename T2>
void  sortMapByValue(const MapType& tMap,vector<pair<T1,T2> >& tVector) {
    tVector.reserve(tMap.size());
    for(auto itor = tMap.begin(); itor != tMap.end(); ++itor)
        tVector.push_back(make_pair(itor->first,itor->second));
    sort(tVector.begin(),tVector.end(),cmp<T1,T2>);
}

int main(int argc,char* argv[]) {
    MapType chCount;
    keyType tmpKey;
    ifstream fileIn;
    if(argc>1)
		fileIn.open(argv[1]);
	else
		fileIn.open("in.txt");
	int t_start = clock();
    while(fileIn>>tmpKey)
		++chCount[tmpKey];
	fileIn.close();
	cout<<"保存至map中耗时: "<<clock()-t_start<<"ms"<<endl;
    //for(auto iter = chCount.begin(); iter != chCount.end(); iter++)
    //   cout<<iter->first<<" "<<iter->second<<endl;

    vector<pair<keyType,valueType> > sortVec;
    sortMapByValue(chCount,sortVec);
	cout<<"排序耗时"<<clock()-t_start<<"ms\n"<<endl<<"排序后结果如下："<<endl;
    for(auto iter = sortVec.begin(); iter != sortVec.end(); iter++)
        cout<<iter->first<<" "<<iter->second<<endl;
	cin.get();
	return 0;
}
