#ifndef COURSEWORK2_CHANGELOG_H
#define COURSEWORK2_CHANGELOG_H

void loadFilePath(char *filepath);
void initChange(char *filepath);
void addCommand(char *change);
void addCurrentCommand(char *change);
void unloadChange();
char *getPreviousChange();
char *getNextChange();
int saveChangeFile();
void loadChangeFile();

#endif //COURSEWORK2_CHANGELOG_H
