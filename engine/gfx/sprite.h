#ifndef FROGGER_SPRITE_HEADER
#define FROGGER_SPRITE_HEADER

#define SDL_MAIN_HANDLED
#include <SDL.h>

typedef struct image_info
{
    int width, height, comp, length;
    unsigned char *image;
    SDL_Texture *texture;
}image_info_t;

typedef struct sprite
{
    SDL_Rect sprite_rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    float scale;
}sprite_t;

void load_texture(image_info_t *img_info, SDL_Renderer *renderer);
int load_image(image_info_t *img, const char* path);
void init_sprite(sprite_t *sprite, image_info_t *img_info, SDL_Renderer *renderer, float scale);

#endif