#include<stdio.h>
#include "Terminal.h"
#include "Library.h"
#include "unistd.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    setTerminal();

    while (1) {
        char c;
        mnextInput(&c, 40, 1);
        printLineNumbers();
    }

    resetTerminal();

    return 0;
}