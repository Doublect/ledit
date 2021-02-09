#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "FileIO.h"
#include "Library.h"
#include "definitions.h"

static char **history;
static long *linecountTracker, *length;
static char *changelogPath = NULL;
static long capacity = 0, count = 0;
static long currentCommand = 0;

int loadChangeFile();

void loadFilePath(char *filepath){
    // If the path is empty
    changelogPath = getHiddenFilePath(filepath);
}

void initChange(char *filepath){
    loadFilePath(filepath);

    loadChangeFile();
    currentCommand = count;

    length = calloc(count, sizeof(long));
}

void unloadChange(){
    free(changelogPath);

    for(int i = 0; i < capacity; i++){
        free(history[i]);
    }

    free(linecountTracker);
    free(length);
}

void addCommand(char *change, long linecount){
    if(capacity <= (count + 1)){
        changeStringArrayCapacity(&history, count, &capacity, 32);

        long *temp = malloc(capacity * sizeof(long));
        long *templen = calloc(capacity, sizeof(long));

        for(int i = 0; i < count; i++){
            temp[i] = linecountTracker[i];
            templen[i] = length[i];
        }

        free(linecountTracker);
        free(length);

        linecountTracker = temp;
        length = templen;
    }



    history[count] = change;
    linecountTracker[count] = linecount;

    count++;
    currentCommand++;
}

char *getCommand(long pos, long offset, long *lineCount){
    if(pos >= count) return NULL;

    if(length[pos] == 0){
        length[pos] = (long)strlen(history[pos]);
    }

    if(offset >= length[pos]) return NULL;

    *lineCount = linecountTracker[pos];

    return &(history[pos][offset]);
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

    writeChangeFile(changelogPath, &history, count, &linecountTracker);
    return 0;
}

int loadChangeFile(){
    if(changelogPath == NULL) return NOPATH;

    readChangeFile(changelogPath, &history, &count, &capacity, &linecountTracker);
    return 0;
}