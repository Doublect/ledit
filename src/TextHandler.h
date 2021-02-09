#ifndef COURSEWORK2_READER_H
#define COURSEWORK2_READER_H

void readFile(char *path);
char *getLine(long pos, long offset);
void unloadText();
void writeTextFile(char *path, int bunload);
void setLine(char *string, long pos, long len);
void swapLines(long posA, long posB);
void deleteLines(long posStart, long posEnd);
void removeFile(char *path);

#endif //COURSEWORK2_READER_H
