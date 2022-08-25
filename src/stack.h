#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <string.h>
#include <stdio.h>

#define MAX_OP 100

typedef struct stack_rec {
    char items[MAX_OP];
    int priority[MAX_OP];
    int top;
} st;

void initStack_rec(st *s);
int isempty_rec(st *s);
void pop_rec(st *s);

#endif  // SRC_STACK_H_
