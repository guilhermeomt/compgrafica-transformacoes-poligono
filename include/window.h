#include "GL/glut.h"
#include <string.h>


#ifndef __WINDOW_H__
#define __WINDOW_H__

class Window {
private:
  int _height;
  int _width;
  const char* _title;
  int _argc;
  char** _argv;
  GLenum _doubleBuffer;

  void initGLUT(int argc, char** argv);
  void args(int argc, char** argv);
  void init();
  void plotAxis();

public:
  Window() {};
  Window(const char* title, int argc, char** argv);
  ~Window();
  void display();
  void render();
};


#endif // __WINDOW_H__