#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

int isNumber(char c){
    if(c >= '0' && c <= '9'){
        return True;
    }
    return False;
}

int isNumberStr(char *c){
    int len = (int)strlen(c);
    for(int i = 0; i < len; i++){
        if(!isNumber(c[i])){
            return False;
        }
    }
    return True;
}

//Limited to size 10, because of int
int strtoint(char *str){
    int ans = 0;
    int len = (int)strlen(str);

    for(int i = 0; i < 10 && i < len; i++){
        if(isNumber(str[i])){
            ans *= 10;
            ans += str[i] - '0';
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

void changeStringArrayCapacity(char ***text, long count, long *capacity, long delta) {
    if(delta == 0) return;

    // Make sure we don't have negative number of lines
    if(delta + *capacity < 0) {
        delta = -*capacity;
    }

    char **newtext = calloc(*capacity + delta, sizeof(char *));
    char **oldtext = *text;
    // Copy over the lines, make sure to only copy the number of elements we need
    long copyAmount = (((*capacity + delta) < count) ? *capacity + delta : count);

    for(long i = 0; i < copyAmount; i++){
        newtext[i] = oldtext[i];
    }

    // Free strings which are less than the copied
    for(long i = copyAmount; i < count; i++){
        free(oldtext[i]);
    }

    // Update pointer
    *text = newtext;

    // Update *capacity
    *capacity += delta;
}