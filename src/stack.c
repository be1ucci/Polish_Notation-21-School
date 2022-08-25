#include "stack.h"

// Инициализация стека
void initStack_rec(st *s) {
    s -> top = -1;
}

// Проверка, пустой ли стек
int isempty_rec(st *s) {
    int check = 0;
    if (s -> top == -1)
        check = 1;
    return check;
}

// Удаление элемента из стека
void pop_rec(st *s) {
    if (!isempty_rec(s))
        s -> top--;
}
