#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

#include "../include/RenderWindow.hpp"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700

int *range(int st, int end, int step=1) {
  int size = (end - st)/step;
  int *arr = new int[size];
  int i = 0;
  for (; st < end; st+=step){
    arr[i] = st;
    i++;
  }
  return arr;
}

int main(int argc, char *args[]) {

  if (SDL_INIT_VIDEO < 0) {
    std::cout << "SDL could not initialize.\nError: ";
    std::cout << SDL_GetError() << '\n';
  } else {
    // Initialize Window and Renderer
    RenderWindow window("test", SCREEN_WIDTH, SCREEN_HEIGHT);
    // Create Grid
    CreateGrid grid(&window, 20);
    Rectangle *arr = grid.createGrid(35, 35);

    grid.grid(arr, 35, 35);

    SDL_RenderPresent(window.getRenderer());
    
    bool isRunning = true;
    SDL_Event event;
    unsigned long generation = 0;

    while (isRunning) {
      // (1) Handle Input

      // Start Event loop
      while (SDL_PollEvent(&event)) {
	if (event.type == SDL_QUIT) {
	  isRunning = false;
	}
      }
      // (2) Handle Updtades

      // (3) Clear and Draw the screen
      std::cout << generation << '\n';
      generation++;
    }

    // for (int j = 0; j<35; j++) {
    //   for (int i = 0; i<35; i++) {
    // 	std::cout << "{x="<<arr[i*35+j].rect.x/20<<", y="<<arr[i*35+j].rect.y/20<<"},\n";
    //   }
    // }

    SDL_Quit();
  }

  int *ptr = range(0, 11, 2);

  return 0;
}
