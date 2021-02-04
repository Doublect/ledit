#ifndef COURSEWORK2_RENDERER_H
#define COURSEWORK2_RENDERER_H

int getNumberSize();
int *getScreenXptr();
int *getScreenYptr();
void clearScreen();
void clearLine();
void printExitQuestion();
void abortExit();
void printHeadLine();
void printLineNumbers();
void printStatusLine(char* command);
void redrawScreen();

#endif //COURSEWORK2_RENDERER_H