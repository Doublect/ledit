#include<stdio.h>

#include "Library.h"
#include "TextHandler.h"


void clearScreen(){
    printf("\033[2J \033[;H");
}

void clearLine(){
    printf("\033[2K");
}

void printHeadLine(struct PointInt *screenSize){
    printf("\033[H"); //Move cursor to top left corner

    char head[] = "LEditor";

    printf("\033[7m"); //start inverted formatting
    printf("%*c%s%*c", (screenSize->x - 8) / 2, ' ', head, (screenSize->x - 8) / 2 + 1, ' ');
    printf("\033[27m"); //stop inverted formatting
    putchar('\r');

}

void printTextLines(struct Point *screenPos, struct PointInt *screenSize){
    int writeableRows = screenSize->y - 2;

    //Move cursor to top left corner, then down by one
    printf("\033[H");
    moveCursor('B');

    int newLineNumberSize = longsize(writeableRows + screenPos->y) + 2;


    for(int row = 0; row < writeableRows; row++){
        int spaceCount = newLineNumberSize - longsize(row + screenPos->y + 1) - 1;
        int textSpace = screenSize->x - (newLineNumberSize + 1);

        char *string = getLine(row + screenPos->y, screenPos->x);

        if(string == NULL){
            printf("%ld%*c|\033[0K\r", row + screenPos->y + 1, spaceCount, ' ');
        } else {
            printf("%ld%*c|\033[0K %.*s\r", row + screenPos->y + 1, spaceCount, ' ', textSpace, string);
        }

        moveCursor('B');
    }
    putchar('\r');
}

void printStatusLine(char* command, struct PointInt *screenSize){
    //Get cursor location
    printf("\033[H\033[%dB", screenSize->y - 1); //1. move cursor to top left corner, 2. move cursor down to (0, rows - 1)

    //write(STDOUT_FILENO, "\033[2K", 4); //Clear last line

    //int curRow = screenY + y - 1; //The first row is the headline
    //int curCol = screenX + x;

    printf("\033[2K\033[7m%s\033[27m", command);
    //printf("\033[7mRow: %d, Col: %d%*c\033[27m", curRow, curCol, cols - 12 - intsize(curCol) - intsize(curRow), ' ');
}

void redrawScreen(struct Point *screenPos, struct PointInt *screenSize){
    clearScreen();
    printHeadLine(screenSize);
    printTextLines(screenPos, screenSize);
}