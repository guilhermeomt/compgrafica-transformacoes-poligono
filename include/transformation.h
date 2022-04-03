#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

class Transformation
{
public:
  Transformation() {};

  static void translate(struct Polygon (&pvertex)[30], float dx, float dy);
  // static void rotate(float dx, float dy);
  // static void scale(float dx, float dy);
  // static void shear(float dx, float dy);
  // static void reflect(float dx, float dy);
};


#endif // __TRANSFORMATION_H__