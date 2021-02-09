//
// Created by doublect on 2021. 02. 03..
//

#ifndef COURSEWORK2_FILEIO_H
#define COURSEWORK2_FILEIO_H

int readTextFile(char *filepath, char *(*(*filecontentsptr)), long *fileContentsCapacity, long *linecount, long **linelength, long **linecapacity);
int readChangeFile(char *filepath, char ***filecontents, long *linecount, long *capacity, long **lineCountTracker);
int writeChangeFile(char *filepath, char ***filecontents, long linecount, long **lineCountTracker);
int writeToTextFile(char *filepath, char ***filecontents, long linecount);
int deleteFile(char *path);

#endif //COURSEWORK2_FILEIO_H
