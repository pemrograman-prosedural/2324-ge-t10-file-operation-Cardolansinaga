// 112S23006 - Cardolan Sinaga
// 12S23039 - Prisca Manurung

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/repository.h"

typedef void (*CommandFunc)(char *, struct student_t **, int *, struct dorm_t **, int *);

typedef struct {
    char *name;
    CommandFunc func;
} Command;

void dorm_add(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
void dorm_print_all(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
void student_add(char *student_name, int student_id, struct student_t **mhs, int *size) {
    (*mhs)[*size].name = malloc(strlen(student_name) + 1);
    strcpy((*mhs)[*size].name, student_name);
    (*mhs)[*size].id = student_id;
}
void student_print_all(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
void print_unassigned_students(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2);
void handle_unknown_command(char *input);

int main(int _argc, char **_argv) {
    char input[100];
    int size = 0;
    char *token;
    struct student_t *mhs = NULL;
    int size2 = 0;
    struct dorm_t *dorm = NULL;

    Command commands[] = {
        {"dorm-add", dorm_add},
        {"dorm-print-all", dorm_print_all},
        {"student-add", student_add},
        {"student-print-all", student_print_all},
        {NULL, NULL}  // End marker
    };

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    while(fgets(input, sizeof input, file) != NULL) {
        if(input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\r') {
            input[strlen(input) - 1] = '\0';
        }

        token = strtok(input, "#");
        if(strcmp(token, "---") == 0) {
            break;
        }

        int found = 0;
        for(Command *cmd = commands; cmd->name != NULL; cmd++) {
            if(strcmp(token, cmd->name) == 0) {
                cmd->func(input, &mhs, &size, &dorm, &size2);
                found = 1;
                break;
            }
        }
        if (!found) {
            handle_unknown_command(token);
        }
    }

    fclose(file);

    // Free allocated memory
    for (int i = 0; i < size; i++) {
        if (mhs[i].name != NULL) {
            free(mhs[i].name);
        }
        if (mhs[i].id != NULL) {
            free(mhs[i].id);
        }
        if (mhs[i].dorm != NULL) {
            if (mhs[i].dorm->name != NULL) {
                free(mhs[i].dorm->name);
            }
            free(mhs[i].dorm);
        }
    }
    free(mhs);
    free(dorm);
    return 0;
}

// Define the functions here
void dorm_add(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2) {
    char *token = strtok(NULL, "#");
    if (token == NULL) {
        printf("Error: No dorm name provided.\n");
        return;
    }

    char *dorm_name = strdup(token);

    // Resize the dorm array if necessary
    if (*size2 % 10 == 0) {
        *dorm = realloc(*dorm, (*size2 + 10) * sizeof(struct dorm_t));
        if (*dorm == NULL) {
            printf("Error: Failed to allocate memory.\n");
            free(dorm_name);
            return;
        }
    }

    // Initialize the new dorm
    (*dorm)[*size2].name = dorm_name;
    (*dorm)[*size2].students = NULL;
    (*dorm)[*size2].student_count = 0;

    (*size2)++;
}

void dorm_print_all(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2) {
    if (*size2 == 0) {
        printf("No dorms to display.\n");
        return;
    }

    for (int i = 0; i < *size2; i++) {
        printf("Dorm name: %s\n", (*dorm)[i].name);
        printf("Number of students: %d\n", (*dorm)[i].student_count);
        printf("--------------------\n");
    }
}

void student_add(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2) {
    char *token = strtok(NULL, "#");
    if (token == NULL) {
        printf("Error: No student name provided.\n");
        return;
    }

    char *student_name = strdup(token);

    token = strtok(NULL, "#");
    if (token == NULL) {
        printf("Error: No student ID provided.\n");
        free(student_name);
        return;
    }

    char *student_id = strdup(token);

    // Resize the mhs array if necessary
    if (*size % 10 == 0) {
        *mhs = realloc(*mhs, (*size + 10) * sizeof(struct student_t));
        if (*mhs == NULL) {
            printf("Error: Failed to allocate memory.\n");
            free(student_name);
            free(student_id);
            return;
        }
    }

    // Initialize the new student
    (*mhs)[*size].name = student_name;
    (*mhs)[*size].id = student_id;
    (*mhs)[*size].dorm = NULL;

    (*size)++;
}

void student_print_all(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2) {
    if (*size == 0) {
        printf("No students to display.\n");
        return;
    }

    for (int i = 0; i < *size; i++) {
        printf("Student name: %s\n", (*mhs)[i].name);
        printf("Student ID: %s\n", (*mhs)[i].id);
        if ((*mhs)[i].dorm != NULL) {
            printf("Dorm: %s\n", (*mhs)[i].dorm->name);
        } else {
            printf("Dorm: Not assigned\n");
        }
        printf("--------------------\n");
    }
}
struct dorm_t {
    char *name;
    struct student_t *students;
    int student_count;
};
void print_unassigned_students(char *input, struct student_t **mhs, int *size, struct dorm_t **dorm, int *size2) {
    int found = 0;
    for (int i = 0; i < *size; i++) {
        if ((*mhs)[i].dorm == NULL) {
            printf("Student name: %s\n", (*mhs)[i].name);
            printf("Student ID: %s\n", (*mhs)[i].id);
            printf("Dorm: Not assigned\n");
            printf("--------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No unassigned students.\n");
    }
}
void handle_unknown_command(char *input) {
    printf("Error: Unknown command '%s'. Please check your command and try again.\n", input);
}