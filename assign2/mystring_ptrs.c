/*______________mystring_ptrs.c_____________
 * assignement 1
 * hy255
 * Tsolis Dimitris
 * email:tsolis@csd.uoc.gr
 *
 * Contains a function implementation of the interface introduced by 
 * mystring.h library.
 * This implementation is done with use of pointers
 * 
 */
#include<assert.h>
#include<stddef.h>

/*******HELPING FUNCTIONS*********/
/*--------------Function last_index-----------------
 * Returns the adrress of the '\0' character.
 *
 * Arguments:
 * 		-string *a: The string that the character is in
 *
 * Returns:
 * 		-char *i: The index of NULL char
 * 
 */
char *last_index(char *a){
	char *i;
	for(i=a;*i!='\0';i++){
		;
	}

	return i;
}



/**************FUNCTION IMPLEMENTATION******************/

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

size_t ms_length(const char *cs){
	
	const char *i;
	
	assert(cs);
	
	for(i=cs;*i!='\0';i++){
		;
	}

	

	return i-cs;
}


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
char *ms_copy(char *str,const char *cs){
	const char *i;
	char *j;
	
	assert(str);
	assert(cs);
	
	if(*str=='\0' && *cs=='\0'){
		return "";
	}
	for(i=cs,j=str;i-cs!=ms_length(cs)+1;i++,j++){
		*j=*i;
	}
	
	
	return str;
}


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

char *ms_ncopy(char *str,const char *cs,size_t n){
	const char *i;
	char *j;
	
	assert(str);
	assert(cs);
	if(*str=='\0' && *cs=='\0') {
		return "";
	}

	
	for(i=cs,j=str;i-cs<n;i++,j++){
		*j=*i;
	}
	*j='\0';
	return str;
}




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
char *ms_concat(char *str,const char *cs){
	char *j;
	const char *i=cs;
	assert(str);
	assert(cs);
	
	if(*str=='\0' && *cs=='\0'){
		return "";
	}
	
	for(j=last_index(str) ; i-cs<=ms_length(cs) ; i++,j++){
		*j=*i;
	}
	
	
	
	return str;
}


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

char *ms_nconcat(char *str,const char *cs,size_t n){
	char *j;
	const char *i=cs;
	
	assert(cs);
	assert(str);


	if(*str=='\0' && *cs=='\0'){
		return "";
	}
		
	for(j=last_index(str); i-cs<n ;i++,j++){
		*j=*i;
	}
	*j='\0';
	return str;

}


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
int ms_compare(const char *csa,const char *csb){
	
	const char *j;
	const char *i;
	int res=0;

	assert(csa);
	assert(csb);
	
	for(i=csa,j=csb;*i!='\0' || *j!='\0';i++,j++){
		res=*i-*j;
		if(res<0 || res>0){
			return res;
		}
	}
	
	return res;

}



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
int ms_ncompare(const char *csa,const char *csb,size_t n){
	const char *i;
	const char *j;
	int res=0;

	assert(csa);
	assert(csb);

	for(i=csa,j=csb;(*i!='\0' || *j!='\0') && (i-csa<n && j-csb<n);i++,j++){
		res=*i-*j;
		if(res<0 || res>0){
			return res;
		}

	}


	return res;
}


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
char *ms_search(const char *csa,const char *pat){
	const char *i;
	
	assert(csa);
	assert(pat);
	
	for(i=csa;*i!='\0';i++){
		if(ms_ncompare(i,pat,ms_length(pat))==0){
			return (char *)i;
		}
	}
	return NULL;
	
}
