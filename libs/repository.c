#include "repository.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Define the complete function definition here. Be sure to enlist the prototype of each function
 * defined here in the corresponding header file.
 *
 */

short line_count(char* fileName)
{
    fileName[strcspn(fileName, "\n")] = 0;
    FILE *ptr = fopen(fileName,"r");
    short counter = 0;
    char chr = getc(ptr);

    while (chr != EOF)
    {
        if (chr == '\n') { counter++; }
        chr = getc(ptr);
    }

    fclose(ptr);
    return counter;
}