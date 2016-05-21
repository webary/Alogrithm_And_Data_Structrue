#include <string.h>
#include <stdio.h>
#define MAXN 0X7000

int a[MAXN];

int main() {
	printf("%d\n",MAXN);
    int n,m,i,j,c,t;
    printf("Enter n(n>=2) :");
    while(1) {
        scanf("%d",&n);
        if(n>=2&&n<=3276) break;
        printf("must be 2<=n<=3276:");
    }
    a[0]=1;
    m=1;
    for(i=2; i<=n; i++) {
        for(c=0,j=0; j<m; j++) {
            t=a[j]*i+c;
            a[j]=t%10;
            c=t/10;
        }
        while(c) {
            a[m++]=c%10;
            c/=10;
        }
    }
    printf("%d! =\n",n);
    for(i=m-1; i>=0; i--) putchar(a[i]+'0');
    //getch();
    return 0;
}

