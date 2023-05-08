#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void unitTest_firstLetterBig(char* s){

    if(isupper(s[0])){
        printf("First name is uppercase, Correct //");
    }else{
        printf("First name is NOT uppercase, False //");
    }

}

void unitTest_validEmail(char* s){

    if(strchr(s,'@')){
        printf("It is a valid Email, Correct //");
    }else{
        printf("It is NOT a valid Email, False //");
    }

}