#ifndef _APP_
#define _APP_

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

void configure(const Config &conf);
void terminate();
// scene is owned by app
void run(Scene *scene);

// so that scenes can close app
EXTERN bool shouldClose;

/**
 * Send arbitrary data through events.
 * Data is copied and copy is owned by event.
 * If you want to push non-user events, use SDL_PushEvent directly.
 */
bool pushEvent(int code, void *data, size_t dataLen);
void freeEventData(SDL_UserEvent &event);

#define USER_EVENT_GET_TYPE(T)\
static inline T get##T##FromUserEvent(const SDL_UserEvent &event, size_t offset)\
{\
  return *(T *)(event.data1 + offset);\
}

USER_EVENT_GET_TYPE(Uint8);
USER_EVENT_GET_TYPE(Uint16);
USER_EVENT_GET_TYPE(Uint32);
USER_EVENT_GET_TYPE(Uint64);

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

#endif /* _APP_ */
