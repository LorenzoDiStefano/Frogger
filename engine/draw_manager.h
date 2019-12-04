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

typedef struct draw_manager
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    void (*draw_scene)(struct draw_manager *draw_manager);
} draw_manager_t;

int draw_manager_init(draw_manager_t* draw_manager);

#ifdef _TEST
void draw_manager_test_wrapper(const char *name, int (*func)(draw_manager_t *draw_manager));
#define RUN_TEST_DRAW_MANAGER(func) draw_manager_test_wrapper(#func, func);

void test_draw_manager();

#endif