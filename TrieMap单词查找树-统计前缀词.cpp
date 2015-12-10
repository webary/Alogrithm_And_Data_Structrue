#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

class TrieMap {
public:
    TrieMap();
    virtual ~TrieMap();
    //重载[]运算符，和map, unorder_map容器接口一样
    void push( const string& strKey );
    int getCountByPrefix(const string &prefix);
    int operator[](const string &prefix);
protected:
    typedef struct Node {
        char ch;  //当前结点存储的字符
        Node *Children[58] ;  //每个节点最多有58个子节点
        int num; //以此为前缀词的个数
        Node(char _ch=0,int n=0)
        {
            ch = _ch;
            memset( Children , 0 , sizeof( Children ) ) ;
            num = n;
        }
    } Node;
    Node * m_pRoot ;// 树根节点
    void deleteNode(Node * pNode); //删除一个结点及其子节点
};

TrieMap::TrieMap()
{
    m_pRoot = new Node() ;
}

TrieMap::~TrieMap()
{
    deleteNode(m_pRoot);
}
//删除节点及其子节点
void TrieMap::deleteNode(Node * pNode)
{
    if(pNode==NULL)
        return;
    for (int i = 0; i < 58; ++i) {
        if (pNode->Children[i] != 0) {
            deleteNode(pNode->Children[i]) ;
            pNode->Children[i] = 0;
        }
    }
    delete pNode;
    pNode = 0;
}
//插入一条记录
void TrieMap::push(const string& strKey)
{
    Node * pNode = m_pRoot;
    // 建立或者查找树路径
    for ( size_t i = 0 , sz = strKey.size() ; i < sz ; ++i ) {
        Node *&child = pNode->Children[strKey[i]-'A'];
        pNode = child;
        if (child == 0)
            pNode = child = new Node(strKey[i],1);
        else
            ++pNode->num;
    }
}
//查找以某个前缀开始的单词数
int TrieMap::getCountByPrefix(const string &prefix)
{
    Node *pNode = m_pRoot;
    for(size_t i = 0, sz = prefix.size() ; i < sz ; ++i) {
        pNode = pNode->Children[prefix[i]-'A'];
        if(pNode==NULL)
            return 0;
    }
    return pNode->num;
}

int TrieMap::operator[](const string &prefix)
{
    return getCountByPrefix(prefix);
}

int main()
{
    int n,m;
    TrieMap myTrie ;
    string word;
    cin>>n;
    while(n--) {
        cin>>word;
        myTrie.push(word);
    }
    cin>>m;
    while(m--) {
        cin>>word;
        cout<<myTrie[word]<<endl;
    }

    return 0;
}
