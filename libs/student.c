#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct student_t create_student(char *input)
{
  struct student_t mhs;
  strcpy(mhs.id, strtok(NULL, "#"));
  strcpy(mhs.name, strtok(NULL, "#"));
  strcpy(mhs.year, strtok(NULL, "#"));
  char *gender = strtok(NULL, "#");
  if (strcmp(gender, "male") == 0)
  {
    mhs.gender = GENDER_MALE;
  }
  else if (strcmp(gender, "female") == 0)
  {
    mhs.gender = GENDER_FEMALE;
  }
  return mhs;
}

void print_student(struct student_t mhs)
{
  printf("%s|%s|%s|", mhs.id, mhs.name, mhs.year);
  if (mhs.gender == GENDER_MALE)
  {
    printf("male\n");
  }
  else if (mhs.gender == GENDER_FEMALE)
  {
    printf("female\n");
  }
}