#include <stdio.h>
#include <unistd.h>

#include "Renderer.h"
#include "Terminal.h"

int main(int argc, char *argv[]){

    if(setTerminal() != 0)
        return 301;
        
    setvbuf(stdout, NULL, _IONBF, 0);

    clearScreen();

    printHeadLine();

    moveCursor('B');
    printf("\r");
    
    printLineNumbers();

    printStaticElements();

    moveCursorTo(getNumberSize() + 1, 2);

    while(1) {
        char c[3] = "\0";

        mnextInput(&c[0], 50, 3);

        //arrow key detection: https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
        //cursor movement: https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
        if (c[0] == '\033') { // if the first value is esc
            //printf("\033[6n");
            if (c[1] == '[') { // catch escape sequence
                arrowKeyHandler(c[2]);
            } else if(c[1] == '\0') {
                printExitQuestion();

                mnextInput(c, 50, 1);

                if(c[0] == 'x'){
                    break;

                } else {
                    abortExit();
                    putchar(c[0]);
                }
            }

        } else {
            putchar(c[0]);
        }

        printStaticElements();
    }

    printf("\n\r");
    moveCursorTo(0, 0);
    printf("\033[2J");

    if(resetTerminal() != 0)
        return 302;

    return 1;
}



//keytest: https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses
//ch = getch(); endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);