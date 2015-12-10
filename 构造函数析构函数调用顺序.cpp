#include<iostream>
using namespace std;

class Base1{
public:
	Base1(){
		cout<<"Base1()"<<endl;
		m_i = -1;
	};
	Base1(int i){
		cout<<"Base1():"<<i<<endl;
		m_i = i;
	}
	~Base1(){
		cout<<"~Base1():"<<m_i<<endl;
	}
private:
	int m_i;
};

class Derived : public Base1{
public:
	Derived():Base1(),b2(2),b1(1){
		cout<<"Derived()"<<endl;
	}
	Derived(int i){
		cout<<"Derived():"<<i<<endl;
	}
	~Derived(){
		cout<<"~Derived()"<<endl;
	}
	Base1 b1,b2;
};

int main()
{
	Derived d;
	return 0;
}
