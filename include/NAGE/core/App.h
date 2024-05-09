#pragma once

#include "Scene.h"

#include <SDL.h>

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
  const char *fontPath, *atlasPath, *sfxPath;
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
 * Drawing capabilities
*/

// You're all by yourself when rendering stuff
void disableDrawingContext();
// Drawing context restored to the last values passed to the functions
void enableDrawingContext();

/**
 * See SDL_RendererFlip enum to know more.
 * Flips are applied after rotation
*/
void setFlip(SDL_RendererFlip flip);

// ARGB format
void setColor(uint32_t color);
void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0);

void setBlend(bool blend);

void renderTile(int x, int y, int id);
void renderText(int x, int y, const char *text);

#undef EXTERN

