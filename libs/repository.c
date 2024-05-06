#include "repository.h"

void student_add(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2) {
    (*size)++;
    *mhs = realloc(*mhs, *size * sizeof(struct student_t));
    if (*mhs == NULL) {
        printf("Failed to allocate memory.\n");
        return;
    }
    struct student_t *new_student = create_student(input);
    if (new_student == NULL) {
        printf("Failed to create student.\n");
        return;
    }
    (*mhs)[*size - 1] = *new_student;
}

void dorm_add(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2) {
    (*size2)++;
    *dorm = realloc(*dorm, *size2 * sizeof(struct dorm_t));
    if (*dorm == NULL) {
        printf("Failed to allocate memory.\n");
        return;
    }
    struct dorm_t *new_dorm = create_dorm(input);
    if (new_dorm == NULL) {
        printf("Failed to create dorm.\n");
        return;
    }
    (*dorm)[*size2 - 1] = *new_dorm;
}