// no need to redeclare app fields here!
#define EXTERN

#include "App.h"
#include "AppGlobals.h"

#include <ctime>
#include <cstdio>
#include <cassert>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_FontCache/SDL_FontCache.h>

void App::init()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  srand(time(nullptr));

  window = SDL_CreateWindow(
      "Application",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      50 * tileSize, 28 * tileSize,
      SDL_WINDOW_RESIZABLE);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_RenderSetVSync(renderer, false);
}

void quit()
{
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
  while (true)
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
