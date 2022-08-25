#ifndef SRC_RECORD_RPN_H_
#define SRC_RECORD_RPN_H_

#include "stack.h"

#define MAX_STR 1000

int recording(char str[MAX_STR], int n, st* opers, char out_str[MAX_STR]);

int processing(st* opers, char out_str[MAX_STR], int k);

int preproc(st* opers, int priority, char out_str[MAX_STR], int k);

int step_record(st* opers, int i, char str[MAX_STR]);

int first_check(const char str[MAX_STR], char out_str[MAX_STR], int* i, int* k);

void help_func(st *opers, const char str[MAX_STR], int priora, int *i);

int second_check(st* opers, char str[MAX_STR], char out_str[MAX_STR], int* i, int* k);

int third_check(st *opers, const char str[MAX_STR], char out_str[MAX_STR], int *i, int *k);

void help_func_2(st *opers, char out_str[MAX_STR], int *i, int *k, int priora, char spec_symbol);

#endif  // SRC_RECORD_RPN_H_
