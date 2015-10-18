/*_________symtable.h__________
 *
 * assignement 3
 * hy255
 * Tsolis Dimitris
 * email: tsolis@csd.uoc.gr
 *
 *
 *   Is the interface of a symbol table ADT.
 * A symbol table object is a collection o mapping between 
 * a key and a value.A key is a string that corresponds to 
 * only one value.
 *   This file contains the declaration of functions that 
 * belong to the contract of the ADT symbol table.Also defines
 * the type of the SymTable object.
 *
 */


#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_




/*-------SymTable_T------------
 *   Is the type of SymTable Object.
 * 
 *
 */

typedef struct SymTable * SymTable_T;





/*-----------Function:SymTable_new-----------
 *    Returns a new SymTable object that contains no 
 * mappings (no keys,no values).
 * 
 * Arguments:
 *		-
 * Returns:
 *		SymTable_T: A new symbol table object.
 */
SymTable_T SymTable_new(void);





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
void SymTable_free(SymTable_T oSymTable);





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
unsigned int SymTable_getLength(SymTable_T oSymTable);





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
int SymTable_put(SymTable_T oSymTable, const char *pcKey,
		 const void *pvValue);






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
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);







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
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);







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

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);







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
				   void *pvExtra), const void *pvExtra);

#endif
