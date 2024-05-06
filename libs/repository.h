#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "gender.h"
#include "dorm.h"
#include "student.h"

void student_add(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
void student_print_all(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
void dorm_add(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
void dorm_print_all(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
void print_unassigned_students(struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
#endif
