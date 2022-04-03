#include "../include/window.h"
#include "../include/polygon.h"
#include "../include/window_callback.h"

Window::Window(const char* title, int argc, char** argv) : _title(title), _argc(argc), _argv(argv)
{
  _width = 600;
  _height = 500;
  _gVert = -1;
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

void Window::init()
{
  int i;

  _hasPolygon = false;
  pvertex->n_vertex = 0;
  _polygonType = GL_POINTS;

  for (i = 0; i < MAXVERTEXS; i++)
  {
    pvertex[i].v[0] = 0.0f;
    pvertex[i].v[1] = 0.0f;
    pvertex[i].v[2] = 0.0f;
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

void Window::drawPolygon()
{
  int i;

  glColor3f(0.0, 0.0, 0.0);

  glPolygonMode(GL_FRONT_AND_BACK, _polygonType);

  glBegin(_polygonType);
  for (i = 0; i < pvertex->n_vertex; i += 1)
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

  if (_gVert > -1) {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2fv(pvertex[_gVert].v);
    glEnd();
  }

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

void Window::keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27:
    exit(0);
  }
}

void Window::motion(int x, int y) {
  int i;
  float dx, dy;
  if (_gVert > -1) {
    x = x - (_width / 2);
    y = (_height / 2) - y;
    dx = x - pvertex[_gVert].v[0];
    dy = y - pvertex[_gVert].v[1];
    switch (_gOperation)
    {
    case 1:
      Transformation::translate(pvertex, dx, dy);
      break;
    case 2:
      Transformation::rotate(pvertex, _gVert, dx, dy);
      break;
    case 3:
      Transformation::scale(pvertex, _gVert, dx, dy);
      break;
    }
    display();
  }
}

void Window::mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT)
  {
    if (state == GLUT_DOWN)
    {
      x = x - (_width / 2);
      y = (_height / 2) - y;
      clipVertex(x, y);
    }
  }
  if (state == GLUT_UP)
  {
    std::cout << "Polygon: " << std::boolalpha << _hasPolygon << std::endl;
    _gVert = -1;
    if (button == GLUT_LEFT_BUTTON)
    {
      if (_hasPolygon == 0)
      {
        x = x - (_width / 2);
        y = (_height / 2) - y;

        glPointSize(3);

        pvertex[pvertex->n_vertex].v[0] = (float)x;
        pvertex[pvertex->n_vertex].v[1] = (float)y;
        pvertex->n_vertex++;
      }
    }
    else
      if (button == GLUT_RIGHT_BUTTON)
      {
        if (pvertex->n_vertex > 0)
        {
          _hasPolygon = 1;
          _polygonType = GL_LINE;
        }
      }
  }
  glutPostRedisplay();
}

void Window::handleMenuEvents(int option)
{
  switch (option)
  {
  case 0:
    init();
    break;
  }
  glutPostRedisplay();
}

void Window::handleSubMenu1Events(int option)
{
  if (option == 0)
    _polygonType = GL_POINTS;
  else if (option == 1)
  {
    _polygonType = GL_LINE_LOOP;
    _hasPolygon = true;
  }

  glutPostRedisplay();
}

void Window::handleSubMenu2Events(int option)
{
  _gOperation = option;
  glutPostRedisplay();
}

void Window::createGLUTMenus()
{
  int menu, submenu1, submenu2;

  submenu1 = glutCreateMenu(handleSubMenu1EventsCallback);
  glutAddMenuEntry("Pontos", 0);
  glutAddMenuEntry("Poligono", 1);

  submenu2 = glutCreateMenu(handleSubMenu2EventsCallback);
  glutAddMenuEntry("Translacao", 1);
  glutAddMenuEntry("Rotacao", 2);
  glutAddMenuEntry("Escala", 3);
  glutAddMenuEntry("Cisalhamento", 4);

  menu = glutCreateMenu(handleMenuEventsCallback);
  glutAddMenuEntry("Limpar", 0);
  glutAddSubMenu("Objetos", submenu1);
  glutAddSubMenu("Transformacoes", submenu2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Window::clipVertex(int x, int y)
{
  int i;
  float d;
  _gVert = -1;
  for (i = 0; i < pvertex->n_vertex; i++) {
    d = sqrt(pow((pvertex[i].v[0] - x), 2.0) + pow((pvertex[i].v[1] - y), 2.0));
    if (d < 3.0) {
      _gVert = i;
      break;
    }
  }
}

void Window::render()
{
  initGLUT();
  init();
  g_CurrentInstance = this;
  glutReshapeFunc(reshapeCallback);
  glutDisplayFunc(drawCallback);
  glutKeyboardFunc(keyboardCallback);

  glutMotionFunc(motionCallback);
  glutMouseFunc(mouseCallback);

  createGLUTMenus();

  glutMainLoop();
}




