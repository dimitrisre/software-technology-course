/*________________mystring.h_________________
 * assignement 1
 * hy255
 * Tsolis Dimitris
 * email:tsolis@csd.uoc.gr
 * 
 * This module contains the basic interface of all string
 * manipulation functions and their definitions.
 * In order to use this library include it in any C 
 * programm and just link all the .obj files of the
 * functions together with your main function.
 * 
 * 
 */

#include<stddef.h> /*Includes the declaration of the <size_t> type
		    *used by these functions.
		    */
		   
#include<assert.h> /*Used for checking whether the strings passed like arguments 
		   *are null or not.
		   */

/*--------Function: ms_length---------
 *  Retunrs the length of the string passed sa an argument.
 *
 *  Arguments:
 *  		-const char *:The string to find its length
 *  Returns:
 *  		-size_t :The unsigned integer representing the length
 *
 *  Assertions:
 *  	-Checks if the string argument is <NULL>.If true then exit
 *  	 printing an error message else continue.
 * 
 */
size_t ms_length(const char *);




/*---------Function: ms_copy----------
 *  Copies the second string argument to the first including the '\0' 
 *  character.
 *  	
 *  Arguments:
 *  		-char *: The destination string.Must be large enough to fit the
 *  			 source string.
 *  		
 *  		-const char*: The source string that will be copied
 *
 *  Return:
 *  		-char *: The pointer to start of the copied string (destination string "first arg")
 *
 *  Assertions:
 *  		-Checks if the string (destination,source) are NULL.
 *  		 If true exits the programm printing an error message. 
 *
 *
 */
char *ms_copy(char *,const char*);




/*---------Function: ms_ncopy----------
 *  Copies at most n chars from the second string argument to the first including the '\0' 
 *  character.If the destination argument is bigger then the remaining chars are replaced
 *  by '\0'.
 *  	
 *  Arguments:
 *  		-char *: The destination string.Must be large enough to fit the
 *  			 source string.
 *  		
 *  		-const char*: The source string that will be copied
 *
 *  		-size_t : The number of chars to be copied.
 *
 *  Return:
 *  		-char *: The pointer to start of the copied string (destination string "first arg")
 *
 *  Assertions:
 *  		-Checks if the string (destination,source) are NULL.
 *  		 If true exits the programm printing an error message. 
 *
 *
 */

char *ms_ncopy(char *,const char*,size_t);




/*----------Function: ms_concat------------
 *  Concats the second argument string at the fo the first.
 *
 *  Arguments:
 * 		-char *: The first arguments string at whose the end the first is concated.
 *
 * 		-const char* : The second argument string.
 *
 *  Return:
 *  		-char *: The pointer to start of the first string argument.
 *
 * Assertions:
 *  		-Checks if the strings (first,second) are NULL.
 *  		 If true exits the programm printing an error message. 		
 *
 */
char *ms_concat(char *,const char*);




/*----------Function: ms_nconcat------------
 *  Concats the first n characters shown by the 3rd argument of the second string 
 *  argument string at the end of the first.
 *
 *  Arguments:
 * 		-char *: The first arguments string at whose the end the first is concated.
 *
 * 		-const char* : The second argument string.
 *
 * 		-size_t: The number of characters to be concated.
 *
 *  Return:
 *  		-char *: The pointer to start of the first string argument.
 *
 * Assertions:
 *  		-Checks if the strings (first,second) are NULL.
 *  		 If true exits the programm printing an error message. 		
 *
 */

char *ms_nconcat(char *,const char*,size_t);




/*---------Function: ms_compare----------
 * Compares lexicographically the 2 strigns passed as argumets to this function.
 *
 * Arguments:
 * 		-const char* : The first of the 2 strings to be compared.
 *
 * 		-const char* : The second string to be compared.
 * Return:
 * 		-An integer inticating the result of the comparison.
 * 		 Return value <0 if the first str< second str, 0 if first str==second str,
 * 		 and >0 if the first str> second str.
 *
 * Assertions:
 * 		-Checks if the strings (first,second) are NULL.
 * 		 If true exits the programm printing an error message.
 * 
 */
int ms_compare(const char*,const char*);




/*-----------Function: ms_ncompare---------------
 * Compares lexicographically at most n chars(n is the 3rd argument) of the first string
 * with the 2nd string passed as argumets to this function.
 *
 * Arguments:
 * 		-const char* : The first of the 2 strings to be compared.
 *
 * 		-const char* : The second string to be compared.
 *
 * 		-size_t : The number of chars of the first string argument.
 * Return:
 * 		-An integer inticating the result of the comparison.
 * 		 Return value <0 if the first str< second str, 0 if first str==second str,
 * 		 and >0 if the first str> second str.
 *
 * Assertions:
 * 		-Checks if the strings (first,second) are NULL.
 * 		 If true exits the programm printing an error message.
 * 
 */
int ms_ncompare(const char*,const char*,size_t);




/*-------------Function: ms_search--------------
 * Searches and finds the first apereance of the second string argument in the first.
 *
 * Arguments:
 * 		-const char *: The string to look in.
 *
 * 		-const char *: The pattern to find in the first.
 *
 * Returns:
 * 		-A pointer to the first appearance of the pattern in the first
 * 		 NULL if the pattern does not exist.
 *
 *
 * Assertions:
 * 		-Checks if the 2 string arguments are NULL.
 * 		 If true exits the function printing an error message.
 * 
 */
char *ms_search(const char*,const char*);
