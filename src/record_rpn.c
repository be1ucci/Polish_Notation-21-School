/*
 Приоритеты
 Высочайший: все операторы буквенные
 Высокий: возведение в степень ^
 Средний: деление и умножение * /
 Низкий: сложение и вычитание + -
 Самый низкий: скобки ( )

 /// ///
 s - sin
 c - cos
 q - sqrt
 t - tan
 g - cot
 l - ln
 ~ - унарный минус (важность 11!)
 /// ///

 Порядок:
 0) Проверка, что уже сразу не дан пример в виде польской анотации
 1) Сделать стек для хранения операторов
 2) Читаем символ
 3) Если число -- выводим
    [DONE] Проверка на дробное число
 4) Если функция -- помещаем в стек (при этом проверив правильность вызова)
 5) Если открывающая скобка -- помещаем в стек
 6) Если закрывающая скобка --  выводим элементы из стека (открывающая скобка удаляется из стека)= без вывода)
    [DONE] Проверка на закрытие всех скобок
    [DONE] Если встретили кого-то ниже по приоритету -- выплёвываемся!
    [DONE] Если встретили одинаковый приоритет -- выплёвываемся!
 7) Когда прочли все символы -- выводим все элементы из стека
 */

#include "record_rpn.h"

int recording(char str[MAX_STR], int n, st *opers, char out_str[MAX_STR]) {
  int i = 0;
  int k = 0;
  while (i < n) {
    // Проверка на специальные символы и пробелы + унарный минус
    if (first_check(str, out_str, &i, &k))
      continue;
    // Проверка на операторы и скобки
    if (second_check(opers, str, out_str, &i, &k))
      continue;
    // Проверка на буквенные операторы
    if (third_check(opers, str, out_str, &i, &k))
      continue;

    // Если ничего не подошло
    i++;
  }
  return k;
}

// Вывод из стека ТОЛЬКО для скобки!
int processing(st *opers, char out_str[MAX_STR], int k) {
  if (opers->items[opers->top] == ')') {
    pop_rec(opers);
    while (opers->priority[opers->top] != 0) {
      out_str[k] = opers->items[opers->top];
      k++;
      pop_rec(opers);
    }
    pop_rec(opers);
  }
  return k;
}

/*
 Проверка на вывод из стека и, соответственно, его вывод
 На ввод функции идут:
    1) сам стек
    2) строка вывода с его счетчиком (k), идущим на return
    3) новый входной оператор -- а именно его приоритет
*/
int preproc(st *opers, int priority, char out_str[MAX_STR], int k) {
  while ((!isempty_rec(opers)) &&
         (priority <= opers->priority[opers->top])) {
    out_str[k] = opers->items[opers->top];
    k++;
    pop_rec(opers);
  }
  return k;
}

int first_check(const char str[MAX_STR], char out_str[MAX_STR], int *i,
                int *k) {
  int check = 0;
  if (str[*i] == '.' && str[*i + 1] >= '0' && str[*i + 1] <= '9') {
    out_str[*k] = '.';
    *k = *k + 1;
    *i = *i + 1;
    check = 1;
  } else if (str[*i] == ' ') {
    out_str[*k] = ' ';
    *k = *k + 1;
    *i = *i + 1;
    check = 1;
  } else if ((str[*i] >= '0' && str[*i] <= '9') &&
             (str[*i + 1] < '0' || str[*i + 1] > '9') && str[*i + 1] != '.') {
    out_str[*k] = str[*i];
    *k = *k + 1;
    out_str[*k] = ' ';
    *k = *k + 1;
    *i = *i + 1;
    check = 1;
  } else if (str[*i] == 'x' || (str[*i] >= '0' && str[*i] <= '9')) {
    out_str[*k] = str[*i];
    *k = *k + 1;
    *i = *i + 1;
    check = 1;
  }
  return check;
}

int second_check(st *opers, char str[MAX_STR], char out_str[MAX_STR],
                 int *i, int *k) {
  int check = 0;
  switch (str[*i]) {
  case '(': { help_func(opers, str, 0, i); check = 1; break; }
  case ')': { help_func(opers, str, 0, i); *k = processing(opers, out_str, *k); check = 1; break; }
  case '+':
  case '-': {
      if ((str[*i] == '-' && *i == 0) || (str[*i - 1] == '(' && str[*i] == '-')) {
          *k = preproc(opers, 11, out_str, *k);
          help_func(opers, str, 11, i);
          check = 1; break;
      } else {
          *k = preproc(opers, 1, out_str, *k);
          help_func(opers, str, 1, i);
          check = 1;
          break;
      }
  }
  case '^': { *k = preproc(opers, 3, out_str, *k); help_func(opers, str, 3, i); check = 1; break; }
  case '/':
  case '*': { *k = preproc(opers, 2, out_str, *k); help_func(opers, str, 2, i); check = 1; break; }
  case '=': { *k = preproc(opers, -1, out_str, *k); help_func(opers, str, -1, i); check = 1; break; }
  case '\n': { *k = preproc(opers, -1, out_str, *k); help_func(opers, str, -1, i); check = 1; break; }
  }
  return check;
}

void help_func(st *opers, const char str[MAX_STR], int priora, int *i) {
  opers->top++;
    if (priora == 11) {
        opers->items[opers->top] = '~';
    } else {
      opers->items[opers->top] = str[*i];
    }
  opers->priority[opers->top] = priora;
  *i = *i + 1;
}

int third_check(st *opers, const char str[MAX_STR], char out_str[MAX_STR],
                int *i, int *k) {
  int check = 0;
  if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n' &&
      str[*i + 3] == '(') {
    help_func_2(opers, out_str, i, k, 4, 's');
    check = 1;
  }  // sin -- s
  if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's' &&
      str[*i + 3] == '(') {
    help_func_2(opers, out_str, i, k, 4, 'c');
    check = 1;
  }  // cos -- c
  if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n' &&
      str[*i + 3] == '(') {
    help_func_2(opers, out_str, i, k, 4, 't');
    check = 1;
  }  // tan -- t
  if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 't' &&
      str[*i + 3] == '(') {
    help_func_2(opers, out_str, i, k, 4, 'g');
    check = 1;
  }  // cot -- g
  if (str[*i] == 'l' && str[*i + 1] == 'n' && str[*i + 2] == '(') {
    help_func_2(opers, out_str, i, k, 4, 'l');
    check = 1;
  }  // ln -- l
  if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
      str[*i + 3] == 't' && str[*i + 4] == '(') {
    help_func_2(opers, out_str, i, k, 4, 'q');
    check = 1;
  }  // sqrt -- q
  return check;
}

void help_func_2(st *opers, char out_str[MAX_STR], int *i, int *k,
                 int priora, char spec_symbol) {
  *k = preproc(opers, priora, out_str, *k);
  opers->top++;
  opers->items[opers->top] = spec_symbol;
  opers->priority[opers->top] = priora;
  *i = *i + 1;
}
