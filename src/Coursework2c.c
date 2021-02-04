#include<stdio.h>
#include "Terminal.h"
#include "unistd.h"

int main(int argc, char *argv[]){

    printf("\033[2J \033[;H");


    printf("Columns: %d\n", getTerminalColumns());

    printf("Rows: %d\n\b", getTerminalRows());

    if(setTerminal() != 0)
        return 400;

    while(1) {
        int c = -3;
        c = getchar();

        if(c == -3) {
            printf("HELLO\n");
            sleep((double)0.1);
            continue;
        }
        else {
            //arrow key detection: https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
            //cursor movement: https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
            if (c == '\033') { // if the first value is esc
                printExitQuestion(); // ask if exit

                c = getchar();

                if (c == '[') { // catch escape sequence

                    c = getchar();

                    switch (c) { // the real value
                        case 'A': //Up
                            //printf("A\n");
                            moveCursor('A');
                            break;
                        case 'B': //Down
                            //printf("B\n");
                            moveCursor('B');
                            break;
                        case 'C': //Right
                            //printf("\033[C");
                            moveCursor('C');
                            break;
                        case 'D': //Left
                            //printf("D\n");
                            moveCursor('D');
                            break;
                        default:
                            break;
                    }

                    flushInput();
                } else { // it is not meant to be an escape -> exit?

                    if (c == 'x') { // we want to quit

                        printf("\n");
                        if (resetTerminal() != 0)
                            return 401;

                        break;
                    } else { // nevermind
                        printf("\033[2K");
                        loadCursorLocation();
                        //printf("\033[2K \033[A");
                    }
                }
            } else {
                putchar(c);
            }
        }
    }

    if(resetTerminal() != 0)
        return 401;

    return 1;
}



//keytest: https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses
//ch = getch(); endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);