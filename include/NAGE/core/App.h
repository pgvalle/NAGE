#pragma once

#include "scenes/Scene.h"

#include <SDL.h>

/*
 * Useful aliases
 */

#define FPS 60
#define FRAME_DELAY (1000 / FPS)

#ifndef ASSETS_DIR
#define ASSETS_DIR "./res/"
#endif

#define TILE 8

// These are the dimensions of the canvas. NOT of the window.
#define WIDTH  (28 * TILE) // 224
#define HEIGHT (32 * TILE) // 240

// no need to redeclare variables in App.cpp file again
#ifndef EXTERN
#define EXTERN extern
#endif

/**
 * API
*/

/**
 * imgs: path of the directory where all image resources are located
 * sfxs: ...
 * fonts: ...
 * 
 * They default to assets/{imgs, sfxs, fonts}/.
 * You may have directories within those base directories.
*/
struct Config {
  const char *title = "App",
             *imgs  = "./assets/imgs/",
             *sfxs  = "./assets/sfxs/",
             *fonts = "./assets/fonts/";

  Uint16 fps = 60;
  bool vsync = false;
  // window dimensions (defaults to a NES-like resolution)
  int tileSize = 8, wTile = 32, hTile = 30;
};

void initialize(const Config &conf);
void terminate();
// scene is owned by app
void run(Scene *scene);

// so that scenes can close app
EXTERN bool shouldClose;

bool isKeyPressed(int key);

void renderText(int x, int y, const char *text,
                SDL_Color color = {255, 255, 255, 255});
void renderClip(int x, int y, const SDL_Rect &clip);

#undef EXTERN

