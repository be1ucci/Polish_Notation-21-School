#ifndef SRC_STACK_KALC_H_
#define SRC_STACK_KALC_H_

#define MAX_OP 100

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200


typedef struct stack {
  double val[MAX_OP];
  int top;
} stack;

void initStack(stack *s);
int isempty(stack *s);
void pop(stack *s);

double kalc(char strout[], double x, int *check);
void binar_oper(char a, stack *counts, int *check);
void unar_oper(char a, stack *counts);
int binary(char a);
char *number(char *strout, stack *counts);
int is_number(char a);

#endif  // SRC_STACK_KALC_H_
