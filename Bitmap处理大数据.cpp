/**
	给定40亿个unsigned int的整数，没排过序的；
	然后再给一个数，如何快速判断这个数是否在那40亿个数当中
**/
#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;
const unsigned SIZE = 512000000;//512兆静态存储区可处理40.96亿数据

class Bitmap {
    typedef struct Byte {
        unsigned char bit8;
		static const unsigned char mask[9];//用来取得一个字节每一位的辅助数组
        Byte()
        {
            bit8 = 0;
        }
        //设置该位，就是存储该数
        void set1(unsigned at)
        {
            bit8 |= mask[at];
        }
        //读取该位是否有数
        bool get1(unsigned at)
        {
            return bit8 & mask[at];
        }
    } Byte;
    Byte *m_byte;
    unsigned m_size;
public:
    Bitmap(unsigned _size)
    {
        m_byte = new Byte[(_size+7)/8];
        m_size = _size;
    }
    virtual ~Bitmap()
    {
        delete[] m_byte;
        m_size = 0;
    }
    //存储一个数据
    bool push(unsigned data)
    {
        if(data>=m_size)
            return false;
        m_byte[data/8].set1(data%8);
        return true;
    }
    //读取一个数据是否存在
    bool find(unsigned data)
    {
        return data>=m_size ? 0 : m_byte[data/8].get1(data%8);
    }
    //返回能存储的数据个数
    unsigned size()
    {
        return m_size;
    }
    //重载运算符实现常用功能
    //存储一个数据
    bool operator>>(unsigned data)
    {
        return push(data);
    }
    //读取一个数据是否存在
    bool operator<<(unsigned data)
    {
        return find(data);
    }
    //访问到某个数据块
    Byte& operator[](unsigned i)
    {
        if(i>=m_size/8)
            throw "index out of range";
        return m_byte[i];
    }
};
const unsigned char Bitmap::Byte::mask[9] = {0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};//用来取得一个字节每一位的辅助数组

int main()
{
    Bitmap bitmap(8*SIZE);//可以存储40+亿数据
    ifstream file("in.txt");
    unsigned read, i=0, t1 = clock();
    for(i=0; i<SIZE; ++i)
        if(file>>read)
            bitmap>>read;
        else
            break;
    file.close();
    cout<<"共存储"<<i/10000<<"W 数据, "<<"耗时: "<<clock()-t1<<"ms"<<endl;
    t1 = clock();
    for(i=0; i<1000000; ++i)
        if(bitmap<<i)
            ;
    cout<<"访问"<<i/10000<<"W 数据共耗时: "<<clock()-t1<<"ms"<<endl;
    cout<<"请输入需要检索的数据:"<<endl;
    while(cin>>read) {
        if(bitmap<<read)
            cout<<"已存储"<<read<<endl;
        else
            cout<<"Error: 未存储"<<read<<endl;
    }
    return 0;
}
