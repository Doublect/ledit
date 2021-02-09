#include <sys/ioctl.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "Renderer.h"
#include "Library.h"
#include "Commands.h"

//Based upon: https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c

#define True 1
#define False 0

static struct termios oldt, newt;
static int savedX,  savedY;

static struct PointInt screenSize = {0, 0};
static struct Point screenPos = {0, 0};




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
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    return 0;
}

int setCREAD(int bon){
    if(bon) {
        newt.c_cflag |= CREAD;
    } else {
        newt.c_cflag &= ~CREAD;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void updateScreenSize(){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    screenSize.x = w.ws_col;
    screenSize.y = w.ws_row;
}

struct PointInt *getScreenSize(){
    return &screenSize;
}

int initTerminal(){

    if(setTerminal()) return 301;

    updateScreenSize();

    clearScreen();

    printHeadLine(&screenSize);

    //printf("\r");

    printTextLines(&screenPos, &screenSize);

    return 0;
}

///Restore original terminal settings
int resetTerminal(){
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}

void moveCursorTo(int x, int y){
    printf("\033[%d;%dH", y, x);
}

int quitTerminal(){
    printf("\n\r");
    moveCursorTo(0, 0);
    printf("\033[2J");

    if(resetTerminal() != 0) {
        return 302;
    }

    return 0;
}

void getCursorPosition(int *xpos, int *ypos){

    // Disables input recieving
    setCREAD(False);

    // VT100 request to print cursor position, the response has the format \033[row;columnR
    printf("\033[6n");


    // Eat all other inputs, until the response begins
    char c;
    while((c = (char)getchar()) != '\033');

    scanf("[%d;%dR", ypos, xpos); // NOLINT(cert-err34-c)

    // Enable input
    setCREAD(True);
}

void saveCursorLocation(){
    getCursorPosition(&savedX, &savedY);
}

void loadCursorLocation(){
    //VT100 escape code to move cursor
    printf("\033[%d;%dH", savedY, savedX);
}

void WINCHSignal(int signal){
    updateScreenSize();

    // If window has changed, redraw
    saveCursorLocation();
    redrawScreen(&screenPos, &screenSize);
    loadCursorLocation();

    int x, y;
    getCursorPosition(&x, &y);

    moveCursorTo(x, screenSize.y);
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

void printText(){
    saveCursorLocation();
    printTextLines(&screenPos, &screenSize);
    loadCursorLocation();
}

void printCommand(char *command){
    saveCursorLocation();
    printStatusLine(command, &screenSize);
    loadCursorLocation();
}

void controlArrowHandler(char key){
    switch (key) { // The real value
        case 'A': //Up
            if(screenPos.y > 0){
                (screenPos.y) -= (screenPos.y <= 2) ? (screenPos.y) : 3;
                printText();
            }
            break;
        case 'B': //Down
            (screenPos.y) += 3;
            printText();
            break;
        case 'C': //Right
            (screenPos.x) += 5;
            printText();
            break;
        case 'D': //Left
            if(screenPos.x > 0){
                (screenPos.x) -= (screenPos.x < 5) ? (screenPos.x) : 5;
                printText();
            }
            break;
        default:
            break;
    }
}

void altArrowHandler(char key){

    switch (key) { // the real value
        case 'A': //Up
            if(screenPos.y > 0){
                screenPos.y--;
                printText();
            }
            break;
        case 'B': //Down
            screenPos.y++;
            printText();
            break;
        case 'C': //Right
            screenPos.x++;
            printText();
            break;
        case 'D': //Left
            if(screenPos.x > 0){
                screenPos.x--;
                printText();
            }
            break;
        default:
            break;
    }
}

void arrowKeyHandler(char key){
    switch (key) { // the real value
        case 'A': //Up
            // TODO: Command history
            break;
        case 'B': //Down
            // TODO: Command history
            break;
        case 'C': //Right
            if(moveCursorRight()){
                moveCursor('C');
            }
            break;
        case 'D': //Left
            if(moveCursorLeft()){
                moveCursor('D');
            }
            break;
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