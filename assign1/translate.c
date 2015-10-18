#include<stdio.h>
#include<string.h>

#define MAP_SIZE 256
#define MAX_CHARS 4

enum STATE {INIT,M,m,N,n};
enum STATE state;
char map[MAP_SIZE][MAX_CHARS];




/*-----Function Prototypes-----*/
int Init_map(void);
void print_help(void);
void Init(int);/*Initial state of state machine*/
void NT(int);/*NT state of state machine(checks if it must print D,d)*/
void MP(int);/*MP state of state machine(checks if it must print B,b)*/


/*-----Main-----*/
int main(int argc,char **argv){
	int res1,res2;
	void (*actions[])(int)={Init,MP,MP,NT,NT};/*Array of state functions of the state machine*/
	int ch;
	
	state=INIT;
	
	
	if(argc>1){
		res1=strcmp(argv[1],"-h");
		res2=strcmp(argv[1],"-help");
		if(res1==0 || res2==0){
			print_help();
			return 0;
		}
		else{
			fprintf(stderr,"Invalid switch.\nTry -h,-help switch.\n");
			return 1;
		}
	}
	/*
	 * Call Init_map() to initialize the map of chars
	 * */
	if(Init_map()==1){
		return 1;
	}
	
	/*cd  
	 * Read characters from input and perform the right actions.
	 * */
	while((ch=getchar())!=EOF){
		actions[state](ch);
	}
	

	return 0;
		
}

/*---Function Implementation----*/

/********Init_map*********/
/* This function initializes the  character map from a standar initialization file,
 * with a standar characters map.
 * 
 * Arguments:
 * 		-
 * Returns:
 * 	The error value of the function.
 * 		The value 0 indicates a normal execution.
 * 		The value 1 indicates an ecxeptional (error) execution.
 * 		
 */
int Init_map(void){
	int i,j;
	FILE *Init_file;/*A file pointer to the init file*/
	char tmp_str[4];/*A temporary string*/
	
	for(i=0;i<4;i++){
		tmp_str[i]='\0';
	}
	
	/*
	 * Opens the init file.
	 * If an error occurs exits with errorcode 1.
	 */
	if((Init_file=fopen("Init_file.txt","r"))==NULL){
		fprintf(stderr,"Can not find Init file.\n");
		return 1;
	}	
	
	/*Initialize all mappings with null(\0)*/
	for(i=0; i<=255; i++){
		for(j=0; j<=3; j++){
			map[i][j]='\0';
		}
	}
	
	/*
	 * Initializes the map from the init file.
	 * Reads first the integer that represents the character in the iso-8859-7,
	 * and theb reads the mapped character from the iso-8859-1,
	 * until the End Of File is reached.
	 */
	while(fscanf(Init_file,"%d",&i)!=EOF){
		fscanf(Init_file,"%s",tmp_str);
		strcpy(map[i],tmp_str);
	}
	fclose(Init_file);

	return 0;

}

/* The followin define statements define the number codes
 * for letters Μ,μ,Ν,ν,τ,Τ,Π,π
 * 
 * */
#define Mi 204
#define Ni 205
#define mi 236
#define ni 237
#define taf 244
#define Taf 212
#define Pi 208
#define pi 240

/******Init Function*******/
/* This function represents the init state of the state machine.
 * 
 * Arguments:
 * 	int ch:The character that is for convertion.
 * Returns:
 * 		-
 * 
 */
void Init(int ch){
	if(ch!=Mi && ch!=mi && ch!=ni && ch!=Ni ){/*Case characters are not mi,Mi,ni,Ni*/
		if(ch>181 && ch<255){/*Case characters are in the range of the map*/
			printf(map[ch]);
		}
		else{/*Case they are not*/
			putchar(ch);
		}
		state=INIT;
	}
	else if(ch==Mi){
		state=M;
	}
	else if(ch==mi){
		state=m;
	}
	else if(ch==ni){
		state=n;
	}
	else if(ch==Ni){
		state=N;
	}
	
}

/******NT Function*******/
/* This function represents the NT state which when we want to print d,D
 * for the greek ντ,νΤ,Ντ,ΝΤ.
 *
 * Arguments:
 * 	int ch:The char for convertion (the code in the iso-8859-7)
 *
 * Returns:
 * 		-
 * 
 */
void NT(int ch){
	if(state==N){/*Case we read a Capital Ni*/
		if(ch==taf || ch==Taf){
			putchar('D');
			state=INIT;
		}
		else if(ch==Ni){
			printf(map[Ni]);
			state=N;
		}
		else if(ch==ni){
			printf(map[Ni]);
			state=n;
		}
		else if(ch==Mi){
			printf(map[Ni]);
			state=M;
		}
		else if(ch==mi){
			printf(map[Ni]);
			state=m;
		}
		else{
			printf(map[Ni]);
			printf(map[ch]);
			state=INIT;
		}	
	}
	else if(state==n){/*Case we read a little ni*/
		if(ch==taf || ch==Taf){
			putchar('d');
			state=INIT;
		}
		else if(ch==Ni){
			printf(map[ni]);
			state=N;
		}
		else if(ch==ni){
			printf(map[ni]);
			state=n;
		}
		else if(ch==Mi){
			printf(map[ni]);
			state=M;
		}
		else if(ch==mi){
			printf(map[ni]);
			state=m;
		}
		else{
			printf(map[ni]);
			printf(map[ch]);
			state=INIT;
		}	
	}	
	
}
/******MP Function*******/
/* 
 * This function represents the MP state which when we want to print b,B
 * for the greek μπ,μΠ,Μπ,ΜΠ.
 *
 * Arguments:
 * 	int ch:The char for convertion
 *
 * Returns:
 * 		-
 */
void MP(int ch){
	if(state==M){/*Case we read a capital Mi*/
		if(ch==Pi || ch==pi){
			putchar('B');
			state=INIT;
		}
		else if(ch==Ni){
			printf(map[Mi]);
			state=N;
		}
		else if(ch==ni){
			printf(map[Mi]);
			state=n;
		}
		else if(ch==Mi){
			printf(map[Mi]);
			state=M;
		}
		else if(ch==mi){
			printf(map[Mi]);
			state=m;
		}
		else{
			printf(map[Mi]);
			printf(map[ch]);
			state=INIT;
		}	
	}
	else if(state==m){/*Case we read a little mi*/
		if(ch==Pi || ch==pi){
			putchar('b');
			state=INIT;
		}
		else if(ch==Ni){
			printf(map[mi]);
			state=N;
		}
		else if(ch==ni){
			printf(map[mi]);
			state=n;
		}
		else if(ch==Mi){
			printf(map[mi]);
			state=M;
		}
		else if(ch==mi){
			printf(map[mi]);
			state=m;
		}
		else{
			printf(map[mi]);
			printf(map[ch]);
			state=INIT;
		}	
	}	

}

/******Print_help*******/
/* Prints the manual of the programm if the the command 
 * switch -h of --help.
 * 
 * Arguments:
 * 		-
 * Returns:
 * 		-
 * 
 */
void print_help(void){
	FILE *manual_pages;
	char c;
	
	/* Opens the manual pages of the programm
	 * and prints them to stderr.
	 * 
	 * */
	if((manual_pages=fopen("manual_pages.txt","r"))==NULL){
		fprintf(stderr,"Can't find manual pages\n");
		return;
		
	}

	while((c=fgetc(manual_pages))!=EOF){
		fprintf(stderr,"%c",c);
	}
	fclose(manual_pages);
	return;

	
}
