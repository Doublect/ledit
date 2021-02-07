#include <unistd.h> //STDOUt_FILENO, write
#include <stdio.h>
//Defined in features.h (<- unistd.h)
//#define __USE_POSIX199309
//#define _POSIX_C_SOURCE 199309L

//#ifdef WIN32
//#include <windows.h>
//#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
//#else
//#include <unistd.h> // for usleep
//#endif

#include "definitions.h"

//Print null-terminated string
void strprint(char * str){
    for(; *str; str++){
        write(STDOUT_FILENO, str, 1);
    }
}

int isNumber(char c){
    if(c >= '0' && c <= '9'){
        return True;
    }
    return False;
}

int isNumberStr(char *c){
    for(; *c; c++){
        if(!isNumber(*c)){
            return False;
        }
    }
    return True;
}

//Limited to size 10, because of int
int strtoint(char *str){
    int ans = 0;
    for(int i = 0; i < 10 && *str; str++, i++){
        if(isNumber(*str)){
            ans *= 10;
            ans += *str - '0';
        }
    }
    return ans;
}

long strtolong(char *str){
    long ans = 0;
    for(int i = 0; i < 19 && *str; str++, i++){
        if(isNumber(*str)){
            ans *= 10;
            ans += *str - '0';
        }
    }
    return ans;
}

//Returns the number of digits in an int
int intsize(int x){
    if(x < 0) x *= -1;

    if(x < 10) return 1;
    if(x < 100) return 2;
    if(x < 1000) return 3;
    if(x < 10000) return 4;
    if(x < 100000) return 5;
    if(x < 1000000) return 6;
    if(x < 10000000) return 7;
    if(x < 100000000) return 8;
    if(x < 1000000000) return 9;

    return 10;
}

int longsize(long x){
    if(x < 0) x *= -1;

    if(x < 10) return 1;
    if(x < 100) return 2;
    if(x < 1000) return 3;
    if(x < 10000) return 4;
    if(x < 100000) return 5;
    if(x < 1000000) return 6;
    if(x < 10000000) return 7;
    if(x < 100000000) return 8;
    if(x < 1000000000) return 9;
    if(x < 10000000000) return 10;
    if(x < 100000000000) return 11;
    if(x < 1000000000000) return 12;
    if(x < 10000000000000) return 13;
    if(x < 100000000000000) return 14;
    if(x < 1000000000000000) return 15;
    if(x < 10000000000000000) return 16;
    if(x < 100000000000000000) return 17;
    if(x < 1000000000000000000) return 18;

    return 19;
}

void moveCursor(char key){
    printf("\033[%c", key);
}

void terminalCommand(char *input){
    printf("\033[%s", input);
}
