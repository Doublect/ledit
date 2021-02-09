#ifndef COURSEWORK2_RENDERER_H
#define COURSEWORK2_RENDERER_H
#include "Library.h"

void clearScreen();
void clearLine();
void printHeadLine(struct PointInt *screenSize);
void printTextLines(struct Point *screenPos, struct PointInt *screenSize, int bChangeLog);
void printStatusLine(char* command, struct PointInt *screenSize);
void redrawScreen(struct Point *screenPos, struct PointInt *screenSize, int bChangeLog);

#endif //COURSEWORK2_RENDERER_H