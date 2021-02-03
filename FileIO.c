#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//Returns contents of a textfile
//filecontents is a array which stores the pointers to the line beginnings, we want to return this, so filecontentsptr is a pointer to an array of pointers
int readTextFile(char *filepath, char *(*filecontentsptr)[], int *linecount, int **linelength){
    FILE *fptr, *fstart;

    fstart = fopen(filepath, "r");

    if(fstart == NULL){ //No such file
        return 401;
    }

    int i = 1, maxline = 1, *linecount = 1;
    char c;

    //Set pointer to start
    fptr = fstart;

    while((c = fgetc(fptr)) != NULL){
        if(c == '\n' || c == '\0'){
            if(i > maxline)
                maxline = i;

            i = 1;
            *linecount++;
        }
        i++;
    }

    //Set pointer to start
    fptr = fstart;
    char line[maxline];

    //Allocate the array of pointers and line length array
    filecontentsptr = malloc(sizeof(char *) * (*linecount + 4));
    *linelength = malloc(sizeof(int *) * (*linecount + 4));



    while (fgets(line, maxline, fptr)){
        
        char *lineptr = &line;
        i = 1;
        int linenum = 0;

        while(*lineptr != '\n' && *lineptr != '\0'){
            i++;
            lineptr++;
        }

        //Change the line terminator to null;
        *lineptr = '\0';

        //Allocate string
        char *str = malloc(sizeof(char) * (i + 4));

        strcpy(str, line);

        //Save line data
        (*filecontentsptr)[linenum] = str;
        *(linelength + linenum) = i;
    }

    fclose(fstart);

    return 0;
}


int writeTextFile(char *filepath, char *filecontentsptr[], int linecount, int **linelength){
    FILE *fptr, *fstart;

    fstart = fopen(filepath, "w");

    
    if(fstart == NULL){ //Can't create file
        return 402;
    }

    fptr = fstart;

    for(int linenum = 0; linenum < linecount; linenum++){

        //print line
        fprintf(fptr, "%s\n", filecontentsptr[linenum]);

        //free string in filecontent
        free(filecontentsptr[linenum]);
    }

    free(*linelength); //free the array of linelength
    free(filecontentsptr); //free array holding strings
}