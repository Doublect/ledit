#include <stdlib.h>
//File type-check: https://stackoverflow.com/questions/11276521/determine-file-type-in-c
#include <string.h>

#include "FileIO.h"
#include "Library.h"
#include "definitions.h"

static char *filePath = NULL;
static long *lineLength, *lineCapacity; //stores the positions of lines on screenPos
static long lineCount, fileContentsCapacity;
static char **fileContents;

static char *empty = "\0"; // Empty string

void changeLineCount(long delta);

char *getLine(long pos, long offset){

    if(fileContentsCapacity > pos && offset < lineLength[pos] && lineCount > pos) {
        //printf("%d-%d\n\r", offset, lineLength[pos]);
        return &(fileContents[pos][offset]);
    }
    if(pos < lineCount)
        return empty;

    return NULL;
}

long getLineCount(){
    return lineCount;
}

void readFile(char *path){
    filePath = path;

    readTextFile(filePath, &fileContents, &fileContentsCapacity, &lineCount, &lineLength, &lineCapacity);
}
// Returns a line if it is possible, else returns null pointer

void unloadFileContents(){
    for(long i = 0; i < fileContentsCapacity; i++){
        // Free strings
        free(fileContents[i]);
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

void writeTextFile(char *path, int bunload){
    if(path == NULL){
        writeToTextFile(filePath, &fileContents, lineCount);
    } else {
        writeToTextFile(path, &fileContents, lineCount);
        filePath = path;
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
        changeStringArrayCapacity(&fileContents, lineCount, &fileContentsCapacity, delta);
    }

    if(lineCount < pos){
        changeLineCount(pos - lineCount);
    }

    if(len == -1)
        len = (long)strlen(string);

    fileContents[pos - 1] = string;

    lineLength[pos - 1] = (long)len;
    lineCapacity[pos - 1] =  (long)len;
}

void insertLine(char *string, long pos, long len){

    // If there isn't enough capacity to add a string, then expand it
    if(fileContentsCapacity < lineCount + 1){
        long delta = 32;
        changeStringArrayCapacity(&fileContents, lineCount, &fileContentsCapacity, delta);
    }

    if(lineCount < pos)
        return setLine(string, pos, len);

    changeLineCount(1);

    if(len == -1)
        len = (long)strlen(string);

    for(long i = lineCount - 1; i >= pos; i--){
        fileContents[i] = fileContents[i - 1];
        lineLength[i] = lineLength[i - 1];
        lineCapacity[i] = lineCapacity[i - 1];
    }

    fileContents[pos - 1] = string;
    lineCapacity[pos - 1] = len;
    lineLength[pos - 1] = len;
}

void swapLines(long posA, long posB){
    if(posA == posB) return;

    if(!(posA > 0 && posB > 0 && posA < lineCount && posB < lineCount)) return;

    long tempLineLength = lineLength[posA - 1];
    char *tempLine = fileContents[posA - 1];

    setLine(fileContents[posB - 1], posA, lineLength[posB - 1]);

    setLine(tempLine, posB, tempLineLength);
}

void deleteLines(long posStart, long posEnd){
    if(posStart >= lineCount) return;

    if(posEnd < posStart) posEnd = posStart;

    posStart--;
    posEnd--;

    long range = posEnd - posStart + 1;

    for(long i = posStart; i < lineCount; i++){

        if(i >= posStart && i <= posEnd)
            free(fileContents[i]);

        if(i + range > lineCount){
            fileContents[i] = NULL;
        } else {
            fileContents[i] = fileContents[i + range];
        }
    }

    lineCount -= range;
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

void removeFile(char *path){
    if(path != NULL && strcmp(path, "")) {
        deleteFile(path);
    } else {
        if (filePath == NULL)
            return;
        deleteFile(filePath);
    }
}