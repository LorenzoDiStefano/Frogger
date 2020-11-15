#ifndef FROGGER_SPRITE
#define FROGGER_SPRITE
#pragma once

#include <SDL.h>

typedef struct image_info image_info_t;

typedef struct sprite
{
    SDL_Rect sprite_rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    float scale;
}sprite_t;

void sprite_init(sprite_t *sprite, image_info_t *img_info, SDL_Renderer *renderer, const float scale);

#endif // !FROGGER_SPRITE