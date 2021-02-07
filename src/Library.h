#ifndef COURSEWORK2_LIBRARY_H
#define COURSEWORK2_LIBRARY_H
struct Point {
    long x;
    long y;
};

struct PointInt {
    int x;
    int y;
};

int isNumber(char c);
int isNumberStr(char *c);
int strtoint(char *str);
long strtolong(char *str);
int intsize(int x);
int longsize(long x);
void moveCursor(char key);
void terminalCommand(char *input);

#endif //COURSEWORK2_LIBRARY_H
