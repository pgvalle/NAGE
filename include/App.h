#pragma once

#include "Scene.h"

// no need to redeclare variables in App.cpp file again
#ifndef EXTERN
#define EXTERN extern
#endif

/**
 * Setup app
 * sfxPath: path to a directory
 */
struct Config
{
  const char *title = "Application";
  const char *atlasPath, *fontPath, *sfxPath;
  int fps = 30;
  int tileSize = 8, wTiles = 32, hTiles = 30;
};

/**
 * API
 */

void initialize(const Config &conf);
void terminate();
// scene is owned by app
void run(Scene *scene);

// so that scenes can close app
EXTERN bool shouldClose;

/**
 * Rendering capabilities. Only apply to things offered by this library.
 * If you use renderer directly, this will not affect it.
 */

// 0xAARRGGBB
void setColor(Uint32 color);
void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

// See SDL_RendererFlip enum to know more
void setFlip(SDL_RendererFlip flip);

// to use palettes
void setBlend(bool blend);

void renderTile(int x, int y, int AtlasX, int atlasY);
void renderText(int x, int y, const char *text, ...);

#undef EXTERN
