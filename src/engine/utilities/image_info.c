#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"
#endif

#include <engine/utilities/image_info.h>
#include <engine/gfx/interface_texture.h>
#include <SDL.h>

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

void load_texture(image_info_t *img_info, interface_renderer_t *renderer)
{
    interface_texture_t* itexture = create_interface_texture(
        renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 
        img_info->width, img_info->height);

    if (!itexture->raw_data)
        printf("error");

    itexture->set_blend_mode(itexture, SDL_BLENDMODE_BLEND);

    Uint8 *pixels = NULL;
    int pitch = 0;

    if(itexture->lock(itexture, (void**)&pixels, &pitch))
    {
        printf("Unable to map texture into address space");
    }

    memcpy(pixels, (void *)img_info->image, (size_t)img_info->height * 4 * img_info->width);

    itexture->unlock(itexture);

    img_info->texture = itexture;

    return;
}