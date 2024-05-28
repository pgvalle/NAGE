#ifndef _NAGE_
#define _NAGE_

#include <SDL.h>

namespace NAGE
{
  class Timer
  {
  private:
    float elapsed = 0, timeout = 0;

  public:
    bool hasTimedOut() const
    {
      return timeout <= elapsed;
    }

    void update(float delta);
    void reset(float newTimeout = 0);
  };


  class Scene
  {
    public:
      virtual ~Scene() {}

      virtual void processEvent(const SDL_Event &event) = 0;
      virtual void update(float delta) = 0;
      virtual void render(SDL_Renderer *renderer) = 0;
  };


  void init();
  void quit();

  // scene is owned by app
  void run(Scene *scene);

  /* PROPERTIES */

  void setTitle(const char *title);
  void setIcon(const char *path);
  void setDimensions(int wTiles, int hTiles, int tileSize = 8);
  void setFPS(int fps);

  /* ASSETS */

  void loadAtlas(const char *path);
  void loadFont(const char *path);
  void loadSFX(const char *path);

  /* EVENT */

  /**
   * The data is copied, saved in userevent.data1 and the event owns the copy.
   * Be aware that if an user defined event isn't processed, it will be discarted.
   */
  bool pushEvent(int code, const void *data, size_t dataLen);

  template <class T>
  static inline bool pushEvent(int code, const T &value)
  {
    return pushEvent(code, &value, sizeof(T));
  }

  template <class T>
  static inline T getEventData(const SDL_UserEvent &event, size_t offset = 0)
  {
    return *(T *)((Uint8 *)event.data1 + offset);
  }

  // RENDERING
  // Just worry about using SDL_Renderer directly if you're thinking of using threads.

  void setColor(Uint32 color);  // 0xAARRGGBB
  void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

  void setFlip(SDL_RendererFlip flip);  // See SDL_RendererFlip enum to know more

  void setBlend(bool blend);  // to use palettes

  void renderTile(int x, int y, int atlasX, int atlasY);
  void renderTile(int x, int y, int id);
  void renderText(int x, int y, const char *text, ...);
}

#endif /* _NAGE_ */
