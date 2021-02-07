#include<stdio.h>
#include <unistd.h>
#include "Terminal.h"
//#include "Library.h"
#include <stdlib.h>
//#include "Reader.h"

int main(int argc, char *argv[]) {
    setTerminal();

    /*
    if(argc == 2) {
        //readFile(argv[1]);
        FILE *fptr = fopen(argv[1], "r");
        char *string = malloc(sizeof (char )*1024);
        while(fgets(string, 1024, fptr) != NULL){
            printf("%s", string);
        }
    }*/

    putchar('\n');
    while (1) {
        char c = getchar();
        //read(STDIN_FILENO, &c, 1);

        if(c == 'a') break;

        if(c == 's') saveCursorLocation();

        //putchar(c);
        //putchar('\n');
        //mnextInput(&c, 40, 1);
        //printLineNumbers();

        //printf("%c %d\n", c, c);
    }

    quit();

    return 0;
}