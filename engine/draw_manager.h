#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/clock.c"
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

typedef struct image_info
{
    int width, height, comp, length;
    unsigned char *image;
}image_info_t;

typedef struct sprite
{
    SDL_Rect sprite_rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    int scale;
}sprite_t;

void init_sprite(sprite_t *sprite, image_info_t img_info, SDL_Renderer *renderer, int scale);

typedef struct draw_manager
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    sprite_t **sprites;
    int sprites_to_draw;
    int max_sprites;

    void (*draw_scene)(struct draw_manager *draw_manager);
} draw_manager_t;

int draw_manager_init(draw_manager_t* draw_manager);
int load_image(image_info_t *img, const char *path);

#ifdef _TEST
void draw_manager_test_wrapper(const char *name, int (*func)(draw_manager_t *draw_manager));
#define RUN_TEST_DRAW_MANAGER(func) draw_manager_test_wrapper(#func, func);

void test_draw_manager();

#endif