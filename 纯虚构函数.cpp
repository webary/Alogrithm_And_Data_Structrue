#include<iostream>
using namespace std;
class A
{
public:					//这里就不用protected了
	virtual ~A()=0    //它虽然是个纯虚函数，但是也可以被实现
	{ //这个语法很好很强大（完全是为了实现其接口类而弄的语法吧）
		cout<<" A: ~A()"<<endl;
	}
};
class B : public A
{
};
int main(int argc, char* argv[])
{
	B* p =new B;
	delete  p;
	A* p2 =new B;
	delete  p2;            //不用担心编译器报错了，因为此时A的析构函数是public
	return 0;
}
//result：
/*
 A: ~A()
 A: ~A()
*/
