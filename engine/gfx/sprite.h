#ifndef FROGGER_SPRITE_HEADER
#define FROGGER_SPRITE_HEADER

#include "image_info.h"

typedef struct sprite
{
    SDL_Rect sprite_rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    float scale;
}sprite_t;

void init_sprite(sprite_t *sprite, image_info_t *img_info, SDL_Renderer *renderer, const float scale);

#endif