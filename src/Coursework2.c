#include <stdio.h>
#include <unistd.h>

#include "Renderer.h"
#include "Terminal.h"
#include "Commands.h"
#include "TextHandler.h"
#include "definitions.h"

int main(int argc, char *argv[]){

    if(argc == 2)
        readFile(argv[1]);

    if(setTerminal() != 0)
        return 301;
        
    setvbuf(stdout, NULL, _IONBF, 0);

    clearScreen();

    printHeadLine();

    //moveCursor('B');
    printf("\r");
    
    printLineNumbers();

    moveCursorTo(1, getTerminalRows());

    initializeCommands();

    while(1) {
        char c[3] = "\0";

        //mnextInput(&c[0], 50, 3);
        c[0] = getchar();
        //arrow key detection: https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
        //cursor movement: https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
        if (c[0] == '\033') { // if the first value is esc
            c[1] = getchar();
            if (c[1] == '[') { // catch escape sequence
                c[2] = getchar();
                arrowKeyHandler(c[2]);
            }
        } else if(c[0] == 127) {
            deleteCharacter();
        } else if(c[0] == 13) {
            int signal = executeCommand();

            if(signal == QUIT) break;

            if(signal == SAVE) writeFile(NULL, False);

            initializeCommands();
        } else {
            insertCharacter(c[0]);
        }

        //redrawScreen();
    }

    quit();

    return 0;
}



//keytest: https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses
//ch = getch(); endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);