#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    int j = 0;

    // Count line length
    while((c = fgetc(fptr)) != EOF){
        if(c == '\n' || c == '\0'){
            (*linelength)[i] = j;
            j = 0;
            i++;
        } else {
            j++;
        }
    }

    fclose(fptr);
    fptr = fopen(filepath, "r");

    // Stores the length of the given line
    j = 0;

    for(int i = 0; i < *linecount; i++){
        (*linecapacity)[i] = (((*linelength)[i] / 16) + 1) * 16;
        char* string = malloc(sizeof(char) * (*linecapacity)[i]);

        //fread(string, sizeof(char), (*linelength)[i], fptr);
        fgets(string, (*linelength)[i] + 1, fptr);

        //getline(&string, &(*linelength)[i], fptr);
        // Remove \n from input
        //fgetc(fptr);

        string[(*linelength)[i]] = '\0';

        //printf("%s\n\r", string);

        (*filecontentsptr)[i] = string;
    }

    fclose(fptr);

    return 0;
}


int writeTextFile(char *filepath, char *filecontentsptr[], int linecount, int **linelength){
    FILE *fptr;

    fptr = fopen(filepath, "w");

    
    if(fptr == NULL){ //Can't create file
        return 402;
    }

    for(int linenum = 0; linenum < linecount; linenum++){

        //print line
        fprintf(fptr, "%s\n", filecontentsptr[linenum]);

        //free string in filecontent
        free(filecontentsptr[linenum]);
    }

    free(*linelength); //free the array of linelength
    free(filecontentsptr); //free array holding strings
}