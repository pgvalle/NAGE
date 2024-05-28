#ifndef _SCENE_
#define _SCENE_

#include <SDL.h>

namespace NAGE
{
  class Scene
  {
    public:
      virtual ~Scene() {}

      virtual void processEvent(const SDL_Event &event) = 0;
      virtual void update(float delta) = 0;
      virtual void render(SDL_Renderer *renderer) = 0;
  };
}

#endif /* _SCENE_ */
