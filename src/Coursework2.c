#include <stdio.h>
#include <unistd.h>

#include "Terminal.h"
#include "Commands.h"
#include "TextHandler.h"
#include "definitions.h"

int main(int argc, char *argv[]){

    int exitsignal = 0;
    if(argc == 2)
        readFile(argv[1]);
        
    //setvbuf(stdout, NULL, _IONBF, 0);

    if((exitsignal = initTerminal())) return exitsignal;

    initializeCommands();

    initSignal();

    while(1) {
        char c = getchar();

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