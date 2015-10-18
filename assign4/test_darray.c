#include<stdio.h>
#include"darray.h"

int compare(const void *,const void *);
int Equals(const void *,const void *);
	
int main(){
	DArray_T any_array;
	int i,plast,j;
	
	any_array=DArray_new(10,sizeof(double));
	for(i=0;i<10;i++){
		DArray_put(any_array,9-i,&i);
	}

	for(i=0;i<DArray_getNumElts(any_array);i++){
		printf("any_array[%d]=%d\n",i,*(double*)DArray_get(any_array,i));
	}
	
	printf("The elements size is:%d \n",DArray_getEltSize(any_array));
	printf("The Current maxsize of the dynamic array is:%d \n",DArray_getNumElts(any_array));
	j=132;
	plast=DArray_append(any_array,&j);
	for(i=plast+1;i<DArray_getNumElts(any_array);i++){
		DArray_put(any_array,i,&i);
	}
	
		
	for(i=0;i<DArray_getNumElts(any_array);i++){
		printf("any_array[%d]=%d\n",i,*(double *)DArray_get(any_array,i));
	}

	printf("The elements size is:%d \n",DArray_getEltSize(any_array));
	printf("The Current maxsize of the dynamic array is:%d \n",DArray_getNumElts(any_array));
/*	DArray_sort(any_array,compare);
	
	for(i=0;i<DArray_getNumElts(any_array);i++){
		printf("any_array[%d]=%d\n",i,*(double *)DArray_get(any_array,i));
	}
*/
	
	printf("132 is in the index %d of the dynamic table\n",DArray_search(any_array,&j,Equals));
	return 0;
	
	
	

}

int Equals(const void *a,const void *b){
	if(a!=NULL || b!=NULL){
		if((*(double *)a)==(*(double*)b)){
			return 0;
		}
	}
	return -1;
}

int compare(const void *a,const void *b){

	if(*(double*)a<*(double*)b)
		return -1;
	else if(*(double*)a>*(double*)b)
		return 1;

	return 0;
}
