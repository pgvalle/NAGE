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

#undef EXTERN
