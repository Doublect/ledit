#ifndef COURSEWORK2_CHANGELOG_H
#define COURSEWORK2_CHANGELOG_H

void initChange(char *filepath);
void addCommand(char *command);
void unloadChange();
void getPreviousChange(char **output);
void getNextChange(char **output);
void saveChangeFile();
void loadChangeFile();

#endif //COURSEWORK2_CHANGELOG_H
