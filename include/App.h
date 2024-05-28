#ifndef _APP_
#define _APP_

#include "Scene.h"

#include <array>

namespace App
{
  void init();
  void quit();

  // scene is owned by app
  void run(Scene *scene);

  /**
   * PROPERTIES
   */

  void setTitle(const char *title);
  void setIcon(const char *path);
  void setDimensions(int wTiles, int hTiles, int tileSize = 8);
  void setFPS(int fps);

  /**
   * ASSETS 
   */

  void loadAtlas(const char *path);
  void loadFont(const char *path);
  void loadSFXs(const char *path);

  /**
   * EVENT
   */

  static inline bool pushEvent(const SDL_Event &event)
  {
    return SDL_PushEvent((SDL_Event *)&event);
  }

  /**
   * The data is copied, saved in userevent.data1 and the event owns the copy.
   * Be aware that if an user defined event isn't processed, it will be discarted.
   */
  bool pushUserEvent(int code, void *data, size_t dataLen);

  template <class T>
  static inline bool pushUserEvent(int code, const T &value)
  {
    return pushUserEvent(code, &value, sizeof(T));
  }

  template <class T>
  static inline T getUserEventData(const SDL_UserEvent &event, size_t offset = 0)
  {
    return *(T *)((Uint8 *)event.data1 + offset);
  }

  /**
   * RENDERING
   * Just worry about using SDL_Renderer directly if you're thinking of using threads.
   */

  // 0xAARRGGBB
  void setColor(Uint32 color);
  void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

  // See SDL_RendererFlip enum to know more
  void setFlip(SDL_RendererFlip flip);

  // to use palettes
  void setBlend(bool blend);

  void renderTile(int x, int y, int atlasX, int atlasY);
  void renderTile(int x, int y, int id);
  void renderText(int x, int y, const char *text, ...);
}

#endif /* _APP_ */
