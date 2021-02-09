#include <stdlib.h>
#include <string.h>

#include "Terminal.h"
#include "TextHandler.h"
#include "ChangeLog.h"
#include "Library.h"
#include "definitions.h"

static char* command;
static int capacity, length, cursor;

char *parseArgument(char **string, int spaceSeparated);
int doSet(char *pointer);
int doSwap(char *pointer);
int doInsert(char *pointer);
int doSave(char *pointer);
int doDelete(char *pointer);
int doRemove(char *pointer);

void initCommands(){
    // Make sure command is a null pointer
    //free(command);

    // Allocate new command buffer and set up variables and null-terminators
    command = calloc(256, sizeof(char));
    capacity = 256;
    length = 0;
    cursor = 0;

    command[0] = '\0';
    command[255] = '\0';

    // Make sure cursor is in bottom left corner, then clear the it
    moveCursorTo(1, getScreenSize()->y);
    terminalCommand("2K");
}

void quitCommands(){
    free(command);

    unloadText();
    unloadChange();
}

int commands(){
    char first = command[1];

    switch (first) {
        case 'w':
            return SAVE;

        case 'q':
            return QUIT;

        case 'd':
            return DELETE;

        case 'r':
            return REMOVE;

        case 'a':
            return -1;

        case 'i':
            return INSERT;

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
                doSave(&command[3]);
                return SAVE;

            case DELETE:
                addCommand(command);
                if(strlen(&command[0]) >= 4)
                    return doDelete(&command[3]);

            case REMOVE:
                if(strlen(&command[0]) >= 4)
                    return doRemove(&command[3]);
                else return doRemove(NULL);

            case SET:
                addCommand(command);
                if(strlen(&command[0]) >= 4)
                    return doSet(&command[3]);
                return -1;

            case SWAP:
                addCommand(command);
                return doSwap(&command[4]);

            case INSERT:
                if(strlen(&command[0]) >= 4)
                    doInsert(&command[3]);

            default:
                return -1;
        }
    }


    return 0;
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

    printCommand(command);

    // Move cursor to reflect the change
    arrowKeyHandler('C');
}

/*
void getHistory(int bnext){
    char *temp = (bnext) ? getNextChange() : getPreviousChange();

    if(temp == NULL) return;

    // Save currently written command (if it has content and is the newest)
    if(length > 1)
        addCurrentCommand(command);
    else deleteNotCurrentCommand(command);

    command = temp;


}
*/
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

    printCommand(command);

    // Move cursor to reflect change
    arrowKeyHandler('D');
}

// Tries to move the cursor right, returns 1 if successful, else 0
int moveCursorRight(){
   if(cursor < length){
       cursor++;
       return True;
   }
    return False;
}

// Tries to move the cursor left, returns 0 if successful, else 1
int moveCursorLeft(){
    if(cursor > 0){
        cursor--;
        return True;
    }
    return False;
}

/// Tries to find the next parameter of a command
/// \param string The string from which the parsing shall occur. The position
/// \param spaceSeparated Whether the argument is delimited by spaces.
/// \return A null-terminated string or NULL.
char *parseArgument(char **string, int spaceSeparated){
    if(*string == NULL){
        return NULL;
    }

    long arglen = 0;
    if(spaceSeparated){
        arglen += (long)strcspn(*string, " \n\r\0");
    } else {
        arglen += (long)strlen(*string) + 1;
    }

    char *arg = malloc(sizeof(char) * arglen + 1);

    memccpy(arg, *string, sizeof(char), arglen);

    arg[arglen] = '\0';

    //printf("'%s'\n", arg);

    // Move the command pointer, so it will be possible to parse next argument afterwards
    (*string) += arglen;

    if(spaceSeparated) (*string)++;

    return arg;
}

int doSet(char *pointer){

    // Get the pos of the line which needs changing
    char *pos;
    if((pos = parseArgument(&pointer, True)) == NULL) return NOARG;

    if(!isNumberStr(pos)) return NOTNUMWARN;
    int lineNum = strtoint(pos);

    // Get the actual content of the line
    char *line = parseArgument(&pointer, False);

    // Change the stored text values
    setLine(line, lineNum, -1);

    // Update rendered text
    printText();

    // Do not free line, because that is used for the line in the text
    free(pos);

    return 0;
}

int doSwap(char *pointer){
    // Get the pos of the line which needs changing
    char *posA, *posB;
    if((posA = parseArgument(&pointer, True)) == NULL) return NOARG;
    if((posB = parseArgument(&pointer, True)) == NULL) return NOARG;

    if(!isNumberStr(posA) || !isNumberStr(posB)) return NOTNUMWARN;

    swapLines(strtolong(posA), strtolong(posB));

    // Update rendered text
    printText();

    free(posA);
    free(posB);

    return 0;
}

int doInsert(char *pointer) {
    // Get the pos of the line which needs changing
    char *pos;
    if((pos = parseArgument(&pointer, True)) == NULL) return NOARG;
    if(!isNumberStr(pos)) return NOTNUMWARN;
    int lineNum = strtoint(pos);

    // Get the actual content of the line
    char *line = parseArgument(&pointer, False);

    // Do the insertion
    insertLine(line, lineNum, -1);

    // Update rendered text
    printText();

    // Do not free line, because that is used for the line in the text
    free(pos);

    return 0;
}

int doSave(char *pointer){
    char *path;

    // We don't care whether we get a NULL or a value
    path = parseArgument(&pointer, False);

    if(path != NULL){
        loadFilePath(path);
    }

    int signal;

    if((signal = saveChangeFile())) return signal;
    writeTextFile(path, False);

    return 0;
}

int doDelete(char *pointer){
    char *posStart, *posEnd;

    if((posStart = parseArgument(&pointer, True)) == NULL) return NOARG;
    if((posEnd = parseArgument(&pointer, True)) == NULL) posEnd = posStart;

    if(!isNumberStr(posStart) || !isNumberStr(posEnd)) return NOTNUMWARN;

    deleteLines(strtolong(posStart), strtolong(posEnd));

    // Update rendered text
    printText();

    free(posStart);
    free(posEnd);

    return 0;
}

int doRemove(char *pointer){
    char *path = parseArgument(&pointer, True);

    removeFile(path);

    return 0;
}