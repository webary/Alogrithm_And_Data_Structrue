#include<stdio.h>

int getNums(char* str,int *arr)
{
	int num=0,count=0;
	while(1) {
		if(*str>='0' && *str<='9') {
			num*=10;
			num+=*str-'0';
		} else if(num>0) {
			*arr++=num;
			count++;
			num=0;
		}
		if(*str=='\0') break;
		str++;
	}
	return count;
}

int main()
{
	char * str="sdf23432 edf354 54 dgfdg456 54678";
	int arr[10],total,i;
	total=getNums(str,arr);
	for(i=0; i<total; i++) {
		printf("%d ",arr);
	}
	return 0;
}
