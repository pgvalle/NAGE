#include "NAGE/core/Rendering.h"

// declared somewhere else
extern SDL_Renderer *renderer;
extern SDL_Texture *atlas;

SDL_RendererFlip _flip = SDL_FLIP_NONE;
Uint8 _r = 0, _g = 0, _b = 0, _a = 0xff;
bool _blend = false;

void setFlip(SDL_RendererFlip flip)
{
  _flip = flip;
}

void setColor(uint32_t color)
{
  _b = Uint8((color >>  0) & 0xff);
  _g = Uint8((color >>  8) & 0xff);
  _r = Uint8((color >> 16) & 0xff);
  _a = Uint8((color >> 24) & 0xff);
}

void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0)
{
  _b = b;
  _g = g;
  _r = r;
  _a = a;
}

void setBlend(bool blend)
{
  _blend = blend;
}

void toggleUserCtx()
{
  static bool userCtxOn = true; // first call is to save user ctx
  static SDL_BlendMode userBlend;
  static Uint8 r, g, b, a;
  if (userCtxOn)
  {
    SDL_GetRenderDrawBlendMode(renderer, &userBlend);
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  }
  else
  {
    SDL_SetRenderDrawBlendMode(renderer, userBlend);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
  }

  userCtxOn = !userCtxOn;
}

void renderTile(int x, int y, int AtlasX, int atlasY)
{
  const SDL_Rect srcRect = {AtlasX, atlasY, 8, 8},
                 dstRect = {x, y, 8, 8};

  toggleUserCtx(); // save

  SDL_SetRenderDrawBlendMode(renderer, _blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
  SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);
  SDL_RenderCopyEx(renderer, atlas, &srcRect, &dstRect, 0, nullptr, _flip);

  toggleUserCtx(); // restore
}

void renderText(int x, int y, const char *text)
{
  // TODO: implement me
}
