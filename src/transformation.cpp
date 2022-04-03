#include "../include/polygon.h"
#include "../include/transformation.h"

float* calculateCenter(struct Polygon(&pvertex)[MAXVERTEXS])
{
  int i;
  float* gCen = new float[3];

  gCen[0] = gCen[1] = 0.0f;
  for (i = 0; i < pvertex->n_vertex; i++) {
    gCen[0] += pvertex[i].v[0];
    gCen[1] += pvertex[i].v[1];
  }
  gCen[0] /= pvertex->n_vertex;
  gCen[1] /= pvertex->n_vertex;

  return gCen;
}

void translateCenter(struct Polygon pvertex[MAXVERTEXS], float* gCen, int t)
{
  int i;
  // translada para centro
  for (i = 0; i < pvertex->n_vertex; i++) {
    pvertex[i].v[0] += (t * gCen[0]);
    pvertex[i].v[1] += (t * gCen[1]);
  }
}

void Transformation::translate(struct Polygon(&pvertex)[MAXVERTEXS], float dx, float dy)
{
  int i;
  for (i = 0; i < pvertex->n_vertex; i++) {
    pvertex[i].v[0] += dx;
    pvertex[i].v[1] += dy;
  }
}

void Transformation::rotate(struct Polygon(&pvertex)[MAXVERTEXS], int gVert, float dx, float dy)
{
  int i;
  float oo, theta, xy[3], * gCen;

  gCen = calculateCenter(pvertex);
  translateCenter(pvertex, gCen, -1);

  oo = pvertex[gVert].v[1] * dx - pvertex[gVert].v[0] * dy;

  float	gAng = (2.0f * PHI) / 180.0f;
  theta = gAng;
  if (oo > 0.0f)
    theta = -1.0f * gAng;

  for (i = 0; i < pvertex->n_vertex; i++) {
    xy[0] = pvertex[i].v[0];
    xy[1] = pvertex[i].v[1];
    pvertex[i].v[0] = xy[0] * cos(theta) - xy[1] * sin(theta);
    pvertex[i].v[1] = xy[0] * sin(theta) + xy[1] * cos(theta);
  }
  translateCenter(pvertex, gCen, 1);

  delete gCen;
}
