#include<stdio.h>
#include"mymalloc.h"
#include<stdlib.h>

struct str_ma{
	int any;
	double b;
	char c;
}*pstr_ma;
int main(){
	int *inta;
	int i;
	pstr_ma=(struct str_ma*)mymalloc(/*sizeof(struct str_ma)*/4000900);
	pstr_ma->any=12;
	pstr_ma->b=13;
	pstr_ma->c='d';
	printf("sizeof(struct str_ma)=%u\n",sizeof(struct str_ma));
	printf("sizeof(unsigned long)=%u\n",sizeof(unsigned long));

	printf("%d,%f,%c\n\n",pstr_ma->any,pstr_ma->b,pstr_ma->c);
	myfree(pstr_ma);
	
	pstr_ma=(struct str_ma*)mymalloc(sizeof(struct str_ma));
	pstr_ma->any=15;
	pstr_ma->b=16;
	pstr_ma->c='e';
	
	printf("%d,%f,%c\n",pstr_ma->any,pstr_ma->b,pstr_ma->c);
	myfree(pstr_ma);
	
	if(mymalloc(5000000)==NULL){
		printf("Error.Out of memory!!\nThe request you made for 5MB is not available\n");
	}
	
	inta=(int *)mycalloc(30,sizeof(int));
	printf("inta's size=%u\n",sizeof(*inta));
	for(i=0;i<30;i++){
		inta[i]=i;
		printf("inta[%d]=%d\n",i,inta[i]);
	}
	printf("\n\n");

	inta=(int *)myrealloc(inta,10*sizeof(int));
	printf("inta's size=%u\n",sizeof(*inta));	
	for(i=0;i<10;i++){
		
		printf("inta[%d]=%d\n",i,inta[i]);
	}
	printf("\n\n");
	inta=(int *)myrealloc(inta,40*sizeof(int));
	printf("inta's size=%u\n",sizeof(*inta));	
	for(i=0;i<40;i++){
		
		printf("inta[%d]=%d\n",i,inta[i]);
	}
	
	myfree(inta);
	return 0;
}
