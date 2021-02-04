#include<unistd.h>     //STDIN_FILENO
#include<stdio.h>

//#include "Renderer.h"
#include "Terminal.h"
#include "Library.h"
#include "Reader.h"

static int screenX = 0, screenY = 0;
static int commandX = 0;
static int numberSize;

int getNumberSize(){
    return numberSize;
}

int *getScreenXptr(){
    return &screenX;
}

int *getScreenYptr(){
    return &screenY;
}

void clearScreen(){
    printf("\033[2J \033[;H");
}

void clearLine(){
    printf("\033[2K\r");
}

void printExitQuestion(){
    saveCursorLocation(); //save cursor location

    int rows = getTerminalRows(); // Get row count

    printf("\033[H\033[%dB", rows - 1); // 1. move cursor to top left corner, 2. move cursor down to (0, rows - 1)

    write(STDOUT_FILENO, "\033[2K", 4); // Clear last line

    printf("Do you want to exit? Press x.\r"); // Print message
}

void abortExit(){
    write(STDOUT_FILENO, "\033[2K", 4); // Clear last line
    loadCursorLocation();
}

// Fills the area with spaces which are formatted inversely, leaves cursor at position
void printSpace(int startX, int startY, int endX, int endY){
    if(startX > endX || startY > endY)
        return;

    for(int y = startY; y <= endY; y++){
        printf("\033[%d;%dH", y, startX); //Jump to the row we're drawing over

        printf("%*c\r", startX - endX + 1, ' ');
    }
}

void printHeadLine(){
    saveCursorLocation();

    // get terminal size
    int rows = getTerminalRows();
    int cols = getTerminalColumns();    

    printf("\033[H"); //Move cursor to top left corner

    char head[] = "LEditor";

    printf("\033[7m"); //start inverted formatting
    printf("%*c%s%*c", (cols - 8) / 2, ' ', head, (cols - 8) / 2 + 1);
    printf("\033[27m"); //stop inverted formatting
    putchar('\r');

    loadCursorLocation();
}

void printStatusLine(char* command){

    saveCursorLocation();

    //Get terminal size
    int rows = getTerminalRows();
    int cols = getTerminalColumns();

    //Get cursor location
    //int x, y;
    //getCursorPosition(&x, &y);

    printf("\033[H\033[%dB", rows - 1); //1. move cursor to top left corner, 2. move cursor down to (0, rows - 1)

    //write(STDOUT_FILENO, "\033[2K", 4); //Clear last line

    //int curRow = screenY + y - 1; //The first row is the headline
    //int curCol = screenX + x;

    printf("\033[2K\033[7m%s\033[27m", command);
    //printf("\033[7mRow: %d, Col: %d%*c\033[27m", curRow, curCol, cols - 12 - intsize(curCol) - intsize(curRow), ' ');

    loadCursorLocation();
}

void printLineNumbers(){
    saveCursorLocation();

    int writeablerows = getTerminalRows() - 2;

    //Move cursor to top left corner, then down by one
    printf("\033[H"); 
    moveCursor('B');

    int newLineNumberSize = intsize(writeablerows + screenY) + 2;


    for(int row = 0; row < writeablerows; row++){
        int spaceCount = newLineNumberSize - intsize(row + screenY + 1) - 1;
        int textSpace = getTerminalColumns() - (newLineNumberSize + 1);

        printf("%d%*c$\033[0K %.*s\r", (row + screenY + 1), spaceCount, ' ', textSpace, getLine((row + screenY), screenX));

        moveCursor('B');
    }
    putchar('\r');

    numberSize = newLineNumberSize;
    loadCursorLocation();
}

void redrawScreen(){
    saveCursorLocation();

    clearScreen();

    loadCursorLocation();

    printHeadLine();
    printLineNumbers();
    //printStatusLine();
}