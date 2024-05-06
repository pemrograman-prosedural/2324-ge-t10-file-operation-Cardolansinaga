#include "dorm.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct dorm_t create_dorm(char *input)
{
    struct dorm_t dorm;
    strcpy(dorm.name, strtok(NULL, "#"));
    dorm.capacity = atoi(strtok(NULL, "#"));
    char *stop = strtok(NULL, "#");
    if (strcmp(stop, "male")== 0)
    {
        dorm.gender = GENDER_MALE;
    } else if (strcmp(stop, "female") == 0)
    {
        dorm.gender = GENDER_FEMALE;
    }
    return dorm;
}

void print_dorm(struct dorm_t dorm)
{
    printf("%s|%hu|", dorm.name, dorm.capacity);
    if (dorm.gender == GENDER_MALE)
    {
        printf("male\n");
    } else if (dorm.gender == GENDER_FEMALE)
    {
        printf("female\n");
    }
}

struct dorm_t *new_dorm = create_dorm(*int);

