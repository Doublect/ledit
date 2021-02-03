#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Commands.h"
#include "Terminal.h"
#include "Renderer.h"


#define QUIT 9000
#define SAVE 9010

static char* command;
static int capacity, length, cursor;

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

int commands(char c){

    switch (c) {
        case 'w':
            return SAVE;

        case 'q':
            return QUIT;

        case 'a':
            return 0;

        case 'i':
            return 0;
    }
}

int executeCommand(){
    if(command[0] == ':'){
        int value = commands(command[1]);

        if(value == QUIT) return QUIT;
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
   if(cursor <= length){
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