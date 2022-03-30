#ifndef __WINDOW_H__
#define __WINDOW_H__

class Window {
private:
  int m_windX;
  int m_windY;

public:
  Window(int x, int y);
  ~Window();
  void draw();


};

#endif // __WINDOW_H__