// -----------------------------------
// Program x86asm.s
// Compute and print the sum 0+...+N
// -----------------------------------

	.section .data	//Dilosi oti akoloythei tha topothetithei sto data segment 
N:	.long 1000	//arxikopoihsh toy arithmoy N (long) se 1000
S:	.long 0		//arxikopoihsh toy athroismatos S (long) se 0 
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	//Oti akoloythei ao edo kai kato topothetitai sto text segment 
.globl main
main:	
	pushl %ebp	// sozei ton base pointer ebp stin koryfi tis stoivas   
	movl %esp, %ebp	// vazei ton stack pointer esp ston base pointer

 	// initialize
        movl N, %ebx	// metaferei ta periexomena tis thesis mnimis N ston register ebx

 	// compute sum
L1:
	addl %ebx, S	// Arxikopoihsh toy athroismatos S se 1000 o ebx einai o loop counter
	decl %ebx       // meionei kata 1 ton register ebx diladi ton counter
	cmpl $0, %ebx   // sygrinei ton ebx loop counter me to 0
	jng  L2		// ean o ebx den einai megalyteros apo to 0 ektyponei to potelesma kai kanei exit 
        movl $L1, %eax	// metaferei ti dieythinsi mnimis L1 ston eax
        jmp *%eax	// unconditional jump sti dieythinsi poy periexei o eax diladi L1

L2:
	// print result
	pushl S		// pernaei stin stoiva to teleytaio orisma tis printf poy einai to athroisma S
	pushl N	        // pernaei stin stoiva gia orisma stin printf ton arithmo N
	pushl $Msg	// pernaei stin stoiva ti dieythinsi mnimis toy string pros ektyposi
	call printf	// kalei tin printf
	popl %eax	// kanei pop to $Msg apo ti stoiva
	popl %eax	// kanei pop to N apo ti stoiva
	popl %eax	// kanei pop to S apo ti stoiva

	// exit
	movl $0, %eax  	// midenizei ton register eax
        leave		//
 	ret		//epistrefei i main
