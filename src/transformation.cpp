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

void Transformation::scale(struct Polygon(&pvertex)[MAXVERTEXS], int gVert, float dx, float dy)
{
  int i;
  float sx, sy, * gCen;

  gCen = calculateCenter(pvertex);
  translateCenter(pvertex, gCen, -1);

  sx = sy = 1.0f;
  if (fabs(pvertex[gVert].v[0]) > 0.01f)
    sx = 1.0f + dx / pvertex[gVert].v[0];
  if (fabs(pvertex[gVert].v[1]) > 0.01f)
    sy = 1.0f + dy / pvertex[gVert].v[1];
  for (i = 0; i < pvertex->n_vertex; i++) {
    pvertex[i].v[0] *= sx;
    pvertex[i].v[1] *= sy;
  }

  translateCenter(pvertex, gCen, 1);

  delete gCen;
}

void Transformation::shear(struct Polygon(&pvertex)[MAXVERTEXS], int gVert, float dx, float dy)
{
  int i;
  float sx, sy, xy[3], * gCen;

  sx = 0.001f * dx;
  sy = 0.001f * dy;
  if (dx > dy)
  {
    if (fabs(pvertex[gVert].v[0]) > 0.1f)
      sx = dx / pvertex[gVert].v[0];
  }
  else
  {
    if (fabs(pvertex[gVert].v[1]) > 0.1f)
      sy = dy / pvertex[gVert].v[1];
  }

  gCen = calculateCenter(pvertex);
  translateCenter(pvertex, gCen, -1);

  for (i = 0; i < pvertex->n_vertex; i++) {
    xy[0] = pvertex[i].v[0];
    xy[1] = pvertex[i].v[1];
    pvertex[i].v[0] = xy[0] + xy[1] * sx;
    pvertex[i].v[1] = xy[0] * sy + xy[1];
  }

  translateCenter(pvertex, gCen, 1);

  delete gCen;
}

void Transformation::reflect(struct Polygon(&pvertex)[MAXVERTEXS], float dx, float dy)
{
  int i;
  if (dx > 100.0f || dx < -100.0f)
  {
    for (i = 0; i < pvertex->n_vertex; i++) {
      pvertex[i].v[0] *= -1;
      pvertex[i].v[1] *= 1;
    }
  }
  if (dy > 100.0f || dy < -100.0f)
  {
    for (i = 0; i < pvertex->n_vertex; i++) {
      pvertex[i].v[0] *= 1;
      pvertex[i].v[1] *= -1;
    }
  }
}
