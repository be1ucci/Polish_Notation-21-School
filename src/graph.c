#include "graph.h"

int render(char out_str[MAX_STR]) {
  double y_s, x_s;
  int check = 1;
  y_s = 2.0 / (WIDTH - 1);
  x_s = 4.0 * M_PI / (LENGTH - 1);
  int graph[WIDTH][LENGTH];
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < LENGTH; j++) {
      graph[i][j] = 0;
    }
  }
  for (int x = 0; x < LENGTH; x++) {
    double y_res = kalc(out_str, x_s * x, &check);
    int y = round(y_res / y_s) + 12;
    if (y >= 0 && y < WIDTH)
      graph[WIDTH - 1 - y][x] = 1;
  }
  if (check == 1) {
  output(graph);
  } else {
    printf("ERROR");
  }

  return 0;
}

void output(int graph[WIDTH][LENGTH]) {
  for (int y = -1; y <= WIDTH; y++) {
    for (int x = -1; x <= LENGTH; x++) {
      if ((y >= 0 && y < WIDTH) && (x >= 0 && x < LENGTH)) {
        if (graph[y][x] == 0) {
          printf(".");
        } else {
          printf("*");
        }
      }
      if ((y != -1 && y != WIDTH) && (x == -1 || x == LENGTH)) {
        printf("||");
      }
      if (y == -1 || y == WIDTH) {
        printf("=");
      }
    }
    printf("\n");
  }
}
