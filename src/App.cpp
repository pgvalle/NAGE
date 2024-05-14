// no need to redeclare app fields here!
#define EXTERN

#include "App.h"

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_FontCache/SDL_FontCache.h>

#include <vector>

SDL_Window *window;
SDL_Renderer *renderer;
// assets
SDL_Texture *atlas;
FC_Font *font;
int fps;
int tileSize;

void App::configure(const Config &conf)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  srand(time(nullptr));

  assert(conf.fps);
  fps = conf.fps;
  tileSize = conf.tileSize;

  const int w = tileSize * conf.wTiles,
            h = tileSize * conf.hTiles;

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
  FC_LoadFont(font, renderer, conf.fontPath, tileSize,
              {255, 255, 255, 255}, TTF_STYLE_NORMAL);

  surface = IMG_Load(conf.atlasPath);
  atlas = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  // surface = SDL_LoadBMP(ASSETS_DIR "icon.bmp");
  // SDL_SetWindowIcon(window, surface);
  // SDL_FreeSurface(surface);

  // audio assets

  shouldClose = false;
}

void App::terminate()
{
  // audio assets

  // SDL_DestroyTexture(texAtlas);
  SDL_DestroyTexture(atlas);
  FC_FreeFont(font);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void App::run(Scene *scene)
{
  assert(scene);

  // only one run() in stack
  static bool running = false;
  assert(!running);
  running = true;

  const Uint32 msPerFrame = 1000 / fps;
  Uint32 delta = 0;
  while (!shouldClose)
  {
    const Uint32 start = SDL_GetTicks();

    // query and process events
    SDL_Event event;
    if (SDL_WaitEventTimeout(&event, msPerFrame))
    {
      scene->processEvent(event);

      // free user events data. They were already processed
      if (event.type == SDL_USEREVENT)
      {
        free(event.user.data1);
      }
    }

    scene->render(renderer);
    scene->update(1e-3f * delta); // pass delta in seconds

    SDL_RenderPresent(renderer);

    // we want msPerFrame seconds
    const Uint32 realDelta = SDL_GetTicks() - start;
    if (realDelta < msPerFrame)
    {
      SDL_Delay(msPerFrame - realDelta);
    }
    // now we should get around msPerFrame ms
    delta = SDL_GetTicks() - start;
  }

  delete scene;

  running = false;
}

bool App::pushUserEvent(int code, void *data, size_t dataLen)
{
  SDL_UserEvent event;
  event.type = SDL_USEREVENT;
  event.code = code;

  if (data && dataLen > 0)
  {
    void *copy = malloc(dataLen);
    event.data1 = memcpy(copy, data, dataLen);
  }

  return (bool)SDL_PushEvent((SDL_Event *)&event);
}
