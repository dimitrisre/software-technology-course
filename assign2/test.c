#include<stdio.h>
#include"mystring.h"
#include<string.h>

int main(){
	char a[]="string1";
	char b[30];
	char c[30];
	char d[30];
	
	printf("Enter a string:");
	scanf("%s",b);
	printf("The length of b:%s is:%u\n",b,ms_length(b));
	printf("The length of \"\" is:%u\n",ms_length(""));
	printf("A copy of b:%s is c:%s\n",b,ms_copy(c,b));
	printf("The concat of b:%s and a:%s is b:%s\n",b,a,ms_nconcat(b,a,3));
	/*ms_copy(NULL,NULL)*//*Energopoihse gia na elegkseis to apotelesma*/
	printf("Enter a pattern:");
	scanf("%s",d);
	printf("a=%s\nb=%s\nc=%s\nd=%s\n",a,b,c,d);
	printf("The results of the following comparisons are:\n");
	printf("a?a=%d\n",ms_compare(a,a));
	printf("a?b=%d\n",ms_compare(a,b));
	printf("b?c=%d\n",ms_compare(b,c));
	printf("The pattern d:%s in teh string b:%s starts from %s\n",d,b,ms_seasrch(b,d));
	
	return 0;

}

