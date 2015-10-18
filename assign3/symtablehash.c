/*_________symtablehash.c__________
 *
 * assignement 3
 * hy255
 * Tsolis Dimitris
 * email: tsolis@csd.uoc.gr
 *
 *    This file contains an implementation of a symbol table
 * using hash table as a data structure.
 *    The hash function parses the input key an produces
 * a valid brucket of the hash table to put in.If tow or more 
 * keys fall in the same bucket then they are added in a list.
 * 
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"logic.h"
#include"symtable.h"
#include<assert.h>
#define INIT_NHASH 509
#define MAXHASH 65521
#define MULTIPLIER 31



/*-------SymTable_T------------
 *   Is the type of SymTable Object.
 * 
 *
 */

struct SymTable{
	struct hash_list **HASH_TABLE;
	unsigned int NHASH;
	unsigned int HA;
};


/*-------hash_list---------
 *   Is the type of the hash table chains (list)
 * when 2 or more objects has the same hash code
 * are inserted in the same list in each bucket.
 * 
 */
struct hash_list{
	char *key;
	void *value;
	struct hash_list *next;
	struct hash_list *previous;
};

/*A static array that contains the amounts of resizign the array in each case*/
static unsigned int HASH_AMOUNT[]={1021,2053,4093,8191,16381,32771,65521};

/*===========hash===========
 * 	The hash function that returns the hash code 
 * depending on the key passed as an argument.
 *
 * This function was copied from the book "The Practise of Programming".
 *
 *
 * */
unsigned int hash(const char *key,unsigned int NHASH){
	unsigned int h;
	unsigned char *p;

	h=0;
	for(p=(unsigned char *)key;*p!='\0';p++){
		h=MULTIPLIER*h+*p;
	}
	return h%NHASH;
}





/*
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ~		   Helping Functions			    ~
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

/*__________list_length__________
 * 	Returns the length of the list passed as an argument.
 */
unsigned int list_length(struct hash_list *Head){
	struct hash_list *i;
	unsigned int length=0U;
	for(i=Head;i!=NULL;i=i->next){
		length+=1U;
	}
	return length;
}

/*_____________Resize_HT_______________
 *	Resizes a Hash table that belongs to a SymTable object.
 *
 * */
void Resize_HT(SymTable_T oSymTable){
	struct hash_list **newHT,**oldHT;
	struct hash_list *hp,*next;
	
	unsigned int i,oldNHash=oSymTable->NHASH;
	
	oldHT=oSymTable->HASH_TABLE;
	oSymTable->NHASH=HASH_AMOUNT[oSymTable->HA];
	oSymTable->HA+=1U;
	
	newHT=(struct hash_list **)calloc(oSymTable->NHASH,sizeof(struct hash_list *));
	oSymTable->HASH_TABLE=newHT;
	
	for(i=0U;i<oldNHash;i++){
		if(oldHT[i]!=NULL){
			for(hp=oldHT[i];hp!=NULL;hp=next){
				next=hp->next;
				SymTable_put(oSymTable,hp->key,hp->value);
				free(hp->key);
				free(hp);	
			}
		}
	}
	free(oldHT);
	
	
	
}






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
	SymTable_T a=(SymTable_T)malloc(sizeof(struct SymTable));
	a->HASH_TABLE=(struct hash_list **)calloc(INIT_NHASH,sizeof(struct hash_list*));
	a->NHASH=INIT_NHASH;
	a->HA=0;
	return a;
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
	struct hash_list **HT;
	unsigned int i,NHash;
	struct hash_list *tmp,*next;
	
	if(oSymTable==NULL){
		return;
	}

	HT=oSymTable->HASH_TABLE;
	NHash=oSymTable->NHASH;

	for(i=0U;i<NHash;i++){
		if(HT[i]!=NULL){
			for(tmp=HT[i];tmp!=NULL;tmp=next){
				next=tmp->next;
				free(tmp->key);
				free(tmp);
			}
		}
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
unsigned int SymTable_getLength(SymTable_T oSymTable)
{	
	unsigned int i,Nbind=0U,NHash;
	struct hash_list **HashTable;
	
	assert(oSymTable);

	NHash=oSymTable->NHASH;
	HashTable=oSymTable->HASH_TABLE;
	
	for(i=0U;i<NHash;i++){
		if(HashTable[i]!=NULL){
			Nbind+=list_length(HashTable[i]);/*Nbind cotains the number of
							  *bindings.In every loop the 
							  *length of the list of valid 
							  *hash table buckets is added.
							  */
		}
	}
	return Nbind;
	
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
 */

int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
	unsigned int hpos,length;
	struct hash_list *head,*newNode,*i;
	
	assert(oSymTable);
	assert(pcKey);
	length=SymTable_getLength(oSymTable);
	
	if(SymTable_contains(oSymTable,pcKey)==TRUE){
		return FALSE;
	}
	
	/*This is the case when we must resize the hash table
	 */
	if(length>=(oSymTable->NHASH-1U) && oSymTable->NHASH<MAXHASH){
		Resize_HT(oSymTable);
	}
	
	hpos=hash(pcKey,oSymTable->NHASH);/*hpos:the hash position of pcKey*/
	/*printf("%u:%s\n",hpos,pcKey);*/
	
	head=oSymTable->HASH_TABLE[hpos];/*head holds the first node of the list 
					  *at position hpos of the hash table.
					  */
	
	if(list_length(head)>0U){/*Case the list hash elements*/
		newNode=(struct hash_list*)malloc(sizeof(struct hash_list));
		if(newNode==NULL){
			printf("Not enough memory!\n");
			return FALSE;
		}
		newNode->value=(void *)pvValue;
		newNode->key=(char*)malloc((strlen(pcKey)+1)*sizeof(char));
		if(newNode->key==NULL){
			printf("Not enough memory!\n");
			return FALSE;
		}
		strcpy(newNode->key,pcKey);

		
		for(i=head;i->next!=NULL;i=i->next){
			;
		}
		
		i->next=newNode;
		newNode->previous=i;
		newNode->next=NULL;
		return TRUE;
	}
	else{/*Case the list do not have elements*/
		head=(struct hash_list*)malloc(sizeof(struct hash_list));
		if(head==NULL){
			printf("Not enough memory!\n");
			return FALSE;
		}
		head->value=(void *)pvValue;
		head->key=(char*)malloc((strlen(pcKey)+1)*sizeof(char));
		if(head->key==NULL){
			printf("Not enough memory!\n");
			return FALSE;
		}
		strcpy(head->key,pcKey);
		head->next=NULL;
		head->previous=NULL;
		oSymTable->HASH_TABLE[hpos]=head;
		return TRUE;
	}
	
	return FALSE;
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
 *
 *
 */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
	unsigned int hpos;
	struct hash_list *head,*i;
	
	assert(oSymTable);
	assert(pcKey);

	hpos=hash(pcKey,oSymTable->NHASH);
	head=oSymTable->HASH_TABLE[hpos];
	if(head!=NULL){
		for(i=head;i!=NULL;i=i->next){
			if(strcmp(i->key,pcKey)==0){
				if(i==head && i->next==NULL){/*If the node with the appro-
							      *preate key is the only in
							      * the list
							      */
					free(i->key);	      
					free(i);
					oSymTable->HASH_TABLE[hpos]=NULL;

				}
				else if(i->next==NULL){/*If the node is the head */
					i->previous->next=NULL;
					i->previous=NULL;
					free(i->key);
					free(i);
				}
				else if(i->previous==NULL){/*If the node is the Tail*/
					i->next->previous=NULL;
					head=i->next;
					oSymTable->HASH_TABLE[hpos]=head;
					free(i->key);
					free(i);
				}
				else{/*If the node is an insider*/
					i->previous->next=i->next;
					i->next->previous=i->previous;
					i->next=NULL;
					i->previous=NULL;
					free(i->key);
					free(i);
					
				}
			}
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
	unsigned int hpos;
	struct hash_list *i;
	
	assert(oSymTable);
	assert(pcKey);

	hpos=hash(pcKey,oSymTable->NHASH);

	for(i=oSymTable->HASH_TABLE[hpos];i!=NULL;i=i->next){
		if(strcmp(i->key,pcKey)==0){
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
	unsigned int hpos;
	struct hash_list *i;
	void *retVal=NULL;/*Holds the return value of the binding*/
	
	assert(oSymTable);
	assert(pcKey);

	hpos=hash(pcKey,oSymTable->NHASH);
	if(oSymTable->HASH_TABLE[hpos]!=NULL){
		for(i=oSymTable->HASH_TABLE[hpos];i!=NULL;i=i->next){
			if(strcmp(i->key,pcKey)==0){
				retVal=i->value;
			}	
		}
	}
	return retVal;
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
	unsigned int i;
	struct hash_list *head,*tmp;
	
	
	assert(oSymTable);
	assert(pfApply);
	
	for(i=0U;i<oSymTable->NHASH;i++){
		if((head=oSymTable->HASH_TABLE[i])!=NULL){
			for(tmp=head;tmp!=NULL;tmp=tmp->next){
				(pfApply)((const char*)tmp->key,tmp->value,(void *)pvExtra);	
			}
		}
	}
	
	
}

