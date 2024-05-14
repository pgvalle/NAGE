#include "App.h"

#include <cstdarg>

#include <SDL_FontCache/SDL_FontCache.h>

SDL_Renderer *renderer;
SDL_Texture *atlas;
FC_Font *font;

Uint8 _r = 0,
      _g = 0,
      _b = 0,
      _a = 0xff;

SDL_RendererFlip _flip = SDL_FLIP_NONE;

bool _blend = false;

void App::setColor(Uint32 color)
{
  _b = Uint8((color >>  0) & 0xff);
  _g = Uint8((color >>  8) & 0xff);
  _r = Uint8((color >> 16) & 0xff);
  _a = Uint8((color >> 24) & 0xff);
}

void App::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  _b = b;
  _g = g;
  _r = r;
  _a = a;
}

void App::setFlip(SDL_RendererFlip flip)
{
  _flip = flip;
}

void App::setBlend(bool blend)
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

void App::renderTile(int x, int y, int AtlasX, int atlasY)
{
  toggleUserCtx(); // save

  SDL_SetRenderDrawBlendMode(renderer, _blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
  SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);

  const SDL_Rect src = {AtlasX, atlasY, 8, 8}, 
                 dst = {x, y, 8, 8};
  SDL_RenderCopyEx(renderer, atlas, &src, &dst, 0, nullptr, _flip);

  toggleUserCtx(); // restore
}


void App::renderText(int x, int y, const char *text, ...)
{
  toggleUserCtx();

  SDL_SetRenderDrawBlendMode(renderer, _blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE);
  SDL_SetRenderDrawColor(renderer, _r, _g, _b, _a);

  static char buffer[1024];
  va_list args;
  va_start(args, text);
  vsprintf(buffer, text, args);
  va_end(args);
  FC_Draw(font, renderer, x, y, buffer);

  toggleUserCtx();
}
