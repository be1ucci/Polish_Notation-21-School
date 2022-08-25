#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include "record_rpn.h"
#include "stack_kalc.h"

#include <math.h>
#include <stdio.h>

#define LENGTH 80
#define WIDTH 25

void output(int graph[WIDTH][LENGTH]);
int render(char out_str[MAX_STR]);

#endif  // SRC_GRAPH_H_
