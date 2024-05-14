#include "App.h"
#include "AppGlobals.h"

#include <SDL_image.h>
//#include <SDL_mixer.h>
#include <SDL_FontCache/SDL_FontCache.h>

void App::loadAtlas(const char *path)
{
  SDL_Surface *temp = IMG_Load(path);
  atlas = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);
}

void App::loadFont(const char *path)
{
  font = FC_CreateFont();

  const SDL_Color white = {255, 255, 255, 255};
  FC_LoadFont(font, renderer, path, tileSize, white, TTF_STYLE_NORMAL);
}

void App::loadSFXs(const char *path)
{
  // TODO: implement me
}