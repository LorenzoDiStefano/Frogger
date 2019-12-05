#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/draw_manager.h"
#include "engine/vector2.h"

#include "engine/draw_manager.c"
#include "engine/clock.c"
#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/test_vector2.c"
#include "tests/test_game_object.c"
#include "tests/test_rect.c"

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

static uint64_t tests_succeded = 0;
static uint64_t tests_failed = 0;

int run_tests()
{
    test_clock();
    test_draw_manager();
    test_vector2();
    test_game_object();
    test_rect();
    fprintf(stdout, "Tests succeded: %llu failed: %llu\n", tests_succeded, tests_failed);
    return 0;
}