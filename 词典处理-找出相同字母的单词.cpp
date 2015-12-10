/************************************************************************/
/* 程序实现对一个文件中的所有单词进行处理，找出含有相同字母组合的单词。其实应当对一个大的单词表进行处理。
用处暂时没有，就是觉得好玩。网易公开课抽象编程中看到的。
1.分析出每个单词是要排序的，这样才能标识出这个字母组合
2.其实对处理一个字典的单词表比较有意义
3.数据用的《算法4》网站上的数据，wordlist，2MB的一个文件
*/
/************************************************************************/
#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include<ctime>
using namespace std;
//用stl算法里的sort函数形成signature，与上面的二选一
string sortIt(string str)
{
    sort(str.begin(),str.end());
    return str;
}
int main()
{
    string filename;
    ifstream fin;
    do{
		cout<<"Please input the file path: ";
		cin>>filename;
		fin.open(filename.c_str());
		if(fin.is_open())
			break;
		cout<<"can't open the file,please try again!"<<endl;
	}while(1);

    string word;
    map<string,set<string> > myTree;
    clock_t t1=clock();
    while(fin>>word) 	//读入速度约48万/秒
        myTree[sortIt(word)].insert(word);
    fin.close();
    cout<<"读入数据耗时: "<<clock()-t1<<endl<<"按enter键输出所有信息..."<<endl;
    cin.get();cin.get();
    for(auto iter = myTree.begin(); iter!=myTree.end(); iter++) {
        cout<<(*iter).first<<":\t";
        for(auto set_iter = iter->second.begin(); set_iter!=iter->second.end(); set_iter++)
            cout<<*set_iter<<"\t";
        cout<<endl;
    }
    cin.get();
    return 0;
};
