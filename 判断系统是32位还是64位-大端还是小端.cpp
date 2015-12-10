#include <stdio.h>

int main()
{
    int *a = NULL;
    printf("OS is %d位\n",8*sizeof(a));
    union ut {
        short s;
        char c;
    } u = {1};
	printf("%s\n",u.c == 0 ? "big enidan" : "little endian");

	struct test{
		short ss;
	}s = {1};
	printf("%s\n",*(char*)&s==0 ? "big enidan" : "little endian");
    return 0;
}
