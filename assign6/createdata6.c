#include<stdio.h>

int main(){
	FILE *data;
	int i;
	char input[52]={'D','i','m','i','t','r','i','s',' ','T','s','o','l','i','s',
			'\0',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
			' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' ',
 			' ',' ',' ','\xe4','\x02','\x05','\x08','\xe4','\x02','\x05',
			'\x08','\x58','\xb4','\x08','\x08'};


	data=fopen("data6","w+");
	
	for(i=0;i<52;i++){
		fprintf(data,"%c",input[i]);
	}
	fclose(data);
	return 0;
	
}
