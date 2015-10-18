/*__________mymalloc.h____________
 * Assignement 4 <--> hy255
 * Tsolis Dimitris
 * email: tsolis@csd.uoc.gr
 *
 *
 *   This interface contains the basic declaration for
 *the module mymalloc.
 *   The module mymalloc is for memmory management.It uses
 *an internal call of the malloc function the first time 
 *a programm uses this module for allocating a big piece
 *of memmory and then uses that for internal management.
 *
 *
*/

#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_

/*<--------Function Prototypes--------->*/

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
void *mymalloc(size_t size);




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
void *mycalloc(size_t nelem,size_t elsize);



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

void *myrealloc(void *ptr,size_t size);



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

void myfree(void *ptr);
#endif
