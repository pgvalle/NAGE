#pragma once

#include <SDL.h>

/**
 * All scenes, but the main one, have a parent.
 *
 * You implement your own main scene:
 *   class MainScene : public Scene
 *
 * The parenting thing is to allow data access without passing as argument:
 *   childscene::childscene(Scene *urmum) {
 *     this->parent = urmum;
 *   }
 *
 *   void childscene::update(float delta) {
 *     this->parent->field.doSmth();
 *   }
 */
class Scene
{
protected:
  Scene *parent = nullptr;

public:
  virtual ~Scene() {}

  virtual void processEvent(const SDL_Event &event) = 0;
  virtual void update(float delta) = 0;
  virtual void render(SDL_Renderer *renderer) = 0;
};
