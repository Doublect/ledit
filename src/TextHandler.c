#include<stdio.h>
#include <stdlib.h>
//File type-check: https://stackoverflow.com/questions/11276521/determine-file-type-in-c
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h> // max

#include "FileIO.h"
#include "definitions.h"

static char *filePath;
static int *lineLength, *lineCapacity; //stores the positions of lines on screen
static int lineCount, fileContentsCapacity;
static char **fileContents;

static char empty = '\0'; // Empty string

void changeCapacity(int delta);
void changeLineCount(int delta);

char *getLine(int pos, int offset){

    if(fileContentsCapacity > pos && offset < lineLength[pos] && lineCount > pos) {
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

void unloadFileContents(){
    for(int linenum = 0; linenum < lineCount; linenum++){
        // Free strings
        free(fileContents[linenum]);
    }

    free(fileContents); // Free pointer to the array of strings
}

void unloadText(){

    unloadFileContents();

    fileContentsCapacity = 0;
    lineCount = 0;

    free(lineLength); // Free the pointer to linelength array

    free(lineCapacity);
}

void writeFile(char *path, int bunload){
    if(path == NULL){
        writeTextFile(filePath, &fileContents, &fileContentsCapacity, &lineCount, &lineLength, &lineCapacity);
    } else {
        writeTextFile(path, &fileContents, &fileContentsCapacity, &lineCount, &lineLength, &lineCapacity);
    }

    if(bunload){
        unloadText();

        // We have unloaded the text file
        filePath = NULL;
    }
}

void getLineContent(char *path, int *linecount, int *maxline){

}

void setLine(char *string, int pos){

    if(fileContentsCapacity < pos){
        int delta = (((pos - fileContentsCapacity) / 32) + 1) * 32;
        changeCapacity(delta);
    }

    if(lineCount < pos){
        changeLineCount(pos);
    }

    unsigned long len = strlen(string);

    fileContents[pos - 1] = string;

    lineLength[pos - 1] = (int)len;
    lineCapacity[pos - 1] =  (int)len;
}

void changeCapacity(int delta) {
    if(delta == 0) return;

    // Make sure we don't have negative number of lines
    if(delta + fileContentsCapacity < 0) {
        delta = -fileContentsCapacity;
    }

    char **newfileContents = calloc(fileContentsCapacity + delta, sizeof(char *));


    // Copy over the lines, make sure to only copy the number of elements we need
    int copyAmount = ((delta < 0) ? fileContentsCapacity + delta : fileContentsCapacity);
    memcpy(newfileContents, fileContents, copyAmount);

    // Free current fileContents
    unloadFileContents();

    // Update pointer
    fileContents = newfileContents;

    // Update fileContentsCapacity
    fileContentsCapacity += delta;
}


void changeLineCount(int delta) {
    if(lineCount + delta < 0) {
        delta = -lineCount;
    }

    int *newlineCapacity = calloc(lineCount + delta, sizeof(int));
    int *newlineLength = calloc(lineCount + delta, sizeof(int));

    int copyAmount = ((delta < 0) ? lineCount + delta : lineCount);

    memcpy(newlineCapacity, lineCapacity, copyAmount);
    memcpy(newlineLength, lineLength, copyAmount);

    free(lineCapacity);
    free(lineLength);

    lineCapacity = newlineCapacity;
    lineLength = newlineCapacity;

    lineCount += delta;
}