#include "App.h"
#include "AppGlobals.h"

#include <cstdarg>

#include <SDL_FontCache/SDL_FontCache.h>

Uint8 r = 0,
      g = 0,
      b = 0,
      a = 0xff;

SDL_RendererFlip flip = SDL_FLIP_NONE;

SDL_BlendMode blend = SDL_BLENDMODE_NONE;

void NAGE::setColor(Uint32 color)
{
  b = Uint8((color >>  0) & 0xff);
  g = Uint8((color >>  8) & 0xff);
  r = Uint8((color >> 16) & 0xff);
  a = Uint8((color >> 24) & 0xff);
}

void NAGE::setColor(Uint8 a_r, Uint8 a_g, Uint8 a_b, Uint8 a_a)
{
  b = a_b;
  g = a_g;
  r = a_r;
  a = a_a;
}

void NAGE::setFlip(SDL_RendererFlip a_flip)
{
  flip = a_flip;
}

void NAGE::setBlend(bool a_blend)
{
  blend = blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE;
}

// save and restore user drawing context
void toggleUserCtx()
{
  static SDL_BlendMode usrBlend;
  static Uint8 usrR, usrG, usrB, usrA;

  static bool userCtxOn = true; // first call is to save user ctx
  if (userCtxOn)
  {
    // save
    SDL_GetRenderDrawBlendMode(renderer, &usrBlend);
    SDL_GetRenderDrawColor(renderer, &usrR, &usrG, &usrB, &usrA);

    // set to options here
    SDL_SetRenderDrawBlendMode(renderer, blend);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
  }
  else
  {
    SDL_SetRenderDrawBlendMode(renderer, usrBlend);
    SDL_SetRenderDrawColor(renderer, usrR, usrG, usrB, usrA);
  }

  userCtxOn = !userCtxOn;
}

void NAGE::renderTile(int x, int y, int atlasX, int atlasY)
{
  toggleUserCtx(); // save

  const SDL_Rect src = {atlasX, atlasY, 8, 8}, 
                 dst = {x, y, 8, 8};
  SDL_RenderCopyEx(renderer, atlas, &src, &dst, 0, nullptr, flip);

  toggleUserCtx(); // restore
}

void NAGE::renderTile(int x, int y, int id)
{
  // get atlas width
  int atlasW;
  SDL_QueryTexture(atlas, nullptr, nullptr, &atlasW, nullptr);

  // map index to position
  const int a = 8 * (id % (atlasW / 8)),
            b = 8 * (id / (atlasW / 8));
  renderTile(x, y, a, b);
}

void NAGE::renderText(int x, int y, const char *text, ...)
{
  toggleUserCtx(); // save

  static char buffer[1024];
  va_list args;
  va_start(args, text);
  vsprintf(buffer, text, args);
  va_end(args);
  FC_Draw(font, renderer, x, y, buffer);

  toggleUserCtx(); // restore
}
