#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

#include <iostream>
#include <math.h>

#define PHI 3.141572
#define ZERO 0.00001;

class Transformation
{
public:
  Transformation() {};

  static void translate(struct Polygon(&pvertex)[MAXVERTEXS], float dx, float dy);
  static void rotate(struct Polygon(&pvertex)[MAXVERTEXS], int gVert, float dx, float dy);
  static void scale(struct Polygon(&pvertex)[MAXVERTEXS], int gVert, float dx, float dy);
  // static void shear(float dx, float dy);
  // static void reflect(float dx, float dy);
};


#endif // __TRANSFORMATION_H__