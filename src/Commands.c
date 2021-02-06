#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Commands.h"
#include "Terminal.h"
#include "Renderer.h"
#include "TextHandler.h"
#include "Library.h"
#include "definitions.h"

static char* command;
static int capacity, length, cursor;

char *parseArgument(char **string, int spaceSeparated);
int doSet(char *pointer);
int doSwap(char *pointer);

void initializeCommands(){
    // Make sure command is a null pointer
    free(command);

    // Allocate new command buffer and set up variables and null-terminators
    command = calloc(256, sizeof(char));
    capacity = 256;
    length = 0;
    cursor = 0;

    command[0] = '\0';
    command[255] = '\0';

    // Make sure cursor is in bottom left corner, and that the bottom line is clear
    moveCursorTo(1, getTerminalRows());
    clearLine();
}

int commands(){
    char first = command[1];

    switch (first) {
        case 'w':
            return SAVE;

        case 'q':
            return QUIT;

        case 'a':
            return 0;

        case 'i':
            return 0;

        case 's':
            if(length > 1 && command[2] == 'w')
                return SWAP;
            return SET;

        default:
            return NOFUNC;
    }
}

int executeCommand(){
    if(command[0] == ':'){
        int value = commands();

        switch (value) {
            case QUIT:
                return QUIT;

            case SAVE:
                writeFile(NULL, False);
                return SAVE;

            case SET:
                return doSet(&command[3]);

            case SWAP:
                return doSwap(&command[4]);
        }

    }
}

// Insert a new character at the cursor position
void insertCharacter(char c){
    // Increase command buffer size
    if(length >= (capacity - 1)){
        // Create pointer to new command string
        char* newcommand = calloc(capacity * 2, sizeof(char));

        // Copy over the contents of the old string
        strcpy(newcommand, command);

        // Free up old string memory
        free(command);

        // Change pointer to new string and update capacity
        command = newcommand;
        capacity *= 2;

        // Add null-termination to new string
        command[capacity - 1] = '\0';
    }

    // If we are writing a new character to end of the buffer
    if(cursor >= length) {
        command[cursor] = c;
    } else {
        // Inserting character into the buffer
        int i = cursor;
        char new = c;

        while(command[i] != '\0' && i < capacity) {
            char temp = command[i];
            command[i] = new;
            new = temp;

            i++;
        }
        command[i] = new;
    }

    length += 1;

    command[length + 1] = '\0';

    printStatusLine(command);

    // Move cursor to reflect the change
    arrowKeyHandler('C');
}

void deleteCharacter(){
    // If at the start of the buffer, then return
    if(cursor == 0) return;

    // If we are at the end of the buffer
    if(cursor >= length) {
        command[cursor - 1] = '\0';
    } else {
        int i = cursor - 1;

        while(command[i] != '\0' && i < (capacity - 2)){
            command[i] = command[i + 1];

            i++;
        }
    }

    length -= 1;

    command[length + 1] = '\0';

    printStatusLine(command);

    // Move cursor to reflect change
    arrowKeyHandler('D');
}

// Tries to move the cursor right, returns 0 if successful, else 1
int moveCursorRight(){
   if(cursor < length){
       cursor++;
       return 0;
   }
    return 1;
}

// Tries to move the cursor left, returns 0 if successful, else 1
int moveCursorLeft(){
    if(cursor > 0){
        cursor--;
        return 0;
    }
    return 1;
}

/// Tries to find the next parameter of a command
/// \param string The string from which the parsing shall occur. The position
/// \param spaceSeparated Whether the argument is delimited by spaces.
/// \return A null-terminated string or NULL.
char *parseArgument(char **string, int spaceSeparated){
    if(string == NULL){
        return NULL;
    }

    long arglen = 0;
    if(spaceSeparated){
        arglen += strcspn(*string, " \n\r\0");
    } else {
        arglen += strlen(*string) + 1;
    }

    char *arg = malloc(sizeof(char) * arglen);

    memccpy(arg, *string, sizeof(char), arglen);

    arg[arglen] = '\0';

    //printf("'%s'\n", arg);

    // Move the command pointer, so it will be possible to parse next argument afterwards
    (*string) += arglen;

    return arg;
}

int doSet(char *pointer){

    // Get the pos of the line which needs changing
    char *pos = parseArgument(&pointer, True);
    //printf("%d\n", isNumberStr(pos));
    if(!isNumberStr(pos)) return NOTNUMWARN;
    int lineNum = strtoint(pos);

    // Get the actual content of the line
    char *line = parseArgument(&pointer, False);

    // Change the stored text values
    setLine(line, lineNum, -1);

    // Update rendered text
    printTextLines();

    return 0;
}

int doSwap(char *pointer){
    // Get the pos of the line which needs changing
    char *posA = parseArgument(&pointer, True);
    char *posB = parseArgument(&pointer, True);

    //printf("'%s' '%s'\n", posA, posB);

    if(!(isNumberStr(posA) && isNumberStr(posB))) return NOTNUMWARN;


    swapLines(strtolong(posA), strtolong(posB));

    return 0;
}