#include"symtable.h"
#include<stdio.h>
#include"logic.h"
#include<string.h>
#include<stdlib.h>

void Print_cur(const char *,void *,void *);

int main(){
	void *i;
	void(*func)(const char *,void *,void *)=Print_cur;
	int a1=100,b=90,c=80,d=70,e=60;
	SymTable_T a;
	a=SymTable_new();

	i=&a1;
	SymTable_put(a,"string1",i);
	i=&b;
	SymTable_put(a,"string2",i);
	i=&c;
	SymTable_put(a,"string3",i);
	/*i=&d;
	*SymTable_put(a,"string4",i);*/
	i=&e;
	printf("can insert:%d\n",SymTable_put(a,"string5",i));
	printf("length:%u\n",SymTable_getLength(a));
	SymTable_put(a,"string6",i);
	printf("length:%u\n",SymTable_getLength(a));
	printf("contains string1:%d\n",SymTable_contains(a,"string1"));
	printf("contains string7:%d\n",SymTable_contains(a,"string7"));

	
	printf("contains:");
	printf(" %d ",*(int *)SymTable_get(a,"string1"));
	printf(" %d ",*(int *)SymTable_get(a,"string2"));
	printf(" %d ",*(int *)SymTable_get(a,"string3"));
	printf(" %d ",*(int *)SymTable_get(a,"string5"));
	printf(" %d ",*(int *)SymTable_get(a,"string6"));
	printf("\n");
	SymTable_remove(a,"string1");
	SymTable_remove(a,"string2");
	SymTable_remove(a,"string3");
	SymTable_remove(a,"string4");
	SymTable_remove(a,"string5");

	printf("length:%u\n",SymTable_getLength(a));
	
	/*Resize_HT(a);*/
	
	SymTable_free(a);
	a=SymTable_new();
	
	i=&a1;
	SymTable_put(a,"other1",i);
	i=&b;
	SymTable_put(a,"other2",i);
	i=&c;
	SymTable_put(a,"other3",i);
	i=&d;
	SymTable_put(a,"other4",i);
	i=&e;

	printf("can insert:%d\n",SymTable_put(a,"other5",i));
	printf("length:%u\n",SymTable_getLength(a));
	SymTable_map(a,func,NULL);

			
	return 0;
}


void Print_cur(const char* key,void *value,void *pvExtra){
	printf("----------------------------------------------\n");
	printf("--      %s       --           %d      --\n",(char*)key,*(int*)value);
	printf("----------------------------------------------\n");
}
