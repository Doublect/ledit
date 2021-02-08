#include <stdlib.h>
#include <string.h>
#include <libgen.h> //basename
#include <limits.h>

#include "FileIO.h"
#include "Library.h"

static char **history;
static char *changelogPath;
static long capacity = 0, count = 0;
static long currentCommand = 0;

void loadChangeFile();

void loadFilePath(char *filepath){
    char *basec = strdup(filepath);
    char *dirc = strdup(filepath);
    char *filename = basename(basec);
    char *directoryname = dirname(dirc);

    char *path = calloc(PATH_MAX, sizeof(char));
    char *hidden = "/.";

    strcat(path, directoryname);
    strcat(path, hidden);
    strcat(path, filename);

    changelogPath = path;

    free(basec);
    free(dirc);
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

char *getCurrentCommand(){
    long commandlen = (long)strlen(history[currentCommand]);

    char *output = malloc(sizeof(char) * commandlen);

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

void saveChangeFile(){
    writeToFile(changelogPath, &history, count);
}

void loadChangeFile(){
    readFromFile(changelogPath, &history, &count, &capacity);
}