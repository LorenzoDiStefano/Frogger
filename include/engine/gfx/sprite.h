#ifndef FROGGER_SPRITE
#define FROGGER_SPRITE
#pragma once

#include <SDL.h>
#include <engine/gfx/interface_renderer.h>

typedef struct image_info image_info_t;

typedef struct sprite
{
    SDL_Rect sprite_rect;
    interface_texture_t* texture;
    interface_renderer_t* renderer;
    float scale;
}sprite_t;

void sprite_init(sprite_t *sprite, image_info_t *img_info, interface_renderer_t* renderer, const float scale);

#endif // !FROGGER_SPRITE