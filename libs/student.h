#ifndef STUDENT_H
#define STUDENT_H

#include "gender.h"
#include "dorm.h"

struct student_t
{
    char id[12];
    char name[40];
    char year[5];
    enum gender_t gender;
    struct dorm_t *dorm;
};

struct student_t create_student(char *input);
void print_student(struct student_t mhs);
void student_add(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
#endif

