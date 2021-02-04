#include<stdio.h>
#include "Terminal.h"
//#include "Library.h"
#include "unistd.h"
//#include <stdlib.h>
#include "Reader.h"

int main(int argc, char *argv[]) {
    setTerminal();

    if(argc == 2)
        readFile(argv[1]);


    /*while (1) {
        char c;
        read(STDIN_FILENO, &c, 1);

        if(c == 'a') break;

        if(c == '\127') {
            putchar('H');
            //putchar('\n');
        }

        if(c == 127){
            putchar('H');
        }
        //putchar(c);
        //putchar('\n');
        //mnextInput(&c, 40, 1);
        //printLineNumbers();

        printf("%c %d\n", c, c);
    }*/

    resetTerminal();

    return 0;
}