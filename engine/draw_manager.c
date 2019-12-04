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

void draw_scene(draw_manager_t *draw_manager)
{
    SDL_SetRenderDrawColor(draw_manager->renderer,0,0,0,0);
    SDL_RenderClear(draw_manager->renderer);
    SDL_RenderPresent(draw_manager->renderer);
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

    return 0;
}

#ifdef _TEST

static int test_draw_manager_init(draw_manager_t *draw_manager)
{
    int return_value = draw_manager_init(draw_manager);
    return !return_value;
}

void test_draw_manager()
{
    RUN_TEST_DRAW_MANAGER(test_draw_manager_init);
}
#endif