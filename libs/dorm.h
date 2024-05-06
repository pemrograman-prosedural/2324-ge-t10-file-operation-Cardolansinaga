#ifndef DORM_H
#define DORM_H

#include "gender.h"

typedef struct {
  char name[20];
  unsigned short capacity;
  enum gender_t gender;
  unsigned short residents_num;
} dorm_t;

dorm_t *create_dorm(char *input);
void print_dorm(dorm_t dorm);

#endif
