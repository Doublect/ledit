//
// Created by doublect on 2021. 02. 03..
//

#define QUIT 9000
#define SAVE 9010

#ifndef COURSEWORK2_COMMANDS_H
#define COURSEWORK2_COMMANDS_H



void initializeCommands();
int executeCommand();
void insertCharacter(char c);
void deleteCharacter();
int moveCursorRight();
int moveCursorLeft();

#endif //COURSEWORK2_COMMANDS_H
