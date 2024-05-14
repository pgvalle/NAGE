#include "App.h"
#include "AppGlobals.h"

#include <cstdarg>

#include <SDL_FontCache/SDL_FontCache.h>

Uint8 r = 0,
      g = 0,
      b = 0,
      a = 0xff;

SDL_RendererFlip flip = SDL_FLIP_NONE;

bool blend = false;

void App::setColor(Uint32 color)
{
  b = Uint8((color >>  0) & 0xff);
  g = Uint8((color >>  8) & 0xff);
  r = Uint8((color >> 16) & 0xff);
  a = Uint8((color >> 24) & 0xff);
}

void App::setColor(Uint8 a_r, Uint8 a_g, Uint8 a_b, Uint8 a_a)
{
  b = a_b;
  g = a_g;
  r = a_r;
  a = a_a;
}

void App::setFlip(SDL_RendererFlip a_flip)
{
  flip = a_flip;
}

void App::setBlend(bool a_blend)
{
  blend = a_blend;
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

  const SDL_BlendMode mode = blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE;
  SDL_SetRenderDrawBlendMode(renderer, mode);
  SDL_SetRenderDrawColor(renderer, r, g, b, a);

  const SDL_Rect src = {AtlasX, atlasY, 8, 8}, 
                 dst = {x, y, 8, 8};
  SDL_RenderCopyEx(renderer, atlas, &src, &dst, 0, nullptr, flip);

  toggleUserCtx(); // restore
}


void App::renderText(int x, int y, const char *text, ...)
{
  toggleUserCtx();

  const SDL_BlendMode mode = blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE;
  SDL_SetRenderDrawBlendMode(renderer, mode);
  SDL_SetRenderDrawColor(renderer, r, g, b, a);

  static char buffer[1024];
  va_list args;
  va_start(args, text);
  vsprintf(buffer, text, args);
  va_end(args);
  FC_Draw(font, renderer, x, y, buffer);

  toggleUserCtx();
}
