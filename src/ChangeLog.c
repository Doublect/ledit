#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "FileIO.h"
#include "Library.h"
#include "definitions.h"
static char **history;
static char *changelogPath = NULL;
static long capacity = 0, count = 0;
static long currentCommand = 0;

void loadChangeFile();

void loadFilePath(char *filepath){

    // If the path is empty
    changelogPath = getHiddenFilePath(filepath);
}

void initChange(char *filepath){
    loadFilePath(filepath);

    loadChangeFile();
    currentCommand = count;
}

void unloadChange(){
    free(changelogPath);

    for(int i = 0; i < capacity; i++){
        free(history[i]);
    }
}

void addCommand(char *change){
    if(capacity <= (count + 1)){
        changeStringArrayCapacity(&history, count, &capacity, 32);
    }

    history[count] = change;

    count++;
    currentCommand++;
}

void addCurrentCommand(char *change){
    if(currentCommand == count)
        addCommand(change);
}

char *getCurrentCommand(){
    long commandlen = (long)strlen(history[currentCommand]);

    char *output = malloc(sizeof(char) * (commandlen + 32));

    memcpy(output, history[currentCommand], commandlen);

    return output;
}

char *getPreviousCommand(){
    if(currentCommand > 0){
        currentCommand--;

        return getCurrentCommand();
    }
    return NULL;
}

char *getNextCommand(){
    if(currentCommand < count){
        currentCommand++;

        return getCurrentCommand();
    }
    return NULL;
}

int saveChangeFile(){
    if(changelogPath == NULL) return NOPATH;
    writeToFile(changelogPath, &history, count);

    return 0;
}

void loadChangeFile(){
    readFromFile(changelogPath, &history, &count, &capacity);
}