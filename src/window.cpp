#include "../include/window.h"
#include "../include/polygon.h"

Window::Window(const char* title, int argc, char** argv) : _title(title), _argc(argc), _argv(argv)
{
  _width = 600;
  _height = 500;
}

Window::~Window()
{

}

void Window::initGLUT()
{
  GLenum type;

  glutInit(&_argc, _argv);
  args();

  type = GLUT_RGB;
  type |= (_doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;

  glutInitDisplayMode(type);
  glutInitWindowSize(_width, _height);
  glutCreateWindow(_title);

}

void Window::args()
{
  GLint i;

  _doubleBuffer = GL_FALSE;

  for (i = 1; i < _argc; i++)
  {
    if (strcmp(_argv[i], "-sb") == 0)
    {
      _doubleBuffer = GL_FALSE;
    }
    else if (strcmp(_argv[i], "-db") == 0)
    {
      _doubleBuffer = GL_TRUE;
    }
  }
}

void circulo(float r, float ang, float pp[3])
{
}

void Window::init()
{
  float ang, gAng;

  for (int i = 0; i < NPOLYGON; i++)
  {
    ang = (float)(i) * (2.0 * PHI) / ((float)(NPOLYGON));
    pvertex[i].v[0] = (float)(70.0 * cos(ang));
    pvertex[i].v[1] = (float)(70.0 * sin(ang));
    pvertex[i].v[2] = (float)0.0;
  }

  gAng = (2.0f * PHI) / 180.0f;
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

void Window::drawPolygon()
{
  int i;

  glColor3f(0.0, 0.0, 0.0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glBegin(GL_POLYGON);
  for (i = 0; i < NPOLYGON; i += 1)
  {
    glVertex2fv(pvertex[i].v);
  }
  glEnd();
}

void Window::display()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  plotAxis();

  drawPolygon();

  if (_doubleBuffer)
  {
    glutSwapBuffers();
  }
  else
  {
    glFlush();
  }
}

void Window::reshape(int width, int height)
{
  _width = width;
  _height = height;
  int windW = width / 2;
  int windH = height / 2;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-windW, windW, -windH, windH);

  glMatrixMode(GL_MODELVIEW);
}

Window* g_CurrentInstance;

extern "C"
void drawCallback()
{
  g_CurrentInstance->display();
}

extern "C"
void reshapeCallback(int width, int height) {
  g_CurrentInstance->reshape(width, height);
}

void Window::render()
{
  initGLUT();
  init();
  g_CurrentInstance = this;
  glutReshapeFunc(reshapeCallback);
  glutDisplayFunc(drawCallback);
  glutMainLoop();
}




