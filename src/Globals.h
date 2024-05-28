#ifndef _GLOBALS_
#define _GLOBALS_

#include <SDL.h>
#include <SDL_FontCache/SDL_FontCache.h>

#ifndef EXT
#define EXT(type, name, val) extern type name
#endif

EXT(SDL_Window *, window, nullptr);
EXT(SDL_Renderer *, renderer, nullptr);

// assets
EXT(SDL_Texture *, atlas, nullptr);
EXT(FC_Font *, font, nullptr);

EXT(int, fps, 60);

EXT(int, tileSize, 8);

#undef EXT

#endif /* _GLOBALS_ */
