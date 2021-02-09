#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Library.h"
#include "definitions.h"

//Returns contents of a textfile
//filecontents is a array which stores the pointers to the line beginnings, we want to return this, so filecontentsptr is a pointer to an array of pointers
int readTextFile(char *filepath, char *(*(*filecontentsptr)), long *fileContentsCapacity, long *linecount, long **linelength, long **linecapacity){
    FILE *fptr;

    fptr = fopen(filepath, "r");

    if(fptr == NULL){ //No such file
        fprintf(stderr,"ERROR 401");
        return NOFILE;
    }

    char c;

    // linecnt stores the size of the array to be allocated for storing the string pointers
    *linecount = 0;
    *fileContentsCapacity = 32;

    //Set pointer to start
    fseek(fptr, 0, SEEK_SET);


    // Count number of lines
    while((c = (char)fgetc(fptr)) != EOF){
        if(c == '\n' || c == '\0'){
            if(*linecount >= *fileContentsCapacity)
                *fileContentsCapacity += 32;

            (*linecount)++;
        }
    }

    // Allocate array for storing the strings and their length
    *filecontentsptr = calloc(*fileContentsCapacity, sizeof(char *));
    *linelength = calloc(*fileContentsCapacity, sizeof(long));
    *linecapacity = calloc(*fileContentsCapacity, sizeof(long));

    (*filecontentsptr)[(*linecount)] = NULL;
    (*linelength)[(*linecount)] = -1;


    //Set pointer to start
    fclose(fptr);
    fptr = fopen(filepath, "r");

    // Stores which line the process is on
    long i = 0;
    // Stores the length of the given line
    long j = 1;

    // Count line length
    while((c = fgetc(fptr)) != EOF){
        if(c == '\n' || c == '\0'){
            (*linelength)[i] = j;
            j = 1;
            i++;
        } else {
            j++;
        }
    }

    fseek(fptr, 0, SEEK_SET);

    for(long k = 0; k < *linecount; k++){
        (*linecapacity)[k] = (((*linelength)[k] / 16) + 1) * 16;
        char* string = malloc(sizeof(char) * (*linecapacity)[k]);

        //fread(string, sizeof(char), (*linelength)[i], fptr);
        if(fgets(string, (*linecapacity)[k], fptr) == NULL){
            break;
        }

        //fscanf(fptr, )
        //getline(&string, &(*linelength)[i], fptr);
        // Remove \n from input
        //fgetc(fptr);

        // Replace all new line with 0
        string[strcspn(string, "\n")] = 0;

        //printf("%s\n\r", string);

        (*filecontentsptr)[k] = string;
    }

    fclose(fptr);

    return 0;
}


int readFromFile(char *filepath, char ***filecontents, long *linecount, long *capacity){
    FILE *fptr;

    fptr = fopen(filepath, "r");

    if(fptr == NULL){ //No such file
        fprintf(stderr,"ERROR 401");
        return NOFILE;
    }

    char c;

    // linecount stores the size of the array to be allocated for storing the string pointers
    *linecount = 0;


    // Count number of lines
    while((c = (char)fgetc(fptr)) != EOF && c != '\0' ){
        if(c == '\n'){
            (*linecount)++;
        }
    }

    rewind(fptr);

    *capacity = *linecount + 32;

    // Allocate array for storing the strings and their length
    *filecontents = calloc(*capacity, sizeof(char *));

    for(long i = 0; i < *linecount; i++){

        // Store current position of file pointer
        long position = ftell(fptr);

        long j = 1;
        while((c = (char)fgetc(fptr)) != '\n' && c != '\0') {
            j++;
        }

        fseek(fptr, position, SEEK_SET);

        char* string = malloc(sizeof(char) * (j + 1));

        if(fgets(string, j + 1, fptr) == NULL) break;
        //if(fscanf(fptr, "%s", string) == EOF) break;
        fprintf(stderr, "R: %s, len: %ld", string, j + 1);
        // Replace new line with 0
        string[strcspn(string, "\n")] = '\0';

        (*filecontents)[i] = string;
    }

    fclose(fptr);

    return 0;
}

int writeToFile(char *filepath, char ***filecontents, const long linecount){
    FILE *fptr;

    fptr = fopen(filepath, "w");

    
    if(fptr == NULL){ //Can't create file
        fprintf(stderr,"ERROR 402: While opening file: %s\n", filepath);
        return FILECREATEERR;
    }

    for(long linenum = 0; linenum < linecount; linenum++){

        char *string = (*filecontents)[linenum];

        if(string == NULL) {
            fprintf(fptr, "\n");
            continue;
        }

        // Replace null with newline
        //string[strlen(string)] = '\n';
        //long nullpos = strcspn(string, "\0");
        string[strcspn(string, "\0")] = '\n';

        // Output the line
        fprintf(fptr, "%s", string);
        //fprintf(stderr, "W: %s", string);
    }

    fclose(fptr);

    return 0;
}

int deleteFile(char *path){
    if (remove(path) == 0 && remove(getHiddenFilePath(path)) == 0) return 0;
    return FILEDELETEERR;
}