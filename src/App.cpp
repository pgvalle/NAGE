// no need to redeclare app fields here!
#define EXTERN

#include "NAGE/App.h"

#include <cstdio>
#include <cassert>
#include <cstring>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_FontCache.h>

#include <vector>

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Texture *atlas;
FC_Font *font;

Config config;

void initialize(const Config &conf)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  config = conf;

  const int w = conf.tileSize * conf.wTiles,
            h = conf.tileSize * conf.hTiles;

  window = SDL_CreateWindow(
      conf.title,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      w, h,
      SDL_WINDOW_RESIZABLE);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_RenderSetVSync(renderer, false);
  SDL_RenderSetLogicalSize(renderer, w, h); // resolution independent rendering

  // image assets
  SDL_Surface *surface = IMG_Load(conf.atlasPath);
  atlas = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  font = FC_CreateFont();
  FC_LoadFont(font, renderer, conf.fontPath, conf.tileSize,
              {255, 255, 255, 255}, TTF_STYLE_NORMAL);

  // surface = SDL_LoadBMP(ASSETS_DIR "icon.bmp");
  // SDL_SetWindowIcon(window, surface);
  // SDL_FreeSurface(surface);

  // audio assets

  shouldClose = false;
}

void terminate()
{
  // audio assets

  // images
  // SDL_DestroyTexture(texAtlas);
  // SDL_DestroyTexture(atlas);
  FC_FreeFont(font);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void run(Scene *scene)
{
  assert(scene);

  // only one run() in stack
  static bool running = false;
  assert(!running);
  running = true;

  Uint32 delta = 0;
  while (!shouldClose)
  {
    const Uint32 start = SDL_GetTicks();

    // query and process events
    SDL_Event event;
    if (SDL_WaitEventTimeout(&event, 16))
    {
      scene->processEvent(event);
    }

    scene->render(renderer);
    scene->update(1e-3f * delta); // pass delta in seconds

    SDL_RenderPresent(renderer);

    // we want 16 seconds
    const Uint32 realDelta = SDL_GetTicks() - start;
    if (realDelta < 16)
    {
      SDL_Delay(16 - realDelta);
    }
    // now we should get around 16 ms
    delta = SDL_GetTicks() - start;
  }

  delete scene;

  running = false;
}
