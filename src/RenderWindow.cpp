#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../include/RenderWindow.hpp"

// RenderWindow Class
RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
  :window(NULL), renderer(NULL), w_W(p_w), w_H(p_h) {
  window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_W, w_H, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    std::cout << "Window failed to initialize.\nError: ";
    std::cout << SDL_GetError() << '\n';
  } else {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
  }
}

RenderWindow::~RenderWindow() {
  SDL_DestroyWindow(window);
  SDL_RenderClear(renderer);
  std::cout << "Destructor\n";
}

int RenderWindow::getWidth() {
  return w_W;
}

int RenderWindow::getHeight() {
  return w_H;
}

SDL_Window * RenderWindow::getWindow() {
  return window;
}

SDL_Renderer *RenderWindow::getRenderer() {
  return renderer;
}

void RenderWindow::test() {
  std::cout << w_W;
}

// CreateGrid Class
CreateGrid::CreateGrid(RenderWindow *p_renderWindow, int p_cellSize)
  :renderWindow(p_renderWindow), cellSize(p_cellSize) {
}

Rectangle *CreateGrid::createGrid(int p_rowS, int p_columnS, bool random) {
  columnS = p_columnS;
  rowS = p_rowS;
  Rectangle *arr = NULL;
  arr = new Rectangle[rowS * columnS];
  std::srand(std::time(NULL));

  int y = 0;
  for (int j = 0; j<rowS; j++) {
    int x = 0;
    for (int i = 0; i<columnS; i++) {
      SDL_Rect rect = {
	.x = x,
	.y = y,
	.w = cellSize - 1,
	.h = cellSize - 1,
      };
      bool alive;
      if (random == true) {
	int r = std::rand() % 20;
	alive = (r == 1)? true : false;
      } else {
	alive = false;
      }
      arr[i*rowS + j] = {.rect = rect, .alive = alive};
      x += cellSize;
    }
    y += cellSize;
  }
  return arr;
}

CreateGrid::~CreateGrid() {
  renderWindow->~RenderWindow();
  std::cout << "CreateGrid Destructor.\n";
}

void CreateGrid::grid(Rectangle *board, int rowS, int columnS) {
  int y = 0;
  for (int j = 0; j<rowS; j++) {
    int x = 0;
    for (int i = 0; i<columnS; i++) {
      if (board[i*rowS+j].alive == true) {
	SDL_SetRenderDrawColor(renderWindow->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderWindow->getRenderer(), &board[i*rowS+j].rect);
      } else {
	SDL_SetRenderDrawColor(renderWindow->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderWindow->getRenderer(), &board[i*rowS+j].rect);
      }
    }
  }
}

Rectangle *CreateGrid::check(Rectangle *CurBoard) {
  Rectangle *nBoard = NULL;
  nBoard = new Rectangle[rowS * columnS];
  nBoard = this->createGrid(rowS, columnS, false);

  /*
  (i-1), (j+1) | i, (j+1) | (i+1), (j+1)
  (i-1), j     |   i, j   | (i+1), j
  (i-1), (j-1) | i, (j-1) | (i+1), (j-1)
  */

  for (int j = 0; j<rowS; j++) {
    for (int i = 0; i<columnS; i++) {
      unsigned short int aliveNeighbors = 0;
      int x = CurBoard[i*rowS+j].rect.x/20;
      int y = CurBoard[i*rowS+j].rect.y/20;

      int arr[8][2] = {{(i-1), (j-1)},
		       {i    , (j-1)},
		       {(i+1), (j-1)},
		       {(i-1),     j},
		       {(i+1),     j},
		       {(i-1), (j+1)},
		       {i    , (j+1)},
		       {(i+1), (j+1)},
      };
      for (int in = 0; in<8; in++) {
	int a = arr[in][0];
	int b = arr[in][1];

	if (a < 0 || b < 0) {
	  continue;
	} else if (a > rowS || b > columnS) {
	  continue;
	} else {
	  if (CurBoard[a*rowS+b].alive == true) {
	    aliveNeighbors++;
	  }
	}
	
      }

      if (CurBoard[i*rowS+j].alive == true && (aliveNeighbors == 2 || aliveNeighbors == 3)) {
	nBoard[i*rowS+j].alive = true;
      } else if (CurBoard[i*rowS+j].alive == false && aliveNeighbors == 3) {
	nBoard[i*rowS+j].alive = true;
      } else {
	nBoard[i*rowS+j].alive = false;
      }

    }
  }

  delete [] CurBoard;
  return nBoard;
}

int CreateGrid::getCellSize() {
  return cellSize;
}

int CreateGrid::getColumnS() {
  return columnS;
}

int CreateGrid::getRowS() {
  return rowS;
}
