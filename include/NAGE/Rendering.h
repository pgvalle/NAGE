/**
 * Drawing capabilities. Only apply to things offered by this library.
 * If you use renderer directly, this will not affect it.
 */

#pragma once

#include <SDL.h>

// 0xAARRGGBB
void setColor(Uint32 color);
void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

// See SDL_RendererFlip enum to know more
void setFlip(SDL_RendererFlip flip);

// to use palettes
void setBlend(bool blend);

void renderTile(int x, int y, int AtlasX, int atlasY);
void renderText(int x, int y, const char *text, ...);