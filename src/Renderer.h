#ifndef COURSEWORK2_RENDERER_H
#define COURSEWORK2_RENDERER_H

int getNumberSize();
long *getScreenXptr();
long *getScreenYptr();
void clearScreen();
void clearLine();
void printHeadLine();
void printTextLines();
void printStatusLine(char* command);
void redrawScreen();

#endif //COURSEWORK2_RENDERER_H