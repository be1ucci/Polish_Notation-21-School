#include "stack_kalc.h"

double kalc(char strout[], double x, int *check) {
  double res;
  char *end;
  res = strtod(strout, &end);
  if (end != strout || *strout == 'x') {
    stack counts;
    initStack(&counts);
    if (*strout == 'x') {
      counts.top += 1;
      counts.val[counts.top] = x;
      ++strout;
    } else {
      counts.top++;
      counts.val[counts.top] = res;
      strout = end;
    }
    while ((*strout != '\0') && *check && counts.top > -1) {
      if (*strout == ' ') { ++strout; continue; }
      if (is_number(*strout)) {
        strout = number(strout, &counts);
        strout++;
      } else if (binary(*strout)) {
        binar_oper(*strout, &counts, check);
        strout++;
      } else if (*strout == 'x') {
        counts.top++;
        counts.val[counts.top] = x;
        ++strout;
      } else if (!binary(*strout)) {
        unar_oper(*strout, &counts);
        strout++;
      }
    }
    if (*check)
        res = *counts.val;
    else
        *check = 0;
  } return res;
}

void binar_oper(char a, stack *counts, int *check) {
  if ((counts->top) > 0) {
    double last = counts->val[counts->top];
    pop(counts);
    switch (a) {
    case '+':
      counts->val[counts->top] = counts->val[counts->top] + last;
      break;
    case '-':
      counts->val[counts->top] = counts->val[counts->top] - last;
      break;
    case '*':
      counts->val[counts->top] = counts->val[counts->top] * last;
      break;
    case '/':
      counts->val[counts->top] = counts->val[counts->top] / last;
      break;
    case '^':
      counts->val[counts->top] = pow(counts->val[counts->top], last);
      break;
    }
  } else {
    *check = 0;
  }
}

void unar_oper(char a, stack *counts) {
  if (a == 's')
    counts->val[counts->top] = sin(counts->val[counts->top]);
  else if (a == 'c')
    counts->val[counts->top] = cos(counts->val[counts->top]);
  else if (a == 't')
    counts->val[counts->top] = tan(counts->val[counts->top]);
  else if (a == 'g')
    counts->val[counts->top] = 1.0 / tan(counts->val[counts->top]);
  else if (a == 'l')
    counts->val[counts->top] = log(counts->val[counts->top]);
  else if (a == 'q')
    counts->val[counts->top] = sqrt(counts->val[counts->top]);
  else if (a == '~')
    counts->val[counts->top] = -counts->val[counts->top];
}

int binary(char a) {
  int res = 0;
  if (a == '*' || a == '+' || a == '-' || a == '^' || a == '/')
    res = 1;

  return res;
}

char *number(char *strout, stack *counts) {
  char *end;
  double res = strtod(strout, &end);
  counts->top++;
  counts->val[counts->top] = res;
  return end;
}

int is_number(char a) {
  int res = 0;
  if ((a >= '0' && a <= '9'))
    res = 1;
  return res;
}
