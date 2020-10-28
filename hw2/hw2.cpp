#include <stdio.h>

int main(int argc, char* argv[]) {
    int i;
    printf("Hex  Dec  Oct   Ch\n");
    for (i = 32; i < 256; i++) {
        printf(" %2x  %3d  %3o   %c\n", i, i, i, i);
    }
}