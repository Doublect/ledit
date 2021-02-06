#ifndef COURSEWORK2_READER_H
#define COURSEWORK2_READER_H

void readFile(char *path);
char *getLine(int pos, int offset);
void writeFile(char *path, int bunload);
void setLine(char *string, int pos);

#endif //COURSEWORK2_READER_H
