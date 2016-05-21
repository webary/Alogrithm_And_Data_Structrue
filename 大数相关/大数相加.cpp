#include <stdio.h>
#include <string.h>
const int size = 1000000;
void reverse(char *arr,int len) {
    char temp;
    int i;
    for(i= 0; i < len / 2; i++) {
        temp = arr[i];
        arr[i] = arr[len-i-1];
        arr[len-i-1] = temp;
    }
}
void add1(char * s1,char * s2) {
	int i,len[2],max,min;
	char * str[2]={s1,s2};
    for(i=0; i<2; i++) {
        len[i] = strlen(str[i]);
        reverse(str[i],len[i]);
    }
    if(len[0]>len[1]) {
        max=0,min=1;
    } else {
        max=1,min=0;
    }
    for(i=0; i<len[max]; i++) {
        str[1][i] = (str[1][i] + str[0][i])%48;
        if(str[1][i] > 9) {
            str[1][i] %= 10;
            str[1][i+1] += 1;
        }
        str[1][i] += 48;
    }
    str[1][i] += 48;
    if(str[1][i]=='0')
        i--;
    for(; i>=0; i--)
        printf("%c",str[1][i]);
    printf("\n");
}
void add2(char * s1,char * s2) {
    char sum[size];
    int len1,len2,i,max,min;
    len1 = strlen(s1);
    reverse(s1,len1);
    len2 = strlen(s2);
    reverse(s2,len2);
    memset(sum,'0',size-1);
    sum[size-1]=0;
    if(len1>len2) {
        max=len1,min=len2;
    } else {
        max=len2,min=len1;
    }
    for(i=0; i<min; i++) {
        sum[i] += s1[i] + s2[i] - 96;
        if(sum[i] > 57) {
            sum[i] -= 10;
            sum[i+1] += 1;
        }
    }
    for(i=min; i<max; i++) {
        sum[i] += s1[i] + s2[i] - 48;
        if(sum[i] > 57) {
            sum[i] -= 10;
            sum[i+1] += 1;
        }
    }
    for(i=max; sum[i]!='0'; i++);
    for(i-=1; i>=0; i--)
        printf("%c",sum[i]);
    printf("\n");
}
int main() {
    char str[2][size];
    int len[2],i,max,min;
    while(scanf("%s%s",str[0],str[1])==2) {
    	add1(str[0],str[1]);
    //	add2(str[0],str[1]);
		for(i=0;i<2;i++) memset(str[i],0,size);
    }
    return 0;
}
