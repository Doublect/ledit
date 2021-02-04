#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "definitions.h"

//Returns contents of a textfile
//filecontents is a array which stores the pointers to the line beginnings, we want to return this, so filecontentsptr is a pointer to an array of pointers
int readTextFile(char *filepath, char *(*(*filecontentsptr)), int *fileContentsCapacity, int *linecount, int **linelength, int **linecapacity){
    FILE *fptr;

    fptr = fopen(filepath, "r");

    if(fptr == NULL){ //No such file
        fprintf(stderr,"ERROR 401");
        return 401;
    }

    char c;

    // linecnt stores the size of the array to be allocated for storing the string pointers
    *linecount = 0;
    *fileContentsCapacity = 32;

    //Set pointer to start
    fclose(fptr);
    fptr = fopen(filepath, "r");

    // Count number of lines
    while((c = fgetc(fptr)) != EOF){
        if(c == '\n' || c == '\0'){
            if(*linecount >= *fileContentsCapacity)
                *fileContentsCapacity += 32;

            (*linecount)++;
        }
    }

    // Allocate array for storing the strings and their length
    *filecontentsptr = calloc(*fileContentsCapacity, sizeof(char *));
    *linelength = calloc(*fileContentsCapacity, sizeof(int));
    *linecapacity = calloc(*fileContentsCapacity, sizeof(int));

    (*filecontentsptr)[(*linecount)] = NULL;
    (*linelength)[(*linecount)] = -1;


    //Set pointer to start
    fclose(fptr);
    fptr = fopen(filepath, "r");

    // Stores which line the process ar
    int i = 0;
    // Stores the length of the given line
    int j = 1;

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

    fclose(fptr);
    fptr = fopen(filepath, "r");

    for(int k = 0; k < *linecount; k++){
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


int writeTextFile(char *filepath, char *(*(*filecontentsptr)), int *fileContentsCapacity, int *linecount, int **linelength, int **linecapacity, int unload){
    FILE *fptr;

    fptr = fopen(filepath, "w");

    
    if(fptr == NULL){ //Can't create file
        fprintf(stderr,"ERROR 402");
        return 402;
    }

    for(int linenum = 0; linenum < *linecount; linenum++){

        // Output the line
        fprintf(fptr, "%s\n", (*filecontentsptr)[linenum]);

        if(unload == True)
        {
            // Free string
            free((*filecontentsptr)[linenum]);
        }
    }

    if(unload == True) {
        free(*filecontentsptr); // Free array holding strings
        free(filecontentsptr); // Free pointer to the array of strings

        free(fileContentsCapacity);

        free(linecount);

        free(*linelength); // Free the array of linelength
        free(linelength); // Free the pointer to linelength array


        free(*linecapacity);
        free(linecapacity);
    }

    return 0;
}