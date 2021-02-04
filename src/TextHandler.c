#include<stdio.h>
#include <stdlib.h>
//File type-check: https://stackoverflow.com/questions/11276521/determine-file-type-in-c
#include <sys/types.h>
#include <sys/stat.h>

#include "FileIO.h"
#include "definitions.h"

static char *filePath;
static int *lineLength, *lineCapacity; //stores the positions of lines on screen
static int lineCount, fileContentsCapacity;
static char **fileContents;

static char empty = '\0'; // Empty string

char *getLine(int pos, int offset){

    if(fileContentsCapacity > pos && offset < lineLength[pos]) {
        //printf("%d-%d\n\r", offset, lineLength[pos]);
        return (fileContents[pos] + offset);
    }

    return &empty;
}

void readFile(char *path){
    filePath = path;

    readTextFile(filePath, &fileContents, &fileContentsCapacity, &lineCount, &lineLength, &lineCapacity);
}
// Returns a line if it is possible, else returns null pointer

void writeFile(char *path, int bunload){
    if(path == NULL){
        writeTextFile(filePath, &fileContents, &fileContentsCapacity, &lineCount, &lineLength, &lineCapacity, bunload);
    } else {
        writeTextFile(path, &fileContents, &fileContentsCapacity, &lineCount, &lineLength, &lineCapacity, bunload);
    }

    if(bunload){
        // We have unloaded the text file
        filePath = NULL;
    }
}
void getLineContent(char *path, int *linecount, int *maxline){

}