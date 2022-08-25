#include "stack_kalc.h"

// Инициализация стека
void initStack(stack *s) { s->top = -1; }

// Проверка, пустой ли стек
int isempty(stack *s) {
  int check = 0;
  if (s->top == -1)
    check = 1;
  return check;
}

// Удаление элемента из стека
void pop(stack *s) {
  if (!isempty(s))
    s->top--;
}
