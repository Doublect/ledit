#include <stdio.h>
#include <string.h>

#include "Terminal.h"
#include "Commands.h"
#include "TextHandler.h"
#include "ChangeLog.h"
#include "definitions.h"


int quit(){
    int exitsignal = 0;

    if((exitsignal = quitTerminal())) return exitsignal;

    quitCommands();

    return 0;
}

int main(int argc, char *argv[]){

    int exitsignal = 0;
    int signal;

    if(argc == 2) {
        readFile(argv[1]);
        initChange(argv[1]);
    }

    if((exitsignal = initTerminal())) return exitsignal;

    initCommands();

    initSignal();

    while(1) {
        //fgets(input, sizeof input, stdin);

        char c = (char)getchar();


        //arrow key detection: https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
        //cursor movement: https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
        switch (c) {
            case -1: // When changing terminal screen size, a character with value '-1' was being inputted
                break;
            case '\033':
                c = (char)getchar();
                if (c == '[') { // catch escape sequence
                    c = (char)getchar();
                    arrowKeyHandler(c);
                }
                continue;
            case 127: // Backspace
                deleteCharacter();
                break;
            case 13: // Enter
                signal = executeCommand();
                if (signal == QUIT) return quit();

                initCommands();
                break;
            default:
                insertCharacter(c);
                break;
        }
    }
}



//keytest: https://stackoverflow.com/questions/9750588/how-to-get-ctrl-shift-or-alt-with-getch-ncurses
//ch = getch(); endwin(); printf("KEY NAME : %s - %d\n", keyname(ch),ch);