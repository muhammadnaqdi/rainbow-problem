#include "rainbow.h"

int main(int argc, char *argv[]) {
  int v = atoi(argv[1]);
  int c = atoi(argv[2]);
  
  int ***g = rainbow_graph_create(v);
  
  rainbow_find(g, v, c, 1, 0, 1, 2, 3);

  return 0;
}
