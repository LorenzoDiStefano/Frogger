#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/clock.c"
#include "tests/tests.c"
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

    fprintf(stdout, "Tests succeded: %llu failed: %llu\n", tests_succeded, tests_failed);
    return 0;
}