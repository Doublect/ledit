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
static long *lineLength, *lineCapacity; //stores the positions of lines on screenPos
static long lineCount, fileContentsCapacity;
static char **fileContents;

static char empty = '\0'; // Empty string

void changeCapacity(long delta);
void changeLineCount(long delta);

char *getLine(long pos, long offset){

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
    for(long linenum = 0; linenum < lineCount; linenum++){
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

void setLine(char *string, long pos, long len){

    if(fileContentsCapacity < pos){
        long delta = (((pos - fileContentsCapacity) / 32) + 1) * 32;
        changeCapacity(delta);
    }

    if(lineCount < pos){
        changeLineCount(pos);
    }

    if(len == -1)
        len = strlen(string);

    fileContents[pos - 1] = string;

    lineLength[pos - 1] = (long)len;
    lineCapacity[pos - 1] =  (long)len;
}

void swapLines(long posA, long posB){
    if(posA == posB) return;

    if(!(posA > 0 && posB > 0 && posA < lineCount && posB < lineCount)) return;

    long tempLineCapacity = lineCapacity[posA - 1];
    long tempLineLength = lineLength[posA - 1];
    char *tempLine = fileContents[posA - 1];

    setLine(fileContents[posB - 1], posA, lineLength[posB - 1]);
    printf("Hello\n");

    setLine(tempLine, posB, tempLineLength);

}
void changeCapacity(long delta) {
    if(delta == 0) return;

    // Make sure we don't have negative number of lines
    if(delta + fileContentsCapacity < 0) {
        delta = -fileContentsCapacity;
    }

    char **newfileContents = calloc(fileContentsCapacity + delta, sizeof(char *));

    // Copy over the lines, make sure to only copy the number of elements we need
    long copyAmount = (((fileContentsCapacity + delta) < lineCount) ? fileContentsCapacity + delta : lineCount);
    //memcpy(*newfileContents, *fileContents, copyAmount);
    for(long i = 0; i < lineCount; i++){
        newfileContents[i] = fileContents[i];
    }

    // Free strings which are less than the copied
    for(long i = lineCount; lineCount < copyAmount; i++){
        free(fileContents[i]);
    }

    // Free current fileContents
    free(fileContents);

    // Update pointer
    fileContents = newfileContents;

    // Update fileContentsCapacity
    fileContentsCapacity += delta;
}


void changeLineCount(long delta) {
    if(lineCount + delta < 0) {
        delta = -lineCount;
    }

    long *newlineCapacity = calloc(lineCount + delta, sizeof(long));
    long *newlineLength = calloc(lineCount + delta, sizeof(long));

    long copyAmount = ((delta < 0) ? lineCount + delta : lineCount);

    //memcpy(newlineCapacity, lineCapacity, copyAmount);
    //memcpy(newlineLength, lineLength, copyAmount);
    for(long i = 0; i < copyAmount; i++){
      newlineCapacity[i] = lineCapacity[i];
      newlineLength[i] = lineLength[i];
    }

    free(lineCapacity);
    free(lineLength);

    lineCapacity = newlineCapacity;
    lineLength = newlineLength;

    lineCount += delta;
}