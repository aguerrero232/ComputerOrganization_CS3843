// @Author: Ariel Guerrero, aes604
// These are simplified Roman numerals. Instead of IV for 4, we just use IIII. It is a little easier.
// No "subtractive notation", only "additive notation" in en.wikipedia.org/wiki/Roman_numerals
// All letters must be in order M-D-C-L-X-V-I. Up to four each M-C-X-I and up to one D-L-V.
// 2,618 would be MMDCXVIII (2000 + 500 + 100 + 10 + 5 + 3)
// 24 is XXIIII, 50 is just L, 1001 is MI, and so on. All numbers are positive.
// 4,999 is the largest and longest, MMMMDCCCCLXXXXVIIII. Whew.

// All input is on the command line. Do not prompt for values.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n;
char result[100];


int main(int argc, char *argv[]) {
	int i;

	for (i = 1; i < argc; i++) {
		n = atoi(argv[i]);
		if (n > 0 && n < 5000) {
			memset(result, 0, sizeof result); 
			
			__asm {
			mov eax, n
			mov ebx, 0 // digitcount
			mov ecx, 0 // digitindexholder
				
			checkvalue:	
				cmp eax, 0
				jle done
				
				cmp ecx, 7
				jge done	
				
				cmp ecx, 6
				je case1

				cmp ecx, 5
				je case5

				cmp ecx, 4
				je case10

				cmp ecx, 3				
				je case50

				cmp ecx, 2
				je case100

				cmp ecx, 1
				je case500	

				cmp ecx, 0 
				je case1000


			case1000:
					
				push eax
				push ebx

				mov ebx, 1000
				cdq

				div ebx
				cmp eax, 1
	
				pop ebx
				pop eax

				jl checknext

				mov edx, 0
				mov dl, 'M'
				mov byte ptr[result + ebx], dl
				inc ebx
					
				mov edx, 1000
				sub eax, edx
				jmp checkvalue

			case500:
				push eax
				push ebx

				mov ebx, 500
				cdq

				div ebx
				cmp eax, 1

				pop ebx
				pop eax

				jl checknext

				mov edx, 0
				mov dl, 'D'
				mov byte ptr[result + ebx], dl
				inc ebx

				mov edx, 500
				sub eax, edx
				jmp checkvalue
			case100:

				push eax
				push ebx

				mov ebx, 100
				cdq

				div ebx
				cmp eax, 1

				pop ebx
				pop eax

				jl checknext

				mov edx, 0
				mov dl, 'C'
				mov byte ptr[result + ebx], dl
				inc ebx

				mov edx, 100
				sub eax, edx
				jmp checkvalue

			case50:
		
				push eax
				push ebx

				mov ebx, 50
				cdq

				div ebx
				cmp eax, 1

				pop ebx
				pop eax

				jl checknext

				mov edx, 0
				mov dl, 'L'
				mov byte ptr[result + ebx], dl
				inc ebx

				mov edx, 50
				sub eax, edx
				jmp checkvalue

			case10:

				push eax
				push ebx

				mov ebx, 10
				cdq

				div ebx
				cmp eax, 1

				pop ebx
				pop eax

				jl checknext

				mov edx, 0
				mov dl, 'X'
				mov byte ptr[result + ebx], dl
				inc ebx

				mov edx, 10
				sub eax, edx
				jmp checkvalue

			case5:

				push eax
				push ebx

				mov ebx, 5
				cdq

				div ebx
				cmp eax, 1

				pop ebx
				pop eax

				jl checknext

				mov edx, 0
				mov dl, 'V'
				mov byte ptr[result + ebx], dl
				inc ebx

				mov edx, 5
				sub eax, edx
				jmp checkvalue

			case1:
				push eax
				push ebx

				mov ebx, 1
				cdq

				div ebx
				cmp eax, 1

				pop ebx
				pop eax

				jl checknext

				mov edx, 0
				mov dl, 'I'
				mov byte ptr[result + ebx], dl
				inc ebx

				mov edx, 1
				sub eax, edx
				jmp checkvalue

			checknext:
				inc ecx
				jmp checkvalue

			done:
			}
		}
		printf("Roman(%d) = %s\n\n", n, result);
		
	}
	system("pause");
}

/*

checkvalue:
cmp eax, 0
jle done

cmp ecx, 7
jge done

push eax
cdq
idiv dword ptr [RomanValues + ecx*4]
cmp eax, 1
pop eax

jl checknext

mov dl, byte ptr[RomanSymbols + ecx]
mov byte ptr[result + ebx], dl
inc ebx
sub eax, dword ptr[RomanValues + ecx * 4]
jmp checkvalue

checknext:
inc ecx
jmp checkvalue

done:

*/

/*
void printRoman(int value){
	int ValueHolder = value;
	int DigitIndexHolder = 0;
	int DigitCount = 0;

	while (ValueHolder > 0 && DigitIndexHolder < 7) { //repeat process until num is not 0
		//dblPlaceValue = dblValueHolder / decimals[dblDigitIndexHolder];
		while ((ValueHolder) / (RomanValues[DigitIndexHolder]) >= 1) {  	
			printf("%c", RomanSymbols[DigitIndexHolder]) ; // printing current digit
			ValueHolder -= RomanValues[DigitIndexHolder];  //subtract largest base value from num
			DigitCount++; // adding digits to our string 
		}
		DigitIndexHolder++; //move to next base value to divide num 
	}
	printf("\n");
}

*/