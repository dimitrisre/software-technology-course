#include<stdio.h>
#include<stdlib.h>


int main(){
	char *name=(char *)malloc(100*sizeof(char));

	name=lltostr(12000066,name);
	printf("name=%s\n",name);
	return 0;
}
