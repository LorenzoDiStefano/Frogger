#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/vector2.h"
#include "engine/game_object.h"
#include "engine/clock.c"
#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/tests.c"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif


void game_object_test_init(game_object_t *draw_manager)
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO))
    {
        SDL_Log("error %s",SDL_GetError());
    }
}

void game_object_test_wrapper(const char *name, int (*func)(game_object_t *game_object))
{
    game_object_t game_object;
    game_object_init((game_object_t *)&game_object);

    if (!func((game_object_t *)&game_object))
    {
        fprintf(stderr, "TEST %s FAILED\n", name);
        tests_failed++;
    }
    else
    {
        tests_succeded++;
    } 
}