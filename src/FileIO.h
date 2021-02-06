//
// Created by doublect on 2021. 02. 03..
//

#ifndef COURSEWORK2_FILEIO_H
#define COURSEWORK2_FILEIO_H

int readTextFile(char *filepath, char *(*(*filecontentsptr)), int *fileContentsCapacity, int *linecount, int **linelength, int **linecapacity);
int writeTextFile(char *filepath, char *(*(*filecontentsptr)), int *fileContentsCapacity, int *linecount, int **linelength, int **linecapacity);

#endif //COURSEWORK2_FILEIO_H
