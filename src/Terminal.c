#include <sys/ioctl.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include <stdio.h>
#include <stdlib.h> //calloc
#include <signal.h>

#include "Renderer.h"
#include "Terminal.h"
#include "Library.h"
#include "Commands.h"

//Based upon: https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c

#define True 1
#define False 0

static struct termios oldt, newt;
static int savedX,  savedY;


// Mouse scroll: https://stackoverflow.com/questions/8476332/writing-a-real-interactive-terminal-program-like-vim-htop-in-c-c-witho
//https://cboard.cprogramming.com/c-programming/130243-non-blocking-getchar.html -> timeout
int setTerminal(){
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);

    // Save terminal settings
    newt = oldt;
    
    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    //newt.c_lflag &= ~(ICANON | ECHO | ECHOCTL);

    /* Raw mode:*/

    newt.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | ICRNL | IXON);
    newt.c_oflag &= ~OPOST;
    newt.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    newt.c_cflag &= ~(CSIZE | PARENB);
    newt.c_cflag |= CS8;


    //newt.c_cc[VTIME] = 0;
    //newt.c_cc[VMIN] = 0;

    // Write terminal settings for editor session
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    return 0;
}

///Restore original terminal settings
int resetTerminal(){
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}

int quit(){
    printf("\n\r");
    moveCursorTo(0, 0);
    printf("\033[2J");

    if(resetTerminal() != 0) {
        return 302;
    }

    return 0;
}

int getTerminalColumns(){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    return w.ws_col;
}

int getTerminalRows(){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    return w.ws_row;
}

void getCursorPosition(int *xpos, int *ypos){

    // Allocate strings for the characters (numbers)
    char *xstr = malloc(50);
    char *ystr = malloc(50);

    // Store start position of array
    char *x = xstr, *y = ystr;

    // VT100 request to print cursor position, the response has the format \033[row;columnR
    write(1, "\033[6n", 4);


    // Loop and get all numbers between [ and ;
    char in;

    while((in = getchar()) != ';'){ // Loop over all characters until ;
        if(isNumber(in)) { // Make sure it is a number
            *y = in; // Save number
            y++; // Move pointer by 1
        }
    }

    // Loop and get all numbers between ; and R
    while((in = getchar()) != 'R'){
        if(isNumber(in)) { // Make sure it is a number
            *x = in; // Save number
            x++; // Move number string pointer by 1
        }
    }

    // Null-terminate strings
    *x = '\0';
    *y = '\0';

    // Get number from null-terminated string
    *xpos = strtoint(xstr);
    *ypos = strtoint(ystr);

    // Free memory
    free(xstr);
    free(ystr);
}

void saveCursorLocation(){
    getCursorPosition(&savedX, &savedY);
}

void WINCHSignal(int signal){
    // If window has changed, redraw
    redrawScreen();

    int x, y;
    getCursorPosition(&x, &y);

    moveCursorTo(x, getTerminalRows());
}

// TODO: Handle exit signals
void SIGINTSignal(int signal){
}

void initSignal(){
    struct sigaction sigHandler = {{0}};

    sigHandler.sa_handler = WINCHSignal;
    sigaction(SIGWINCH, &sigHandler, NULL);

    sigHandler.sa_handler = SIGINTSignal;
    sigaction(SIGINT, &sigHandler, NULL);
    sigaction(SIGQUIT, &sigHandler, NULL);
}

void moveCursorTo(int x, int y){
    printf("\033[%d;%dH", y, x);
}

void loadCursorLocation(){
    //VT100 escape code to move cursor
    printf("\033[%d;%dH", savedY, savedX);
}

void moveCursor(char key){
    printf("\033[%c", key);
}

void controlArrowHandler(char key){
    long *screenY = getScreenYptr();
    long *screenX = getScreenXptr();

    switch (key) { // The real value
        case 'A': //Up
            if(*screenY > 0){
                (*screenY) -= (*screenY <= 2) ?  (*screenY) : 3;
                printTextLines();
            }
            return;
        case 'B': //Down
            (*screenY) += 3;
            printTextLines();
            return;
        case 'C': //Right
            (*screenX) += 5;
            printTextLines();
            return;
        case 'D': //Left
            if(*screenX > 0){
                (*screenX) -= (*screenX < 5) ?  (*screenX) : 5;
                printTextLines();
            }
            return;
        default:
            break;
    }
}

void altArrowHandler(char key){
    long *screenY = getScreenYptr();
    long *screenX = getScreenXptr();

    switch (key) { // the real value
        case 'A': //Up
            if(*screenY > 0){
                (*screenY)--;
                printTextLines();
            }
            return;
        case 'B': //Down
            (*screenY)++;
            printTextLines();
            return;
        case 'C': //Right
            (*screenX)++;
            printTextLines();
            return;
        case 'D': //Left
            if(*screenX > 0){
                (*screenX)--;
                printTextLines();
            }
            return;
        default:
            break;
    }
}

void arrowKeyHandler(char key){
    switch (key) { // the real value
        case 'A': //Up
            // TODO: Command history
            return;
        case 'B': //Down
            // TODO: Command history
            return;
        case 'C': //Right
            if(moveCursorRight()){
                moveCursor('C');
            }
            return;
        case 'D': //Left
            if(moveCursorLeft()){
                moveCursor('D');
            }
            return;
        case '1': // Pressing ctrl/alt + arrow key Output is of form: "1;5"/"1;3" + 'A-D'
            getchar(); // Eat ';' input

            if((key = getchar()) == '5') // Check whether it is alt or ctrl (5 = ctrl)
                return controlArrowHandler(getchar()); // Get direction and pass it to handler
            else if(key == '3')
                return altArrowHandler(getchar());
            break;
        default:
            break;
    }
}