#include "NAGE.h"
#include "Globals.h"

void NAGE::setTitle(const char *title)
{
  SDL_SetWindowTitle(window, title);
}

void NAGE::setIcon(const char *path)
{
  SDL_Surface *temp = SDL_LoadBMP(path);
  SDL_SetWindowIcon(window, temp);
  SDL_FreeSurface(temp);
}

void NAGE::setDimensions(int wTiles, int hTiles, int a_tileSize)
{
  tileSize = a_tileSize;

  const int w = tileSize * wTiles,
            h = tileSize * hTiles;
  SDL_SetWindowSize(window, w, h);
  SDL_RenderSetLogicalSize(renderer, w, h);
}

void NAGE::setFPS(int a_fps)
{
  fps = a_fps;
}
