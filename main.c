#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  struct matrix *edges;

  edges = new_matrix(4, 4);

   edges = new_matrix(4, 4);
  add_edge(edges, 50, 450, 0, 100, 450, 0);
  add_edge(edges, 50, 450, 0, 50, 400, 0);
  add_edge(edges, 100, 450, 0, 100, 400, 0);
  add_edge(edges, 100, 400, 0, 50, 400, 0);

  add_edge(edges, 200, 450, 0, 250, 450, 0);
  add_edge(edges, 200, 450, 0, 200, 400, 0);
  add_edge(edges, 250, 450, 0, 250, 400, 0);
  add_edge(edges, 250, 400, 0, 200, 400, 0);

  add_edge(edges, 150, 400, 0, 130, 360, 0);
  add_edge(edges, 150, 400, 0, 170, 360, 0);
  add_edge(edges, 130, 360, 0, 170, 360, 0);

  add_edge(edges, 100, 340, 0, 200, 340, 0);
  add_edge(edges, 100, 320, 0, 200, 320, 0);
  add_edge(edges, 100, 340, 0, 100, 320, 0);
  add_edge(edges, 200, 340, 0, 200, 320, 0);

  free_matrix( edges );
}  
