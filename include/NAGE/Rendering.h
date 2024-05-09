#pragma once

#include <SDL.h>
#include <cstdint>

/**
 * Drawing capabilities. Only apply to things offered by this library.
 * If you use renderer directly, this will not affect it.
 */

/**
 * See SDL_RendererFlip enum to know more.
 * Flips are applied after rotation
 */
void setFlip(SDL_RendererFlip flip);

// ARGB format
void setColor(Uint32 color);
void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);

// to use palettes
void setBlend(bool blend);

void renderTile(int x, int y, int AtlasX, int atlasY);
void renderText(int x, int y, const char *text, ...);