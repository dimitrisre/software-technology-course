/*__________mymalloc.c_____________
 * assignement 4
 * hy255
 * Tsolis Dimitris
 * email: tsolis@csd.uoc.gr
 *
 * This file contains an implementation of the functions of 
 * module mymalloc.This module provides all the necessary functions
 * for memmory management.This module request from the system for 
 * a chunk of memory(==5000000 bytes) and uses this chunk of memmory 
 * for further management without requesting any more memmory from 
 * the system.
 *
*/




#include<stdlib.h>
#include<stdio.h>
#include"mymalloc.h"

/* This structure is the node from the free list. 
 *The nodes contain the memory chunks that are free  
 *and ready for further allocation.
 *
 *
*/
struct info{
	unsigned long size;
	struct info *next_free;
	void *mem;
}*head;/*Head is a pointer to the first node of the free list*/

/*Is a pointer to the initial memory area */
static void *initial_blc=NULL;

/*Is the initial size of the memory that this module will manage*/
static unsigned long InitialSz=5000000;/*(==5MB)*/

/*=======Helping Function=========*/

/*_______________Function:Init_mem________________  
 *   When this module is used for te first time every allocation
 * function checks if the initial memory is NULL, meaning that 
 * the memory has not been initialized.Then this function is called and
 * the initial memory block takes its space.Also the head of the free list
 * is allocated on that initial memory block.
*/
void Init_mem(){

	initial_blc=malloc(InitialSz);
	head=(struct info *)initial_blc;
	
	head->size=InitialSz-sizeof(struct info);
	head->next_free=NULL;
	head->mem=(char*)initial_blc+sizeof(struct info);
	
}

/*____________Function:inter_alloc_____________
 *  This function allocates space on the free list for internal
 * use or for an external request for memory.
 * The way this memory will be used depends on the function that calles 
 * that internal function.
 *
 *
*/


void *inter_alloc(size_t size){
	struct info *i;
	char *chunk;


	if(initial_blc==NULL){
		Init_mem();
	}
	for(i=head;i!=NULL;i=i->next_free){
		if(i->size>=size){
			chunk=(char *)i->mem;
			i->mem=(void *)(chunk+size);
			i->size-=size;
			
			return (void *)chunk;
						
		}
	}
	return NULL;
	
}

/*____________Function:New_Node_____________
 *  Allocates a new node for the free list on 
 * the free list.Takes a pointer to the memory that will 
 * be deallocated.Initializes the node to point to the free 
 * memory block and saves the size of that block.
 *
*/
struct info * New_Node(void *ptr){
	struct info *new;
	char *p=(char *)ptr;
	
	new=(struct info *)inter_alloc(sizeof(struct info));
	new->size=*(unsigned long *)(p-sizeof(unsigned long*));
	new->mem=p-sizeof(unsigned long);
	return new;	
}


/*__________Function:concate_block__________
 *   This function chekcs if the memory area pointed with the 
 * ptr can be concated somewhere in the free list with an block of memory.
 * If the block can be concated concates it and returns 1 indicting success
 * else returns 0 indicating failure.This function is used by myfree to avoid 
 * external fragmentation.
 *
*/
int concate_block(void *ptr){
	struct info *i;
	char *tmp,*tmp1;
	unsigned long*size;
	
	tmp=(char *)ptr;
	tmp-=sizeof(unsigned long);
	size=(unsigned long *)tmp;
	
	for(i=head;i!=NULL;i=i->next_free){
		tmp1=(char *)i->mem;
		if(tmp1==tmp+(*size)+sizeof(unsigned long)+1){
			i->size+=(*size);
			i->mem=ptr;
			return 1;
		}
	}
	return 0;
}









/*<<<<<<<<<<Function Implementation>>>>>>>>>>>*/


/*_______Function: mymalloc______
 * This function returns a pointer to a newouly
 *allocated area of memory that is size bytes long.
 *
 *Arguments:
 *		-The size of the memory area to allocate
 *
 *Returns:
 *		-A pointer to that area of memory.
 *
 *
*/
void *mymalloc(size_t size){
	char *mem_alloc;
	unsigned long* header_size;


	mem_alloc=(char*)inter_alloc(size+sizeof(unsigned long));

	if(mem_alloc==NULL){
		return NULL;
	}
	header_size=(unsigned long *)mem_alloc;
	
	*header_size=size;
	mem_alloc+=sizeof(unsigned long);
	return (void *)mem_alloc;

	
	
}


/*_________Function: mycalloc____________
 * This function allocates memory for an array of 
 *nelem each of it is elsize size.The elements are 
 *initialized to zeros
 *
 *Arguments:
 *		-size_t nelem: Is the number of elements of the array.
 *		-size_t elsize: Is the size of each element in the array.
 *Returns:
 *		-a pointer to the newouly allocated memmory.
*/
void *mycalloc(size_t nelem,size_t elsize){
	char *mem_alloc;
	char *i;
	unsigned long* header_size;

	mem_alloc=(char *)inter_alloc(nelem*elsize+sizeof(unsigned long));
	if(mem_alloc==NULL){
		return NULL;
	}
	header_size=(unsigned long *)mem_alloc;
	*header_size=nelem*elsize;

	mem_alloc+=sizeof(unsigned long);
		
	for(i=mem_alloc;i-mem_alloc<nelem*elsize;i+=1){
		*i=0;
	}
	return (void*)mem_alloc;
}



/*___________Function: myrealloc_____________
 * Changers the size of the block pointed by ptr 
 *to size bytes and returns apointer to the new block.
 *The contents will be unchanged if teh were contained 
 *in the area of the previous memory chunk.
 *
 *Arguments:
 *		-void *ptr: Is the pointer to the memory 
 *			    that should be resized.
 *		-size_t size: Is the new size of the memory 
 *			      pointed by ptr
 *
 *Returns:
 *		-a pointer to the resized memory area.
 *
 *
*/

void *myrealloc(void *ptr,size_t size){
	char *new_area,*tmp=ptr,*ntmp;
	unsigned long i,*psize,*nsize;

	psize=((unsigned long *)(tmp-sizeof(unsigned long)));
	if(*psize>size+sizeof(unsigned long)){
		new_area=tmp+(*psize)-size-sizeof(unsigned long);
		nsize=(unsigned long *)new_area;
		*nsize=*psize-size-sizeof(unsigned long);
		*psize=size;
		myfree(new_area);
		return ptr;
		
	}
	else{
		new_area=(char *)inter_alloc(size+sizeof(unsigned long));
		if(new_area==NULL){
			return NULL;
		}
		nsize=(unsigned long *)new_area;
		*nsize=size;
		new_area+=sizeof(unsigned long);
		
		
		for(i=0u,ntmp=new_area;i<*psize;tmp++,ntmp++,i++){
			*ntmp=*tmp;
		}
		myfree(ptr);
		return new_area;
	}
}



/*__________Function: myfree___________
 * This function frees the memory previously allocated with mymalloc, 
 *myrealloc,mycalloc.After myfree is executed the memory pointed by
 *ptr is available for further allocation.
 *
 *Arguments:
 *		-void *ptr: Points to a memory chunk previously 
 *			    allocated with the allocation functions provided
 *			    by this module.
 *Returns:
 *		-
*/

void myfree(void *ptr){
	struct info *i,*new=NULL,*tmp;
	char *p1,*p2=ptr;
	
	if(concate_block(ptr)==1){
		return;
	}
	for(i=head;i!=NULL;i=i->next_free){
		p1=(char *)i->mem;
		if(p2<p1){
			if(i==head){
				new=(struct info *)New_Node(ptr);
				new->next_free=head;
				head=new;
				break;
			}
			else{
				new=(struct info *)New_Node(ptr);
				new->next_free=i;
				tmp->next_free=new;	
				break;
			}
		}
		tmp=i;
	}	
	
	if(i==NULL && new==NULL){
		new=(struct info *)New_Node(ptr);
		new->next_free=NULL;
		tmp->next_free=new;
	}

}
