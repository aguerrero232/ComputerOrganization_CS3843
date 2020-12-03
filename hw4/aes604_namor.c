// @Author Ariel Guerrero 
// abc123: aes604 

// These are simplified Roman numerals. Instead of IV for 4, we just use IIII. It is a little easier.
// No "subtractive notation", only "additive notation" in en.wikipedia.org/wiki/Roman_numerals
// All letters must be in order M-D-C-L-X-V-I. Up to four each M-C-X-I and up to one D-L-V.
// MMDCXVIII is 2,618 (2000 + 500 + 100 + 10 + 5 + 3)
// XXIIII is 24, L is 50, MI is 1001. All numbers are positive.
// MMMMDCCCCLXXXXVIIII is the largest and longest, 4,999. Whew.

// No error checking is needed. Assume all UPPERCASE letters. Assume all input is valid.

// All input is on the command line. Do not prompt for values.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
char source[100];

int main(int argc, char *argv[]) {
	int i;

	for (i = 1; i < argc; i++) {
		printf("argument: %s\n", argv[i]);
		strcpy_s(source, 99, argv[i]);
		__asm {
       
	
		mov n, 0

		mov eax, n
		mov ebx, 0 // digit
		mov ecx, 0 // digitIndex
		
		lea esi, source 

		checkvalue:
			
			cmp ebx, 0
				je caseM
			cmp ebx, 1
				je caseD
			cmp ebx, 2
				je caseC
			cmp ebx, 3
				je caseL
			cmp ebx, 4
				je caseX
			cmp ebx, 5
				je caseV
			cmp ebx, 6
				je caseI
			cmp ebx, 7 
				jge done
		
		caseM:

			push eax
			push ebx 
						
			mov bl, 'M'
			cmp bl, byte ptr[esi + ecx]

			pop ebx
			pop eax
			
			jne checknext 

			add eax, 1000
			inc ecx 

			jmp checkvalue

		caseD:

			push eax
			push ebx

			mov bl, 'D'
			cmp bl, byte ptr[esi + ecx]
			
			pop ebx
			pop eax
			
			jne checknext
			
			add eax, 500
			inc ecx

			jmp checkvalue

		caseC:

			push eax
			push ebx

			mov bl, 'C'
			cmp bl, byte ptr[esi + ecx]

			pop ebx
			pop eax

			jne checknext

			add eax, 100
			inc ecx

			jmp checkvalue

		caseL:

			push eax
			push ebx

			mov bl, 'L'
			cmp bl, byte ptr[esi + ecx]

			pop ebx
			pop eax

			jne checknext

			add eax, 50
			inc ecx

			jmp checkvalue
		 
		caseX:

			push eax
			push ebx

			mov bl, 'X'
			cmp bl, byte ptr[esi + ecx]

			pop ebx
			pop eax

			jne checknext

			add eax, 10
			inc ecx

			jmp checkvalue

		caseV:

			push eax
			push ebx

			mov bl, 'V'
			cmp bl, byte ptr[esi + ecx]

			pop ebx
			pop eax

			jne checknext

			add eax, 5
			inc ecx

			jmp checkvalue
		
		caseI:

			push eax
			push ebx

			mov bl, 'I'
			cmp bl, byte ptr[esi + ecx]

			pop ebx
			pop eax

			jne checknext

			add eax, 1
			inc ecx

			jmp checkvalue
		
		checknext:
			inc ebx
			jmp checkvalue

		done: 
			mov n, eax

		}
    //printf("%s -> %d\n\nNUM: %d\n\n", source, n, num);
	printf("%s -> %d\n\n", source, n);

  }
	system("pause");
}\
