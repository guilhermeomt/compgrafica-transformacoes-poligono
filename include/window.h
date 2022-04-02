#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include "GL/glut.h"
#include <string.h>
#include <math.h>

#define NPOLYGON 4
#define PHI 3.141572
#define ZERO 0.00001;

class Window {
private:
  int _height;
  int _width;
  const char* _title;
  int _argc;
  char** _argv;
  GLenum _doubleBuffer;
  int _polygonType;
  bool _hasPolygon;
  int _gOperation;

  void initGLUT();
  void args();
  void init();
  void plotAxis();
  void drawPolygon();
  void createGLUTMenus();

public:
  Window() {};
  Window(const char* title, int argc, char** argv);
  ~Window();
  void display();
  void reshape(int width, int height);
  void keyboard(unsigned char key, int x, int y);
  void mouse(int button, int state, int x, int y);
  void handleMenuEvents(int option);
  void handleSubMenu1Events(int option);
  void handleSubMenu2Events(int option);
  void render();

};


#endif // __WINDOW_H__