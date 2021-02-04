#ifndef COURSEWORK2_TERMINAL_H
#define COURSEWORK2_TERMINAL_H

int setTerminal();
int resetTerminal();
int quit();
int getTerminalColumns();
int getTerminalRows();
void getCursorPosition();
void moveCursorTo(int x, int y);
void saveCursorLocation();
void loadCursorLocation();
void moveCursor(char key);
void nextInput(char *c);
void mnextInput(char *c, int milliseconds, int elements);
void arrowKeyHandler(char key);

#endif //COURSEWORK2_TERMINAL_H
