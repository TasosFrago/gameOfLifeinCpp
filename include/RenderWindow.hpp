#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <iostream>

struct Rectangle {
  SDL_Rect rect;
  bool alive;
};

class RenderWindow {
protected:
  SDL_Window *window;
  SDL_Renderer *renderer;
  const int w_W;
  const int w_H;
public:
  RenderWindow(const char *p_title, int p_w, int p_h);
  ~RenderWindow();
  int getWidth();
  int getHeight();
  SDL_Window *getWindow();
  SDL_Renderer *getRenderer();
  void test();
};

class CreateGrid {
private:
  RenderWindow *renderWindow;
  int cellSize;
  int rowS;
  int columnS;
public:
  CreateGrid(RenderWindow *p_renderWidnow, int p_cellSize);
  ~CreateGrid();
  Rectangle *createGrid(int rowS, int columnS, bool random=true);
  void grid(Rectangle *board, int rowS, int columnS);
  Rectangle *check(Rectangle *CurBoard);
  int getCellSize();
  int getRowS();
  int getColumnS();
};
