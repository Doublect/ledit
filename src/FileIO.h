//
// Created by doublect on 2021. 02. 03..
//

#ifndef COURSEWORK2_FILEIO_H
#define COURSEWORK2_FILEIO_H

int readTextFile(char *filepath, char *(*(*filecontentsptr)), long *fileContentsCapacity, long *linecount, long **linelength, long **linecapacity);
int readFromFile(char *filepath, char ***filecontents, long *linecount, long *capacity);
int writeToFile(char *filepath, char ***filecontents, long linecount);

#endif //COURSEWORK2_FILEIO_H
