#include<stdio.h>
#include "Terminal.h"
#include "unistd.h"

int main(int argc, char *argv[]){

    printf("\033[2J \033[;H");


    printf("Columns: %d\n", getTerminalColumns());

    printf("Rows: %d\r", getTerminalRows());

    if(setTerminal() != 0)
        return 400;

    while(1) {
        char c;

        if((c = getchar()) == EOF) {
            sleep((double)0.1);
            continue;
        }
        else {
            //arrow key detection: https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
            //cursor movement: https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
            if ((c = getchar()) == '\033') { // if the first value is esc

                if (read(STDIN_FILENO, &c, 1) == 0) {
                    printExitQuestion();

                    while (read(STDIN_FILENO, &c, 1) == 0) {
                        sleep((double) 0.02);
                    }

                    if (c[0] == 'x') { // skip the [ and catch quit
                        printf("\n");
                        if (resetTerminal() != 0)
                            return 401;

                        break;
                    } else {
                        //printf("\033[1K");
                        //loadCursorLocation();
                        //printf("\033[2K \033[A");
                        continue;
                    }
                } else if (c[0] == '[') {
                    if (read(STDIN_FILENO, &c, 1) == -1)
                        continue;

                    switch (c[0]) { // the real value
                        case 'A': //Up
                            moveCursor('A');
                            //arrowKeyHandler('A');
                            break;
                        case 'B': //Down
                            //arrowKeyHandler('B');
                            break;
                        case 'C': //Right
                            //arrowKeyHandler('C');
                            break;
                        case 'D': //Left
                            //arrowKeyHandler('D');
                            break;
                    }
                }
            } else {
                //putchar(c[0]);
            }
        }
    }

    if(resetTerminal() != 0)
        return 401;

    return 1;
}



//keytest: https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses
//ch = getch(); endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);