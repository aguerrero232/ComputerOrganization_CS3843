#include <stdio.h>
#include <stdlib.h>


void function(int i){
	char *msg = "%2x  %3d  %3o   %c\n";
	__asm{

		mov eax, i
		mov esi, msg

		push eax
		push eax
		push eax
		push eax

		push esi

		call printf

		add esp, 14h

	}
}


int main(int argc, char* argv[]) {
    int i;
	char *hdr = "Hex  Dec  Oct   Ch\n";
	printf("NAME: Ariel Guerrero\nabc123: aes604\n\nHomework #2\n\n");
	printf("----  CODE OUTPUT -----------------------------\n\n\n");
	__asm {
			
		mov eax, hdr
		push eax
		call printf
		pop eax

		xor ecx, ecx
		xor eax, eax

		mov ecx, 20h
			
		LOOP1:
			
			xor eax, eax
			mov eax, ecx

			push eax

			call function	
			
			pop eax

			mov ecx, eax 

			inc ecx
			cmp ecx, 100h
			
			jne LOOP1
		
	}
	system("pause");
	return 0;
}