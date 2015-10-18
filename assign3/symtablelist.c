/*__________symatablelist.c____________
 *
 * assignement 3
 * hy255
 * Tsolis Dimitris
 * email: tsolis@csd.uoc.gr
 *
 *	This is an implementation of symbol table ADT.
 * The implementation of the ADT uses list as data representation 
 * of the ADTs fields.
 * 	A double linked list holds the key of the binding,
 * the value of the binding,and the pointers to the next and
 * previous nodes of the list.
 *	Also a pointer to Tail holds the last valid position of
 * the list.
 *
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"logic.h"
#include"symtable.h"
#include<assert.h>

/*-------SymTable_T------------
 *   Is the type of SymTable Object.
 * 
 *
 */

struct SymTable{
	char *key;
	void *value;
	struct SymTable *Tail;
	struct SymTable *next;
	struct SymTable *previous;
};




/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ~                Function Implementation                  ~
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

/*-----------Function:SymTable_new-----------
 *    Returns a new SymTable object that contains no 
 * mappings (no keys,no values).
 * 
 * Arguments:
 *		-
 * Returns:
 *		SymTable_T: A new symbol table object.
 */
SymTable_T SymTable_new(void){

	SymTable_T newNode=(SymTable_T)malloc(sizeof(struct SymTable));
	newNode->next=NULL;
	newNode->previous=NULL;
	newNode->key=NULL;
	newNode->value=NULL;
	newNode->Tail=newNode;
	return newNode;	
}

/*--------------Function:SymTable_free---------------
 *	Frees the memory previous allocated for the symbol table object.
 * If the symbol table object is null then the function does nothing.
 *
 * Arguments:
 *		SymTable_T oSymTable: The symbol table object to
 *					free its memory.
 *
 * Returns:
 *		-
 * Assertions:
 * 		If the symbol table object is NULL then exit the function.
 */
void SymTable_free(SymTable_T oSymTable){
	SymTable_T tmp,next,head;
	
	if(oSymTable==NULL){
		return;
	}
	head=oSymTable->next;
	for(tmp=head;tmp!=NULL;tmp=next){
		next=tmp->next;
		free(tmp->key);
		free(tmp);
	}
	free(oSymTable);

}





/*---------------Function:SymTable_getLength-----------------
 *	Returns the number of mappings in the symbol table.
 *
 * Argumenets:
 *		SymTable_T oSymTable: The symbol table whose mappings are
 *					counted.
 * Returns:
 *		unsigned int: The number of bindings.
 *
 * Assertions:
 *		Symbol table must not be null
 */
unsigned int SymTable_getLength(SymTable_T oSymTable){
	unsigned int size=0U;
	SymTable_T tmp,head;

	assert(oSymTable);

	head=oSymTable->next;
	
	for(tmp=head;tmp!=NULL;tmp=tmp->next){
		size+=1U;
	}
	return size;
}





/*-----------Function: SymTable_put----------------
 *	If there is no mapping with the key pcKey in the symbol table
 * puts the new mapping in the table and returns TRUE=1 else does not 
 * manipulate the symbol table and returns FALSE=0.
 *
 * Arguments:
 *		-SymTable oSymTable:The SymTable that the binding is putted in.
 *		-const char *pcKey: The key of the that describes the value.
 *		-const void *pvValue: The value to be inserted.
 *
 * Returns:
 *		-An integer between values 0 and 1 (FALSE and TRUE) indicating
 *		 if the value was inserted or it was already in.
 * 
 * Assertions:
 *		-Stops the programm if the SymTable object is NULL.
 *		-The programm also stops when the pcKey is NULL.
 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
	
	SymTable_T newNode=NULL;
	assert(pcKey);
	assert(oSymTable);
	
	if(SymTable_contains(oSymTable,pcKey)==TRUE){
		return FALSE;
	}	
	else{	
		newNode=(SymTable_T)malloc(sizeof(struct SymTable));
		newNode->key=(char *)malloc((strlen(pcKey)+1)*sizeof(char));
		strcpy(newNode->key,pcKey);
		newNode->value=(void *)pvValue;
		newNode->Tail=NULL;
		newNode->previous=oSymTable->Tail;
		oSymTable->Tail->next=newNode;
		newNode->next=NULL;
		oSymTable->Tail=newNode;
	}
	return TRUE;
}






/*---------------Function: SymTable_remove-----------------
 *	If the binding pcKey points to exists on the symbol table deletes it 
 * and returns 1 (TRUE) else does not manipulate the table and returns 0 FALSE.
 *
 * Arguments:
 *		-SymTable_T oSymTable: The symbol table that the binding is deleted from
 *		-const char *pcKey: The key of the value to be deleted
 *
 * 
 * Returns:
 *		-An integer indicating if the value was deleted or not.
 *		 The integer has values between 0 and 1 (FALSE and TRUE)
 *
 * Assertions:
 *		-Stops the programm if the symbol table object is NULL.
 *		-Also if the pcKey is NULL the programm is aborted.
 *
 *
 */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
	SymTable_T tmp;
	SymTable_T head;
	
	assert(oSymTable);
	assert(pcKey);

	head=oSymTable->next;
	
	if(SymTable_contains(oSymTable,pcKey)==FALSE){
		return FALSE;
	}
	for(tmp=head;tmp!=NULL;tmp=tmp->next){
		if(strcmp(tmp->key,pcKey)==0){
			if(tmp==oSymTable->Tail){
				tmp->previous->next=NULL;
				oSymTable->Tail=tmp->previous;
			}
			else{
				tmp->previous->next=tmp->next;
				tmp->next->previous=tmp->previous;
			}
			free(tmp->key);
			free(tmp);
			return TRUE;
		}
	}
	return FALSE;	
}







/*------------Function:SymTable_contains--------------
 * 	Checks if there is a binding withe specific key in the oSymTable.
 * If this function find one binding then returns 1 (TRUE) else 0 (FALSE).
 * 
 *  
 * Arguments:
 * 		-oSymTable: The symbol table to look in for the binding.
 * 		-The key to look for.
 * Returns:
 * 		-An integer (0 or 1)  indicating the success or failure 
 * 		  of searching of pcKey.
 *
 * Assertions:
 * 		-If oSymTable is NULL the programm is aborted
 * 		-If pcKey is NULL the programm is aborted
 */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
	SymTable_T tmp;
	SymTable_T head;

	assert(oSymTable);
	assert(pcKey);
	
	head=oSymTable->next;
	for(tmp=head;tmp!=NULL ;tmp=tmp->next){
		if(strcmp(tmp->key,pcKey)==0){
			return TRUE;
		}
	}
	
	return FALSE;

}







/*------------Function:SymTable_get--------------
 * 	Returns the binding from the oSymTable that has the specific pcKey
 * NULL if this binding does not exist.
 * 
 *  
 * Arguments:
 * 		-oSymTable: The symbol table to look in for the binding.
 * 		-The key whose binding is returned.
 * Returns:
 * 		-A reference of the binding.
 *
 * Assertions:
 * 		-If oSymTable is NULL the programm is aborted
 * 		-If pcKey is NULL the programm is aborted
 */

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
	
	SymTable_T tmp;
	SymTable_T head;
	
	assert(oSymTable);
	assert(pcKey);
	
	head=oSymTable->next;
	
	if(SymTable_contains(oSymTable,pcKey)==FALSE){
		return NULL;
	}
	for(tmp=head;tmp!=NULL;tmp=tmp->next){
		if(strcmp(tmp->key,pcKey)==0){
			return tmp->value;
		}
		
	}
	return NULL;
	
}







/*------------Function:SymTable_map--------------
 * 	Applies the function pfApply on all the bindings of the Symbol table
 * passing as an extra argument the pvExtra.
 * 
 *  
 * Arguments:
 * 		-oSymTable: The symbol table whose bindings 
 * 		 will parsed by the function pfApply
 * 		-pfApply: A pointer to the function applied 
 * 		 on the bindings of the symbol table.
 * 		-pvExtra: A pointer to the extra argument passed by to
 * 		 the apply function.
 * Returns:
 * 		-
 *
 * Assertions:
 * 		-If oSymTable is NULL the programm is aborted
 * 		-If pfApply is NULL the programm is aborted
 */

void SymTable_map(SymTable_T oSymTable,
		  void (*pfApply) (const char *pcKey, void *pvValue,
				   void *pvExtra), const void *pvExtra){

	SymTable_T tmp,head;
	
	assert(oSymTable);
	assert(pfApply);

	head=oSymTable->next;
	
	for(tmp=head;tmp!=NULL;tmp=tmp->next){
		(pfApply)((const char *)tmp->key,tmp->value,(void*)pvExtra);
	}
}
