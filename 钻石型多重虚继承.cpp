#include<iostream>
using namespace std;

class B
{
    public:
        int ib;
        char cb;
    public:
        B():ib(0),cb('B') {}

        virtual void f() { cout << "B::f()" << endl;}
        virtual void Bf() { cout << "B::Bf()" << endl;}
};
class B1 : virtual public B
{
    public:
        int ib1;
        char cb1;
    public:
        B1():ib1(11),cb1('1') {}

        virtual void f() { cout << "B1::f()" << endl;}
        virtual void f1() { cout << "B1::f1()" << endl;}
        virtual void Bf1() { cout << "B1::Bf1()" << endl;}

};
class B2: virtual public B
{
    public:
        int ib2;
        char cb2;
    public:
        B2():ib2(12),cb2('2') {}

        virtual void f() { cout << "B2::f()" << endl;}
        virtual void f2() { cout << "B2::f2()" << endl;}
        virtual void Bf2() { cout << "B2::Bf2()" << endl;}

};

class D : public B1, public B2
{
    public:
        int id;
        char cd;
    public:
        D():id(100),cd('D') {}

        virtual void f() { cout << "D::f()" << endl;}
        virtual void f1() { cout << "D::f1()" << endl;}
        virtual void f2() { cout << "D::f2()" << endl;}
        virtual void Df() { cout << "D::Df()" << endl;}

};


int main()
{
	cout<<sizeof(B)<<endl;
	cout<<sizeof(B1)<<endl;
	cout<<sizeof(B2)<<endl;
	cout<<sizeof(D)<<endl<<endl;

	typedef void (*Fun)(void);
	int** pVtab = NULL;
    Fun pFun = NULL;

    D dd;

    pVtab = (int**)&dd;
    cout << "[0] D::B1::_vptr->" << endl;
    pFun = (Fun)pVtab[0][0];
    cout << "     [0] ";    pFun(); //D::f1();
    pFun = (Fun)pVtab[0][1];
    cout << "     [1] ";    pFun(); //B1::Bf1();
    pFun = (Fun)pVtab[0][2];
    cout << "     [2] ";    pFun(); //D::Df();
    pFun = (Fun)pVtab[0][3];
    cout << "     [3] ";
    cout << pFun << endl;

    //cout << pVtab[4][2] << endl;
    cout << "[1] = 0x";
    cout <<  (int*)((&dd)+1) <<endl; //????

    cout << "[2] B1::ib1 = ";
    cout << *((int*)(&dd)+2) <<endl; //B1::ib1
    cout << "[3] B1::cb1 = ";
    cout << (char)*((int*)(&dd)+3) << endl; //B1::cb1

    //---------------------
    cout << "[4] D::B2::_vptr->" << endl;
    pFun = (Fun)pVtab[4][0];
    cout << "     [0] ";    pFun(); //D::f2();
    pFun = (Fun)pVtab[4][1];
    cout << "     [1] ";    pFun(); //B2::Bf2();
    pFun = (Fun)pVtab[4][2];
    cout << "     [2] ";
    cout << pFun << endl;

    cout << "[5] = 0x";
    cout << *((int*)(&dd)+5) << endl; // ???

    cout << "[6] B2::ib2 = ";
    cout << (int)*((int*)(&dd)+6) <<endl; //B2::ib2
    cout << "[7] B2::cb2 = ";
    cout << (char)*((int*)(&dd)+7) << endl; //B2::cb2

    cout << "[8] D::id = ";
    cout << *((int*)(&dd)+8) << endl; //D::id
    cout << "[9] D::cd = ";
    cout << (char)*((int*)(&dd)+9) << endl;//D::cd

    cout << "[10]  = 0x";
    cout << (int*)*((int*)(&dd)+10) << endl;
    //---------------------
    cout << "[11] D::B::_vptr->" << endl;
    pFun = (Fun)pVtab[11][0];
    cout << "     [0] ";    pFun(); //D::f();
    pFun = (Fun)pVtab[11][1];
    cout << "     [1] ";    pFun(); //B::Bf();
    pFun = (Fun)pVtab[11][2];
    cout << "     [2] ";
    cout << pFun << endl;

    cout << "[12] B::ib = ";
    cout << *((int*)(&dd)+12) << endl; //B::ib
    cout << "[13] B::cb = ";
    cout << (char)*((int*)(&dd)+13) <<endl;//B::cb
}
//²Î¿¼ÍøÖ·£ºhttp://blog.csdn.net/jiangnanyouzi/article/details/3721091
