#include "NAGE/Rendering.h"

#include <cstdarg>

#include <SDL_FontCache/SDL_FontCache.h>

/**
 * External dependencies
 */

extern SDL_Renderer *renderer;
extern SDL_Texture *atlas;
extern FC_Font *font;

/**
 * Internals
 */

Uint8 _r = 0,
      _g = 0,
      _b = 0,
      _a = 0xff;

SDL_RendererFlip _flip = SDL_FLIP_NONE;
bool _blend = false;

void setColor(Uint32 color)
{
  _b = Uint8((color >>  0) & 0xff);
  _g = Uint8((color >>  8) & 0xff);
  _r = Uint8((color >> 16) & 0xff);
  _a = Uint8((color >> 24) & 0xff);
}

void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  _b = b;
  _g = g;
  _r = r;
  _a = a;
}

void setFlip(SDL_RendererFlip flip)
{
  _flip = flip;
}

void setBlend(bool blend)
{
  _blend = blend;
}

// save and restore user drawing context
void toggleUserCtx()
{
  static SDL_BlendMode usrBlend;
  static Uint8 usrR, usrG, usrB, usrA;

  static bool userCtxOn = true; // first call is to save user ctx
  if (userCtxOn)
  {
    SDL_GetRenderDrawBlendMode(renderer, &usrBlend);
    SDL_GetRenderDrawColor(renderer, &usrR, &usrG, &usrB, &usrA);
  }
  else
  {
    SDL_SetRenderDrawBlendMode(renderer, usrBlend);
    SDL_SetRenderDrawColor(renderer, usrR, usrG, usrB, usrA);
  }

  userCtxOn = !userCtxOn;
}

void renderTile(int x, int y, int AtlasX, int atlasY)
{
  toggleUserCtx(); // save

  SDL_SetRenderDrawBlendMode(renderer, _blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
  SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);

  const SDL_Rect src = {AtlasX, atlasY, 8, 8}, 
                 dst = {x, y, 8, 8};
  SDL_RenderCopyEx(renderer, atlas, &src, &dst, 0, nullptr, _flip);

  toggleUserCtx(); // restore
}

void renderText(int x, int y, const char *text, ...)
{
  toggleUserCtx();

  SDL_SetRenderDrawBlendMode(renderer, _blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
  SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);

  va_list argList;
  va_start(argList, text);
  FC_Draw(font, renderer, x, y, text, argList);
  va_end(argList);

  toggleUserCtx();
}
