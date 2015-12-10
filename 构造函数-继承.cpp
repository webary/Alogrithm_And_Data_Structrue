#include<iostream>
using namespace std;

class Base
{
public:
	Base() {
		cout << "none argument !!" << endl;
	}
	Base(int x1) : x(x1) {
		cout<<"Base x1"<<endl;
	}
	virtual ~Base() {};

	virtual void func(int x) {
		cout << "Base : " << x << endl;
	}
private:
	int x;
};

class Derive : public Base
{
public:
	Derive () : Base(100) {}
	virtual ~Derive () {}

	//该处覆盖了Base的func方法；
	void func(int x) {
		cout << "Derive : " << x << endl;
	};

private:
	int dint;
};

int main()
{
	Derive derive;
	Derive::Base(2);      //::表示编译期间确定的调用，不是对象的调用，故可以编译通过；
	// derive.Base();          //该语句会出错，表示不能继承父类的构造函数，对比下一个语句；
	derive.func(2);         //该语句可编译通过，表示能继承父类的普通成员函数。
	Base &pBase = derive;
	pBase.func(1);
	return 0;
}
