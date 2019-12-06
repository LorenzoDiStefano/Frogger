#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/clock.c"
#include "main.c"
#include "engine/draw_manager.h"
#include "engine/draw_manager.c"
#ifdef _TEST

#include "tests/tests.c"
#include "tests/test_clock.c"

#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

void init_sprite(sprite_t *sprite, image_info_t img_info, SDL_Renderer *renderer, float scale)
{
    sprite->texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, img_info.width, img_info.height);
    sprite->scale = scale;
    sprite->sprite_rect.w = img_info.width*scale;
    sprite->sprite_rect.h = img_info.height*scale;
    sprite->sprite_rect.x = 0;
    sprite->sprite_rect.y = 0;

    SDL_SetTextureBlendMode(sprite->texture, SDL_BLENDMODE_BLEND);

    Uint8 *pixels = NULL;
    int pitch = 0;
    SDL_LockTexture(sprite->texture, NULL, (void **)&pixels, &pitch);

    memcpy(pixels, img_info.image, pitch * img_info.width);

    //free(img_info.image); //img info is not in the heap

    SDL_UnlockTexture(sprite->texture);
    sprite->renderer = renderer;
}

void draw_scene(draw_manager_t *draw_manager)
{
    SDL_SetRenderDrawColor(draw_manager->renderer, 67, 33, 33, 255);
    SDL_RenderClear(draw_manager->renderer);

    for (int i = 0; i < draw_manager->sprites_to_draw; i++)
    {
        sprite_t *sprite_address = draw_manager->sprites[i];
        SDL_RenderCopy(draw_manager->renderer, sprite_address->texture, NULL, &sprite_address->sprite_rect);
    }
    
    SDL_RenderPresent(draw_manager->renderer);
}

void draw_manager_add_sprite(draw_manager_t *draw_manager, sprite_t *sprite)
{
    draw_manager->sprites[draw_manager->sprites_to_draw] = sprite;
    draw_manager->sprites_to_draw++;
}

int draw_manager_init(draw_manager_t* draw_manager)
{
    draw_manager->window = SDL_CreateWindow("Game",100,100,640,480,SDL_WINDOW_SHOWN);

    if(!draw_manager->window)
    {
        return -1;
    }

    draw_manager->renderer = SDL_CreateRenderer(draw_manager->window,-1,SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);

    if(!draw_manager->renderer)
    {
        return -1;
    }

    draw_manager->draw_scene = draw_scene;
    SDL_SetRenderDrawBlendMode(draw_manager->renderer, SDL_BLENDMODE_BLEND);

    draw_manager->max_sprites = 100;
    draw_manager->sprites_to_draw = 0;
    draw_manager->sprites = malloc(100*sizeof(sprite_t));

    return 0;
}

int load_image(image_info_t *img,const char* path)
{
    int width, height, comp;
    unsigned char* image;
    image = stbi_load(path, &width, &height, &comp, STBI_rgb_alpha);

    //checking if loading was successfull
    SDL_Log("Loading img: %s",path);
    if (!image)
    {
        return 1;
    }

    img->image = image;
    img->width = width;
    img->height = height; 
    img->comp = comp;
    img->length = width*height;

    return 0;
}

#ifdef _TEST

static int test_draw_manager_init(draw_manager_t *draw_manager)
{
    int return_value = draw_manager_init(draw_manager);
    return !return_value &&
    draw_manager->max_sprites == 100 &&
    draw_manager->sprites_to_draw == 0;
}

void test_draw_manager()
{
    RUN_TEST_DRAW_MANAGER(test_draw_manager_init);
}

#endif