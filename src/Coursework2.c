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
        
    //setvbuf(stdout, NULL, _IONBF, 0);

    clearScreen();

    printHeadLine();

    //printf("\r");

    printTextLines();

    initializeCommands();

    initSignal();

    while(1) {
        char c = getchar();

        //mnextInput(&c[0], 50, 3);
        //arrow key detection: https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
        //cursor movement: https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
        if (c == '\033') { // if the first value is esc
            c = getchar();
            if (c == '[') { // catch escape sequence
                c = getchar();
                arrowKeyHandler(c);
            }
        } else if(c == 127) { // If backspace
            deleteCharacter();
        } else if(c == 13) { // If enter
            int signal = executeCommand();

            if(signal == QUIT) break;

            initializeCommands();
        } else {
            insertCharacter(c);
        }
    }

    quit();

    return 0;
}



//keytest: https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses
//ch = getch(); endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);