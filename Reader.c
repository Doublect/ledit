#include<stdio.h>

//File type-check: https://stackoverflow.com/questions/11276521/determine-file-type-in-c
#include <sys/types.h>
#include <sys/stat.h>


static FILE *fstart;
static FILE *firstlinestart, *lastlineend; //stores the positions of lines on screen
static FILE *window

void openFile(char *path){
    FILE *temp = fopen(path, "r+");

    //Check if pointer is null
    if(!temp){
        fprintf(stderr, "File does not exist!");
        return;
    }

    fstart = temp;
}

void getLineContent(char *path, int *linecount, int *maxline){

}