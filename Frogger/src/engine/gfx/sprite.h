#pragma once
#include "image_info.h"

typedef struct sprite
{
    SDL_Rect sprite_rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    float scale;
}sprite_t;

void sprite_init(sprite_t *sprite, image_info_t *img_info, SDL_Renderer *renderer, const float scale);