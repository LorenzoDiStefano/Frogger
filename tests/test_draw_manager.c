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
#include "tests/tests.c"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

void draw_manager_test_init(draw_manager_t *draw_manager)
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO))
    {
        SDL_Log("error %s",SDL_GetError());
    }
}

void draw_manager_test_wrapper(const char *name, int (*func)(draw_manager_t *draw_manager))
{
    draw_manager_t draw_manager;
    draw_manager_init((draw_manager_t *)&draw_manager);

    if (!func((draw_manager_t *)&draw_manager))
    {
        fprintf(stderr, "TEST %s FAILED\n", name);
        tests_failed++;
    }
    else
    {
        tests_succeded++;
    } 
}