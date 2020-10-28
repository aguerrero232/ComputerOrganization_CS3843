#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// conversion functions ------------------------------------ 
// needs for binary .. bin -> oct, bin -> dec, bin -> hex
int convertBinaryToOctal(long long bin);
int convertBinaryToDecimal(long long n);
char* convertBinaryToHex(long long pbinaryNumber);

// 2 comp funtions 
long long flipBits(long long pBinaryNumber);
long long add1ToBinary(long long pBinaryNumber);

// needs for oct .. oct - > dec, oct -> hex
long long convertOctalToBinary(int oct);
int convertOctalToDecimal(int octalNumber);

// needs for dec .. dec -> oct,  dec -> hex
long long convertDecimalToBinary(int dec);
int convertDecimalToOctal(int decimalNumber);

// needs for hex .. hex -> octal, hex -> dec 
long long  convertHexToBinary(char* hex);
// --------------------------------------------------------

// printing functions --------------------------------------
// positive vals
void validbase2Print(char* argument);
void validbase8Print(char* argument);
void validbase10Print(char* argument);
void validbase16Print(char* argument);

// negative vals
void validbase2NegPrint(char* argument);
void validbase8NegPrint(char* argument);
void validbase10NegPrint(char* argument);
void validbase16NegPrint(char* argument);
//----------------------------------------------------------

// checks too see what bases to print for the arg
void checkBases(char *argument);
char* remove1stElement(char* argument);
// valid base n chars
char base2Chars[2] = {'0','1'};
char base8Chars[8] = {'0','1','2','3','4','5','6','7'};
char base10Chars[10] = {'0','1','2','3','4','5','6','7','8','9'};
char base16Chars[22] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','a','b','c','d','e','f'};

int main(int argc, char** argv)
{

    int  i;
   if(argc > 1){
    for (i=1; i< argc; i++)
        checkBases(argv[i]);
    }
    else{
        printf("\n ---- Error no command line arguments ----\n Exiting . . . . .\n");
    }
    printf("\n");
}

void checkBases(char* argument){

    char* textstring = "Octal          Decimal          Unsigned                    Hex ";
    printf("=== CHECKING %-12s\t%15s\n", argument, textstring);
    int i, validBase2 = 1, validBase8 = 1, validBase10 = 1, validBase16 = 1, isNegative = 0;

    for(i=0; i < strlen(argument); i++){
        char currchar = argument[i];
        if(currchar != '-'){
            if(strchr(base2Chars, currchar) == NULL){
                validBase2 = 0;
            }
            if(strchr(base8Chars, currchar) == NULL){
                validBase8 = 0;
            }
            if(strchr(base10Chars, currchar) == NULL){
                validBase10 = 0;
            }
            if(strchr(base16Chars, currchar) == NULL){
                validBase16 = 0;
            }
        }
        else if(strlen(argument) == 1 ){   
            printf("\nmessed up only \"-\" was inputted! ");
            validBase2 = 0;
            validBase8 = 0;
            validBase10 = 0;
            validBase16 = 0;
            break;
        }
        if(currchar == '-'){
            isNegative = 1;
        }
    }
    
    if(isNegative == 0){
        if(validBase2)
            validbase2Print(argument);
        if(validBase8)
            validbase8Print(argument);
        if(validBase10)
            validbase10Print(argument);
        if(validBase16)
            validbase16Print(argument);
    }
    else{
        // handle negatives
        if(validBase2 == 1)
            validbase2NegPrint(argument);
        if(validBase8 == 1)
            validbase8NegPrint(argument);
        if(validBase10 == 1)
            validbase10NegPrint(argument);
        if(validBase16 == 1)
            validbase16NegPrint(argument);
    }

    printf("\n\n");
}

//-----------------------------------------------------------------------------------------------------------------------------
// Print for positives
//-----------------------------------------------------------------------------------------------------------------------------
void validbase2Print(char* argument){
    printf( "\nBase  2: %28d %16d", convertBinaryToOctal( atoll(argument)), convertBinaryToDecimal(atoll(argument))); 
    printf("\t\t\t\t %14s", convertBinaryToHex(atoll(argument)));
}
void validbase8Print(char* argument){
    printf( "\nBase  8: %28d %16d", atoi(argument), convertOctalToDecimal(atoi(argument))); 
    printf("\t\t\t\t %14s", convertBinaryToHex(convertOctalToBinary(atoi(argument))));
}
void validbase10Print(char* argument){
    printf( "\nBase 10: %28d %16d", convertDecimalToOctal(atoi(argument)), atoi(argument)); 
    printf("\t\t\t\t %14s", convertBinaryToHex(convertDecimalToBinary(atoi(argument))));
}
void validbase16Print(char* argument){
    printf( "\nBase 16: %28d %16d", convertBinaryToOctal(convertHexToBinary(argument)), convertBinaryToDecimal(convertHexToBinary(argument))); 
    printf("\t\t\t\t %14s", argument);
}
//-----------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------
// Print for negatives
//-----------------------------------------------------------------------------------------------------------------------------
void validbase2NegPrint(char* argument){
    if(atoll(argument) == -1){
        printf("\nBase  2: %28s %16s" , "37777", " -1");
        printf("\t\t\t\t %14s","FFFF");
    }
    else{
        printf("\nBase  2:" );
        printf( "%24s%d", "37777", convertBinaryToOctal(add1ToBinary(flipBits(convertOctalToBinary(atoll(argument)*-1)))));
        printf( "%14s%d", " -",convertBinaryToDecimal(add1ToBinary(flipBits(convertOctalToBinary(atoll(argument)*-1)))));
        printf("\t\t\t\t %12s%s","FFFFF", convertBinaryToHex(add1ToBinary(flipBits(convertOctalToBinary(atoll(argument)*-1)))));
    }
}
void validbase8NegPrint(char* argument){

    if(atoll(argument) == -1){
        printf("\nBase  8: %28s %16s" , "37777", " -1");
        printf("\t\t\t\t %14s","FFFF");
    }
    else{
        printf("\nBase  8: ");
        printf( "%24s%d", "37",  (77777 - convertBinaryToOctal((convertOctalToBinary( atoll(argument)*-1))) + 1));
        printf( "%14s%d", " -", convertBinaryToDecimal(convertOctalToBinary(atoll(argument)*-1)));
        printf("\t\t\t\t %12s%s","FFFFF", convertBinaryToHex(add1ToBinary(flipBits(convertOctalToBinary(atoll(argument)*-1)))));
    }
}
void validbase10NegPrint(char* argument){
  
    if(atoll(argument) == -1){
        printf("\nBase 10: %28s %16s" , "37777", " -1");
        printf("\t\t\t\t %14s","FFFF");
    }
    else{

        printf( "\nBase 10: ");
        printf("%24s%d " , "37",  (77777 - convertBinaryToOctal((convertDecimalToBinary( atoll(argument)*-1))) + 1));
        printf("%15d", atoi(argument)); 
        printf("\t\t\t\t %12s%s","FFFFF", convertBinaryToHex(add1ToBinary(flipBits(convertDecimalToBinary(atoll(argument)*-1)))));
    }

}
void validbase16NegPrint(char* argument){
    if(atoll(argument) == -1){
        printf("\nBase 16: %28s %16s" , "37777", " -1");
        printf("\t\t\t\t %14s","FFFF");
    }
    else{
        // removing - sign 
        char* newArg = remove1stElement(argument);
        printf( "\nBase 16: ");
        printf("%24s%d" , "37", (77777 - convertBinaryToOctal((convertHexToBinary(newArg))) + 1));
        printf("%14s%d", " -", convertBinaryToDecimal(convertHexToBinary(newArg))); 
        printf("\t\t\t\t %12s%s","FFFFF", convertBinaryToHex(add1ToBinary(flipBits(convertHexToBinary(newArg)))));
    }

}
//-----------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------
// Helper function 
//-----------------------------------------------------------------------------------------------------------------------------
char* remove1stElement(char* argument){
    char* newArg;
    newArg = malloc (sizeof (char) * 32);
    int i, index=0;
    for(i=0;i<strlen(argument);i++){
        if(i != 0){
            newArg[index++] = argument[i];
        }
    }
    newArg[index] = '\0';
    // printf("\n ---- removed - : %s\n", newArg);
    return newArg;
}
//-----------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------
// Flip Bits for negatives
//-----------------------------------------------------------------------------------------------------------------------------
long long flipBits(long long pBinaryNumber){
    
    // printf("\n----- initial binary num %lld\n", pBinaryNumber);
    
    char newBinaryNumber[999];   
    memset(&newBinaryNumber, 0, sizeof(newBinaryNumber));
    char binaryNumber[999];
    memset(&binaryNumber, 0, sizeof(binaryNumber));
    
    sprintf(binaryNumber,"%lld", pBinaryNumber);
    // printf("function binary num %lld\n", binaryNumber);
    if(strlen(binaryNumber)%4 != 0){
        // printf("\nnot modulo 4 len");
        strrev(binaryNumber);
        while(strlen(binaryNumber)%4 != 0){
            strcat(binaryNumber,"0");
        }
        strrev(binaryNumber);
        // printf("\n -- after adjustment: %s ", binaryNumber);
    }
    int i;

    for(i=0; i < strlen(binaryNumber); i++){
        switch (binaryNumber[i])
        {
        case '1':
            newBinaryNumber[i] = '0';
            break;
        default:
            newBinaryNumber[i] = '1';
            break;
        }
    } 
    
    // printf("flipped binary num %s\n",newBinaryNumber);
    return atoll(newBinaryNumber);
}
long long add1ToBinary(long long pBinaryNumber){

    char newBinaryNumber[999];   
    memset(&newBinaryNumber, 0, sizeof(newBinaryNumber));   
    char binaryNumber[999];
   
    sprintf(binaryNumber,"%lld", pBinaryNumber);
    // printf("function binary num %lld\n", binaryNumber);
    if(strlen(binaryNumber)%4 != 0){
        // printf("\nnot modulo 4 len");
        strrev(binaryNumber);
        while(strlen(binaryNumber)%4 != 0){
            strcat(binaryNumber,"0");
        }
        strrev(binaryNumber);
        // printf("\n -- after adjustment: %s ", binaryNumber);
    }
    strrev(binaryNumber);
   
    if(pBinaryNumber == 1){
        newBinaryNumber[1] = '0';
        newBinaryNumber[0] = '1';
    }
    else if(pBinaryNumber == 0){

        newBinaryNumber[0] = '1';
    }
    else{
        int i,carry = 1;
        for(i=0; i < strlen(binaryNumber); i++){
        
            if(binaryNumber[i] == '0' && carry  == 1){
                // printf("\nadded -> 1 @ index %d\n", i);
                newBinaryNumber[i] = '1';
                carry = 0;
            }

            else if (binaryNumber[i] == '1' && carry == 1){
                // printf("\nadded -> 1 @ index %d\n", i);
                newBinaryNumber[i] = '1';
                carry =1;
            }

            else if(binaryNumber[i] == '1' && carry == 0){
                // printf("\nadded -> 1 @ index %d\n", i);
                newBinaryNumber[i] = '1';
                carry = 0;
            }

            else{
                // printf("\nadded -> 0 @ index %d\n", i);
                newBinaryNumber[i] = '0';
                carry = 0;
            }
        }
        if(carry == 1 ){
            newBinaryNumber[strlen(binaryNumber)] = '1';
        }
        strrev(newBinaryNumber);
    }
   // printf("\n----- after 1 added %s\n", newBinaryNumber);
    return atoll(newBinaryNumber);
}
//-----------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------
// Hex Conversions
//-----------------------------------------------------------------------------------------------------------------------------
long long convertHexToBinary(char* hex){

    char binaryNumber[9999];
    memset(&binaryNumber, 0, sizeof(binaryNumber));
    char* hexConstant[] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    int i;

    for(i=0; i <strlen(hex); i++){
       // printf("Curr char: %c\n", hex[i]);

        switch (hex[i])
        {
        case '0':
            strcat(binaryNumber, hexConstant[0]);
            break;
        case '1':
            strcat(binaryNumber, hexConstant[1]);
            break;
        case '2':
            strcat(binaryNumber, hexConstant[2]);
            break;
        case '3':
            strcat(binaryNumber, hexConstant[3]);
            break;
        case '4':
            strcat(binaryNumber, hexConstant[4]);
            break;
        case '5':
            strcat(binaryNumber, hexConstant[5]);
            break;
        case '6':
            strcat(binaryNumber, hexConstant[6]);
            break;
        case '7':
            strcat(binaryNumber, hexConstant[7]);
            break;
        case '8':
            strcat(binaryNumber, hexConstant[8]);
            break;
        case '9':
            strcat(binaryNumber, hexConstant[9]);
            break;
        case 'A':
        case 'a':
            strcat(binaryNumber, hexConstant[10]);
            break;
        case 'B':
        case 'b':
            strcat(binaryNumber, hexConstant[11]);
            break;
        case 'C':
        case 'c':
            strcat(binaryNumber, hexConstant[12]);
            break;
        case 'D':
        case 'd':
            strcat(binaryNumber, hexConstant[13]);
            break;
        case 'E':
        case 'e':
            strcat(binaryNumber, hexConstant[14]);
            break;
        case 'F':
        case 'f':
            strcat(binaryNumber, hexConstant[15]);
            break;
        default:
            printf("\nNOT A hex value: %c\n" , hex[i]);
            break;

        }
    }
    return atoll(binaryNumber);
}
//-----------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------
// Decimal Conversions
//-----------------------------------------------------------------------------------------------------------------------------
int convertDecimalToOctal(int decimalNumber){
    int octalNumber = 0, i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}
long long convertDecimalToBinary(int dec)
{   
    long long binaryNumber = 0;
    int remainder;
    long long i = 1;    
    int tmpdec = dec, tmpval= 0;
    
    while( tmpdec > 0)
    {
        tmpval = tmpdec%2;   
        binaryNumber += tmpval*i;
        tmpdec = tmpdec/2;
        i = i*10;
    }

    return binaryNumber;
}
//-----------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------
// Octal Conversions
//-----------------------------------------------------------------------------------------------------------------------------
int convertOctalToDecimal(int octalNumber)
{
    int decimalNumber = 0, i = 0;

    while(octalNumber != 0)
    {
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;
    return decimalNumber;
}
long long convertOctalToBinary(int oct) {
   
    int dec = 0;
    long long i = 0;
    long long bin = 0;

    // converting octal to decimal
    while (oct != 0) {
        dec += (oct % 10) * pow(8, i);
        ++i;
        oct /= 10;
    }
    i = 1;

   // converting decimal to binary
    while (dec != 0) {
        bin += (dec % 2) * i;
        dec /= 2;
        i *= 10;
    }

    return bin;
}
//-----------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------
// Binary Conversions
//-----------------------------------------------------------------------------------------------------------------------------
int convertBinaryToOctal(long long bin) {
    int oct = 0, dec = 0, i = 0;
    
    while (bin > 0) {
        dec += (bin % 10) * pow(2, i);
        ++i;
        bin /= 10;
    }
    i = 1;

    while (dec > 0) {
        oct += (dec % 8) * i;
        dec /= 8;
        i *= 10;
    }
    return oct;
}

int convertBinaryToDecimal(long long n) {
    int dec = 0, i = 0, rem;
    while (n > 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
  return dec;
}

char* convertBinaryToHex(long long pbinaryNumber){    
    if(pbinaryNumber == 0)
        return "0";

    int hexConstant[] = {0, 1, 10, 11, 100, 101, 110, 111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111};
    long long index, i, digit, tempBinary = pbinaryNumber;
    char * hex;
    
    hex = malloc (sizeof(char) * 32);
    
    index = 0;
    // hex -> binary 
    while(tempBinary > 0){
        // Group binary to last four digits 
        digit = tempBinary % 10000;
       // printf("\ndigit: %d", digit);
        for(i=0; i<16; i++) {
            if(hexConstant[i] == digit) {
                //printf("\nHex match index: %d\n ", i);
                if(i<10) {
                    hex[index] = (char)(i + 48);
                }
                else {
                    switch (i)
                    {
                    case 15:
                        hex[index] = 'F';    
                        break;
                    case 14:
                        hex[index] = 'E';    
                        break;
                    case 13:
                        hex[index] = 'D';    
                        break;
                    case 12:
                        hex[index] = 'C';    
                        break;
                    case 11:
                        hex[index] = 'B';    
                        break;
                    case 10: 
                        hex[index] = 'A';    
                        break;
                    default:
                        printf("Error what am i doing here");
                        break;
                    }
                }
                index++;
                break;
            }
        }
        tempBinary = tempBinary/10000;
    }

    hex[index] = '\0';
    strrev(hex);
    
    return hex;
}
//-----------------------------------------------------------------------------------------------------------------------------