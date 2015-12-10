#pragma once
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <cstring>
using namespace std ;

template< typename Value_t >
class TireMap {
public:
    typedef pair< string , Value_t > Kv_t ;
    struct Node {
        Kv_t * pKv ;
        Node* Children[256] ;
        Node() {
            pKv = 0;
            memset( Children , 0 , sizeof( Children ) ) ;
        }
        ~Node( ) {
            delete pKv ;
        }
    };

    TireMap();
    virtual ~TireMap() ;
    //重载[]  运算符。和 map , unorder_map 容器接口一样。
    Value_t& operator[]( const string& strKey ) ;
    // 清除保存的数据
    void clear() ;
    const list< Kv_t >& GetKeyValueList() const {
        return m_Kvs ;
    }

protected:
    // 删除一棵树
    static void DeleteTree( Node *pNode ) ;
protected:
    // 树根节点
    Node * m_pRoot ;
    // 映射的键值列表
    list< Kv_t > m_Kvs ;
};

template< typename Value_t >
TireMap<Value_t>::TireMap() {
    m_pRoot = new Node() ;
}

template< typename Value_t >
TireMap<Value_t>::~TireMap() {
    //clear( ) ;
    //delete m_pRoot ;
}

template< typename Value_t >
void TireMap<Value_t>::clear() {
    for ( int i = 0 ; i < 256 ; ++i ) {
        if ( m_pRoot->Children[ i ] != 0 ) {
            DeleteTree( m_pRoot->Children[ i ] ) ;
            m_pRoot->Children[ i ] = 0 ;
        }
    }
    m_Kvs.clear( ) ;
}

template< typename Value_t >
void TireMap<Value_t>::DeleteTree( Node * pRoot ) {
    // BFS 删除树
    stack< Node* > stk ;
    stk.push( pRoot ) ;
    for ( ; stk.size( ) > 0 ; ) {
        Node * p = stk.top() ;
        stk.pop( ) ;
        // 扩展
        for ( int i = 0 ; i < 256 ; ++i ) {
            Node* p2 = p->Children[ i ] ;
            if ( p2 == 0 )
                continue;
            stk.push( p2 ) ;
        }
        delete p ;
    }
}

template< typename Value_t >
Value_t& TireMap<Value_t>::operator[]( const string& strKey ) {
    Node * pNode = m_pRoot ;
    // 建立或者查找树路径
    for ( size_t i = 0 , size = strKey.size( ) ; i < size ; ++i ) {
        const char& ch = strKey[ i ] ;
        Node*& Child = pNode->Children[ ch ] ;
        if ( Child == 0 )
            pNode = Child = new Node() ;
        else
            pNode = Child ;
    }
    // 如果没有数据字段的话，就生成一个。
    if ( pNode->pKv == 0 ) {
        m_Kvs.push_back( Kv_t( strKey , Value_t() ) ) ;
        pNode->pKv = &*( --m_Kvs.end( ) ) ;
    }
    return pNode->pKv->second ;
}

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>
//#include "TireMap.h"
using namespace std ;

#define FOR(it,var) for(auto it = var.begin();it!=var.end();++it)
// 随机生成 Count 个随机字符组合的“单词”
template< typename StringList_t >
int CreateStirngs( StringList_t& strings , int Count ) {
    int nTimeStart , nElapsed ;
    nTimeStart = clock( ) ;
    strings.clear( ) ;
    for ( int i = 0 ; i < Count ; ++i ) {
        int stringLen = 5 ;
        string str ;
        for ( int j = 0 ; j < stringLen ; ++j ) {
            char ch = 'a' + rand( ) % ( 'z' - 'a' + 1 ) ;
            str.push_back( ch ) ;
        }
        strings.push_back( str ) ;
    }
        strings.push_back( "abcde" ) ;

    nElapsed = clock( ) - nTimeStart ;
    return nElapsed ;
}

// 创建 Count 个整型数据。同样创建这些整型对应的字符串
template< typename StringList_t , typename IntList_t >
int CreateNumbers( StringList_t& strings , IntList_t& Ints , int Count ) {
    strings.clear( ) ;
    Ints.clear( ) ;

    for ( int i = 0 ; i < Count ; ++i ) {
        int n =rand( ) % 0x00FFFFFF ;
        char sz[ 256 ] = { 0 } ;
        sprintf(sz,"%d",n);

        strings.push_back( sz ) ;
        Ints.push_back( n ) ;
    }

    return 0 ;
}

// Tire 正确性检查
string Check( const unordered_map< string , int >& Right , const TireMap< int >& Tire ) {
    string strInfo = "Tire 统计正确" ;

    const auto& TireRet = Tire.GetKeyValueList( ) ;
    unordered_map< string , int > ttt ;
    //for ( auto kv = TireRet.front();kv!=TireRet.end();++kv )
    FOR(kv,TireRet) {
        ttt[ kv->first ] = kv->second ;
    }

    if ( ttt.size( ) != Right.size( ) ) {
        strInfo = "Tire统计有错" ;
    } else {
        FOR (kv, ttt) {
            auto it = Right.find( kv->first )  ;
            if ( it == Right.end( ) ) {
                strInfo = "Tire统计有错" ;
                break ;
            } else if ( kv->second != it->second ) {
                strInfo = "Tire统计有错" ;
                break ;
            }
        }
    }

    return strInfo ;

}

// 统计模板函数。可以用map , unordered_map , TrieMap 做统计
template< typename StringList_t , typename Counter_t >
int Count( const StringList_t& strings , Counter_t& Counter ) {
    int nTimeStart = clock() ;
    FOR (str,strings) {
        ++Counter[*str];
    }
    return clock( ) - nTimeStart;
}

int main( int argc , char* argv[ ] ) {
    map< string , int > ElapsedInfo ;
    int nTimeStart , nElapsed ;

    // 生成50000个随机单词
    list< string > strings ;
    nElapsed = CreateStirngs( strings , 500000 ) ;
    //ElapsedInfo[ "生成单词 耗时" ] = nElapsed  ;

    // 用 map 做统计
    map< string , int > Counter1 ;
    nElapsed = Count( strings , Counter1 ) ;
    ElapsedInfo[ "统计单词 用map 耗时" ] = nElapsed  ;

    // 用 unordered_map 做统计
    unordered_map< string , int > Counter2 ;
    nElapsed = Count( strings , Counter2 ) ;
    ElapsedInfo[ "统计单词 用unordered_map 耗时" ] =  nElapsed  ;

    // 用 Tire 做统计
    TireMap< int > Counter3 ;
    nElapsed = Count( strings , Counter3 ) ;
    ElapsedInfo[ "统计单词 用Tire 耗时" ] = nElapsed  ;
    cout<<Counter3["abcde"]<<endl;

    // Tire 统计的结果。正确性检查
    string CheckRet = Check( Counter2 , Counter3 ) ;

    // 用哈希表统计整形数字出现的次数
    // 与 用Tire统计同样的整形数字出现的次数的 对比
    // 当然，用Tire统计的话，先要把那整形数据转换成对应的字符串的表示。

    list< int > Ints ;
    CreateNumbers( strings , Ints , 500000 ) ;
    unordered_map< int , int > kivi ;
    nTimeStart = clock();
    FOR(num , Ints ) {
        ++kivi[ *num ] ;
    }
    nElapsed = clock( ) - nTimeStart ;
    ElapsedInfo[ "统计数字 unordered_map 耗时" ] = nElapsed  ;

    //Counter3.clear( ) ; 这句话非常耗时。因为要遍历树逐个delete树节点。树有可能会非常大。所以我注释掉
    nElapsed = Count( strings , Counter3 ) ;
    ElapsedInfo[ "统计数字 用Tire 耗时" ] = nElapsed  ;

    FOR(it,ElapsedInfo) {
        cout<<it->first<<" : "<<it->second<<endl;
    }

    return 0;
}
