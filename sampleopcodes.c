// local machine: gcc -masm=intel -no-pie -Wall Opcodes.c -o /tmp/Opcodes
// fox machines: gcc -masm=intel -Wall Opcodes.c -o /tmp/Opcodes
// /tmp/Opcodes -45 200 -1

// Note: the variables (x, y, etc.) have to be global for some reason

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nxt(instr,ttl) \
  asm("mov eax, x"); \
  asm(instr); \
  asm("setc carry"); \
  asm("seto overflow"); \
  asm("sets sign"); \
  asm("setz zero"); \
  asm("mov y, eax"); \
  printf("%-8s = %08x CF=%d OF=%d SF=%d ZF=%d (%d)\n", ttl, y, carry, overflow, sign, zero, y);


#define nxt2(instr,ttl, y) \
  asm("mov eax, x"); \
  asm(instr); \
  asm("sets sign"); \
  asm("setz zero"); \
  asm("setp parity");\
  printf("%-8s = %08x SF=%d ZF=%d PF=%d (%d)\n", ttl, x&y, sign, zero, parity, y);


int x = 0;
int y = 0;
char carry = 0;
char overflow = 0;
char sign = 0;
char zero = 0;
char parity = 0;

void doit(char *str) {
    x = atoi(str);
    printf("====== x = %08x (%d)\n", x, x);

    nxt("not eax", "not x");
    nxt("neg eax", "neg x");

    nxt("inc eax", "inc x");
    nxt("dec eax", "dec x");

    nxt("add eax, 5", "add 5");
    nxt("sub eax, 5", "sub 5");
    
    nxt("shl eax, 2", "shl 2");
    nxt("shr eax, 2", "shr 2");
    nxt("sar eax, 2", "sar 2");
    nxt("ror eax, 1", "ror 1");
    nxt("rol eax, 1", "rol 1");
    
    nxt("and eax, 0xAAAAAAAA", "and A's");
    nxt("or eax, 0xAAAAAAAA", "or A's");
    nxt("xor eax, 0xAAAAAAAA", "xor A's");
  }

  void doit2(char *str) {
    x = atoi(str);
    printf("====== x = %08x (%d)\n", x, x);
    nxt("bt eax, 3", " bt 3");
    nxt("bts eax, 3", " bts 3");
    nxt("btr eax, 3", " btr 3");
    nxt("btc eax, 3", " btc 3");
    nxt("bsf eax, x", " bsf 3");
    nxt("bsr eax, x", " bsr 3");

  }


  void doit3(char *str) {
    x = atoi(str);
    printf("====== x = %08x (%d)\n", x, x);
    nxt2("test eax, x","test eax, x", x);
    nxt2("test eax, 7", "test eax, 7", 7);
  }

int main(int argc, char *argv[]) {
 
  char buf[100];
  int i;
  char *evalOption = argv[1];
  switch(evalOption[0]){
    
    case 't':
      for (i = 2; i < argc; i++) {
        if (i > 2) printf("\n");
        doit3(argv[i]);
      }

      while (1) {
        printf("\nEnter a number (q to quit) -->");
        scanf("%s", buf);
        if (strcmp(buf, "q") == 0) break;
        doit3(buf);
      }
    break;

    case 'b':
      for (i = 2; i < argc; i++) {
        if (i > 2) printf("\n");
        doit2(argv[i]);
      }

      while (1) {
        printf("\nEnter a number (q to quit) -->");
        scanf("%s", buf);
        if (strcmp(buf, "q") == 0) break;
        doit2(buf);
      } 
    break;
 
    default:
      for (i = 1; i < argc; i++) {
        if (i > 1) printf("\n");
        doit(argv[i]);
      }
      
      while (1) {
        printf("\nEnter a number (q to quit) -->");
        scanf("%s", buf);
        if (strcmp(buf, "q") == 0) break;
        doit(buf);
      }
    break;

  }
  
  return 0;
}