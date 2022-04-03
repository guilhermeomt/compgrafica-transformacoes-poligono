#include "../include/polygon.h"
#include "../include/transformation.h"

void Transformation::translate(struct Polygon (&pvertex)[30], float dx, float dy)
{
  int i;
  for (i = 0; i < pvertex->n_vertex; i++) {
    pvertex[i].v[0] += dx;
    pvertex[i].v[1] += dy;
  }

}
