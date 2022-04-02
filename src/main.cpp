#ifndef __MAIN_H__
#define __MAIN_H__

#include "../include/window.h"

int main(int argc, char** argv)
{
  Window window("Transformacoes Poligono", argc, argv);
  window.render();
  return (0);
}

#endif // __MAIN_H__