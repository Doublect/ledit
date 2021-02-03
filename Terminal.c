#include <sys/ioctl.h>
#include<termios.h>            //termios, TCSANOW, ECHO, ICANON
#include<unistd.h>     //STDIN_FILENO
#include<stdio.h>
#include<time.h>
#include<stdlib.h> //calloc

#include "Renderer.h"
#include "Terminal.h"
#include "Library.h"

//Based upon: https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c


static struct termios oldt, newt;
static int savedX,  savedY;
static int lastrow, lastcol;

//https://cboard.cprogramming.com/c-programming/130243-non-blocking-getchar.html -> timeout
int setTerminal(){
    // Get current terminal settings
    tcgetattr( STDIN_FILENO, &oldt);

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


    newt.c_cc[VTIME] = 0;
    newt.c_cc[VMIN] = 0;

    // Write terminal settings for editor session
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    // Initialize terminal size tracking
    lastcol = getTerminalColumns();
    lastrow = getTerminalRows();

    return 0;
}

int resetTerminal(){
    // Restore terminal settings
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

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

void checkTerminalSize(){
    int curcol = getTerminalColumns();
    int currow = getTerminalRows();


    if(lastcol != curcol || lastrow != currow){
        redrawScreen();

        lastcol = curcol;
        lastrow = currow;
    }
}

void getCursorPosition(int *xpos, int *ypos){

    // Allocate strings for the characters (numbers)
    char *xstr = malloc(9);
    char *ystr = malloc(9);

    // Store start position of array
    char *x = xstr, *y = ystr;

    // VT100 request to print cursor position, the response has the format \033[row;columnR
    write(1, "\033[6n", 4);


    // Loop and get all numbers between [ and ;
    char in;
    nextInput(&in);
    while(in != ';'){
        if(isNumber(in) == 0){
            *y = in; // Save number
            y++; // Move pointer by 1

        }
        nextInput(&in); // Get next number
    }

    // Loop and get all numbers between ; and R
    while(in != 'R'){
        if(isNumber(in) == 0){
            *x = in; //save number
            x++; //move number
        }
        nextInput(&in); // Get next number
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

void nextInput(char *c){
    while(read(STDIN_FILENO, c, 1) == 0){
        checkTerminalSize();
        msleep(50);
    }
}

void mnextInput(char *c, int milliseconds, int elements){
    while(read(STDIN_FILENO, c, elements) == 0){
        checkTerminalSize();
        msleep(milliseconds);
    }
}

void arrowKeyHandler(char key){

    // Store cursor position
    int x, y;
    getCursorPosition(&x, &y);


    int *screenX = getScreenXptr(), *screenY = getScreenYptr();

    switch (key) { // the real value
        case 'A': //Up
            if(y == 2){
                if(*screenY > 0){
                    (*screenY)--;
                    printLineNumbers();
                }
                return;
            } else {
                moveCursor('A');
            }
            break;
        case 'B': //Down
            if(y == (getTerminalRows() - 1)){
                (*screenY)++;
                printLineNumbers();
                return;
            } else {
                moveCursor('B');
            }
            break;
        case 'C': //Right
            if(x == (getTerminalColumns())){
                (*screenX)++;
            } else {
                moveCursor('C');
            }
            break;
        case 'D': //Left
            if(x == getNumberSize() + 1){
                if(*screenX > 0){
                    (*screenX)--;
                }
                return;
            } else {
                moveCursor('D');
            }
            break;
        default:
            break;
    }
}