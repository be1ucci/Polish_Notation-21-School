#include "graph.h"

int main() {
  char str[MAX_STR];
  char out_str[MAX_STR];

  fgets(str, MAX_STR, stdin);
  int n = strlen(str);
  st opers;
  initStack_rec(&opers);
  int k = recording(str, n, &opers, out_str);
  out_str[k + 1] = '\0';
  render(out_str);
  return 0;
}
