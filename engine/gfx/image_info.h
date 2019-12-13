#ifndef FROGGER_IMAGE_INFO_HEADER
#define FROGGER_IMAGE_INFO_HEADER

#define SDL_MAIN_HANDLED
#include <SDL.h>

typedef struct image_info
{
    int width, height, comp, length;
    unsigned char *image;
    SDL_Texture *texture;
}image_info_t;

void load_texture(image_info_t *img_info, SDL_Renderer *renderer);
int load_image(image_info_t *img, const char* path);

#endif