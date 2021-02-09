#ifndef COURSEWORK2_TERMINAL_H
#define COURSEWORK2_TERMINAL_H

int initTerminal();
int quitTerminal();
void initSignal();
void toggleChangeLog();
void moveCursorTo(int x, int y);
void printHead();
void printText();
void printCommand(char *command);
struct PointInt *getScreenSize();
void moveScreenTo(long line, long col);
void arrowKeyHandler(char key);

#endif //COURSEWORK2_TERMINAL_H
