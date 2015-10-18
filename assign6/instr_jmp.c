#include<stdio.h>

int main(){
	__asm__(
	    	"jmp *%eax\n"
	    	"movb $0x39, 0x80885b4\n"
			"movl $0x80502eb,%eax\n"
	    	"jmp *%eax\n"
		);
	return 0;
}
