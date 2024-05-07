// no need to redeclare app fields here!
#define EXTERN
#define APP_INTERNALS

#include "App.h"

#include <cassert>
#include <cstring>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <vector>

/*
 * Private app stuff
 */

static SDL_Window* window;
static SDL_Renderer *renderer;
// assets
static std::vector<SDL_Texture *> atlases;


void initialize(const Config &conf) {
  const int w = conf.tileSize * conf.wTile,
            h = conf.tileSize * conf.hTile;

  window = SDL_CreateWindow(
    "Space Invaders Clone",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    w, h,
    SDL_WINDOW_RESIZABLE
  );

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_RenderSetVSync(renderer, conf.vsync);
  SDL_RenderSetLogicalSize(renderer, w, h); // resolution independent rendering


  // image assets
  surface = IMG_Load(ASSETS_DIR "atlas.png");
  atlas = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  surface = SDL_LoadBMP(ASSETS_DIR "icon.bmp");
  SDL_SetWindowIcon(window, surface);
  SDL_FreeSurface(surface);

  // audio assets

  shouldClose = false;
}

void terminate() {
  // audio assets

  // images
  SDL_DestroyTexture(texAtlas);
  SDL_DestroyTexture(atlas);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

/*
 * here it comes what is in header
 */
#include <cstdio>
void run(Scene *scene) {
  assert(scene);

  // only one run() in stack
  static bool running = false;
  assert(!running);
  running = true;

  loadAssets();
  
  Uint32 delta = 0;
  while (!shouldClose) {
    const Uint32 start = SDL_GetTicks();

    // query and process events
    SDL_Event event;
    if (SDL_WaitEventTimeout(&event, FRAME_DELAY)) {
      scene->processEvent(event);
    }

    scene->render(renderer);
    scene->update(1e-3 * delta); // delta in seconds

    SDL_RenderPresent(renderer);

    // we want FRAME_DELAY seconds
    const Uint32 realDelta = SDL_GetTicks() - start;
    if (realDelta < FRAME_DELAY) {
      SDL_Delay(FRAME_DELAY - realDelta);
    }
    // now we should get around FRAME_DELAY seconds
    delta = SDL_GetTicks() - start;
  }

  delete scene;

  freeAssets();
  running = false;
}

bool isKeyPressed(int key) {
  const Uint8 *keys = SDL_GetKeyboardState(nullptr);
  return keys[key];
}

void renderClip(int x, int y, const SDL_Rect &clip) {
  const SDL_Rect scale = {x, y, clip.w, clip.h};
  SDL_RenderCopy(renderer, atlas, &clip, &scale);
}

void renderText(int x, int y, const char *text, SDL_Color color) {
  for (int i = 0; i < (int)strlen(text); i++) {
    const char c = text[i] - 32; // printable characters only

    const SDL_Rect srcRect = {TILE * c, 0, TILE, TILE};
    const SDL_Rect dstRect = {x + TILE * i, y, TILE, TILE};
    SDL_RenderCopy(renderer, texAtlas, &srcRect, &dstRect);
  }
}

