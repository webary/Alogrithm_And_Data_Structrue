#include<iostream>
using namespace std;

class Base {
public:
    virtual void f()
    {
        cout << "Base::f" << endl;
    }
    virtual void g()
    {
        cout << "Base::g" << endl;
    }
    virtual void h()
    {
        cout << "Base::h" << endl;
    }
    virtual ~Base() {}
};
class Base2 {
public:
    virtual void f()
    {
        cout << "Base::f" << endl;
    }
};

class Derived :  public Base {
public:
    void g()
    {
        cout << "Derived::g" << endl;
    }
    int getA()
    {
        return a;
    }
    virtual ~Derived() {}
private:
    int a;
};
//多重继承时，拥有两个虚函数表指针
class Derived2 : public Base2, Base {
public:
    void g()
    {
        cout << "Derived::g" << endl;
    }
};

int main()
{
    Base2 b2;
    cout << sizeof(Base) << " " << sizeof(Base2) << " "
         << sizeof(Derived) << " " << sizeof(Derived2) << endl;
    typedef void(*Fun)(void);
    Derived d;
    Base &b = d;
    cout << sizeof(b) << sizeof(d) << endl;
    Fun pFun = NULL;
    cout << "虚函数表地址：" << (int*)(&b) << endl;
    cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl;
    // Invoke the first virtual function
    pFun = (Fun) * ((int*) * (int*)(&b) + 0); // Base::f()
    pFun();
    pFun = (Fun) * ((int*) * (int*)(&b) + 1); // Derived::g()
    pFun();
    pFun = (Fun) * ((int*) * (int*)(&b) + 2); // Base::h()
    pFun();
    *((int*)(&b) + 1) = 555;
    cout << d.getA() << endl;
    return 0;
}
