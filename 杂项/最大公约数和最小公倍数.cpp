#include <iostream>
#include <stdio.h>
using namespace std;

int maxYue (int a,int b) {		//求余法
    int r=a%b;
    while(r) {
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}
int maxYue2(int a,int b) {		//相减法
    while(a!=b) {
        if(a>b)
            a-=b;
        else
            b-=a;
    }
    return a;
}
int maxYue3(int a,int b) {		//递归法
    return b?maxYue3(b,a%b):a;
}
int minBei (int a,int b) {
    int max = a > b ? a : b ,min = a < b ? a : b ,i;
    for(i=1; i * max % min != 0; i++);
    return i*max;
}
int minBei2(int a,int b) {
    return a*b/maxYue(a,b);
}
/* 下面是c++版输入输出
int main(){
	int m,n;
	cout<<"enter two integers : ";
	while(cin>>m>>n){
		cout<<m<<"和"<<n<<"的最大公约数是 : "<<maxYue(m,n)<<" "<<maxYue2(m,n)<<" "<<maxYue3(m,n)<<endl;
		cout<<m<<"和"<<n<<"的最小公倍数是 : "<<minBei(m,n)<<" "<<minBei2(m,n)<<endl;
		cout<<"\nenter two integers : ";
	}
	return 0;
}*/
int main() {
    int m,n;
    printf("enter two integers : ");
    while(scanf("%d%d",&m,&n)==2) {
        printf("%d和%d的最大公约数是 : %d,%d,%d\n",m,n,maxYue(m,n),maxYue2(m,n),maxYue3(m,n));
        printf("%d和%d的最小公倍数是 : %d,%d\n",m,n,minBei(m,n),minBei2(m,n));
        printf("enter two integers : ");
    }
    return 0;
}
