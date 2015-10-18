/*______________mystring_ars.c_____________
 * assignement 1
 * hy255
 * Tsolis Dimitris
 * email:tsolis@csd.uoc.gr
 *
 * Contains a function implementation of the interface introduced by 
 * mystring.h library.
 * This implementation is done with use of arrays
 * 
 */
#include<assert.h>
#include<stddef.h>

/*******HELPING FUNCTIONS*********/
/*--------------Function last_index-----------------
 * Returns the index of NULL char <'\0'>.
 *
 * Arguments:
 * 		-string *a: The string that the character is in
 *
 * Returns:
 * 		-size_t i: The index of NULL char
 * 
 */
size_t last_index(char *a){
	size_t i;
	for(i=0U;a[i]!='\0';i++){
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
	size_t length=0U;
	assert(cs);
	while(cs[length]!='\0'){
		length+=1;
	}
	return length;
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
 *  		-char *: The pointer to start of the copied string (destination string 
 *  		"first arg")
 *
 *  Assertions:
 *  		-Checks if the string (destination,source) are NULL.
 *  		 If true exits the programm printing an error message. 
 *
 *
 */
char *ms_copy(char *str,const char *cs){
	size_t i;
	
	assert(str);
	assert(cs);
	
	if(str[0]=='\0' && cs[0]=='\0'){
		return "";
	}

	for(i=0U;i<ms_length(cs)+1U;i++){
		str[i]=cs[i];
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
 *  		-char *: The pointer to start of the copied string (destination string 
 *  		"first arg")
 *
 *  Assertions:
 *  		-Checks if the string (destination,source) are NULL.
 *  		 If true exits the programm printing an error message. 
 *
 *
 */

char *ms_ncopy(char *str,const char *cs,size_t n){
	size_t i;

	assert(str);
	assert(cs);

	if(str[0]=='\0' && cs[0]=='\0'){
		return "";
	}

	for(i=0U;i<n && cs[i]!='\0';i++){
		str[i]=cs[i];
	}

	str[i]='\0';
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
	size_t i=0U,j;
	assert(str);
	assert(cs);

	if(str[0]=='\0' && cs[0]=='\0'){
		return "";
	}

	i=last_index(str);
	for(j=0U;cs[j]!='\0';j++){
		str[i++]=cs[j];
	}
	str[i]='\0';
	return str;
}

/*----------Function: ms_nconcat------------
 *  Concats the first n characters shown by the 3rd argument of the second string 
 *  argument  at the end of the first.
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
#include<stdio.h>
char *ms_nconcat(char *str,const char *cs,size_t n){
	size_t i=0U,j;

	assert(str);
	assert(cs);
	if(str[0]=='\0' && cs[0]=='\0'){
		return "";
	}


	i=last_index(str);

	for(j=0U;j<n && cs[j]!='\0';j++){
		str[i++]=cs[j];
	}

	str[i]='\0';

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
	
	size_t i;
	int res;

	assert(csa);
	assert(csb);
	
	if(csa[0]=='\0' && csb[0]=='\0'){
		return 0;
	}
	
	for(i=0U;csa[i]!='\0' || csb[i]!='\0';i++){
		res=csa[i]-csb[i];
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
	size_t i;
	int res;

	assert(csa);
	assert(csb);

	if(csa[0]=='\0' && csb[0]=='\0'){
		return 0;
	}
		
	for(i=0U;(csa[i]!='\0' || csb[i]!='\0') && i<n;i++){
		res=csa[i]-csb[i];
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
char *ms_search(const char *cs,const char *pat){
	size_t i;
	char *a=(char *)cs;
	assert(cs);
	assert(pat);

	for(i=0U;i<ms_length(cs);i++){
		
		  if(ms_ncompare(a,pat,ms_length(pat))==0){
			  
			  return a;
		  }	  
		
		  a++;
	}

	return NULL;
}
