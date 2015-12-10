#include<cstring>
#include<fstream>
#include<iostream>
#include<cstdlib>
using namespace std;

int main()
{
	ofstream file("in.txt");
	unsigned read, count=0;
	for(count=0;count<30000;++count){
		file<<rand()<<endl;
	}
	file.close();
	return 0;
}
