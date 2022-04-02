
#include "../include/window.h"

Window::Window(const char* title, int argc, char **argv) : _title(title), _argc(argc), _argv(argv)
{
  _height = 600;
  _width = 500;
}

Window::~Window()
{
  
}

void Window::initGLUT(int argc, char **argv)
{
  GLenum type;

  glutInit(&_argc, _argv);
  args(argc, argv);

  type = GLUT_RGB;
  type |= (_doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;

  glutInitDisplayMode(type);
  glutInitWindowSize(_height, _width);
  glutCreateWindow(_title);

}

void Window::args(int argc, char **argv)
{
  GLint i;

  _doubleBuffer = GL_FALSE;

  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-sb") == 0)
    {
      _doubleBuffer = GL_FALSE;
    }
    else if (strcmp(argv[i], "-db") == 0)
    {
      _doubleBuffer = GL_TRUE;
    }
  }
}

void Window::plotAxis()
{
  int windW = _width / 2;
  int windH = _height / 2;

  glLineWidth(1);

  glColor3f(1.0, 0.0, 0.0);

  glBegin(GL_LINE_STRIP);
  glVertex2f(-windW, 0);
  glVertex2f(windW, 0);
  glEnd();

  glBegin(GL_LINE_STRIP);
  glVertex2f(0, -windH);
  glVertex2f(0, windH);
  glEnd();
}

void Window::display()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  plotAxis();

  if (_doubleBuffer)
  {
    glutSwapBuffers();
  }
  else
  {
    glFlush();
  }
}

Window* g_CurrentInstance;

extern "C"
void drawCallback()
{
  g_CurrentInstance->display();
}

void Window::render()
{
  initGLUT(_argc, _argv);
  ::g_CurrentInstance = this;
  ::glutDisplayFunc(::drawCallback);
  glutMainLoop();
}


