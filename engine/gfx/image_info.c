#ifndef FROGGER_IMAGE_INFO
#define FROGGER_IMAGE_INFO

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../../stb_image.h"
#endif
#include "image_info.h"

int load_image(image_info_t *img, const char* path)
{
    img->image = stbi_load(path, &img->width, &img->height, &img->comp, STBI_rgb_alpha);

    SDL_Log("Loading img: %s",path);
    if (!img->image)
    {
        SDL_Log("Error loading img: %s",path);
        return 1;
    }

    img->length = img->width * img->height;

    return 0;
}

void load_texture(image_info_t *img_info, SDL_Renderer *renderer)
{
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, img_info->width, img_info->height);
    if(!texture)
        printf("error");

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    Uint8 *pixels = NULL;
    int pitch = 0;
    if (SDL_LockTexture(texture, NULL, (void **)&pixels, &pitch))
    {
        printf("Unable to map texture into address space");
    }
    memcpy(pixels, (void *)img_info->image, img_info->height * 4 * img_info->width);

    SDL_UnlockTexture(texture);

    img_info->texture = texture;
    return;
}
#endif