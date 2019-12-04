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

typedef struct clock_test
{
    clock_t base;
    Uint64 fake_now;
} clock_test_t;

void clock_test_cache_now(clock_t *clock)
{
    clock_test_t *clock_test = (clock_test_t *)clock;
    clock_test->base.last = clock_test->base.now;
    clock_test->base.now = clock_test->fake_now;
}

void clock_test_wrapper(const char *name, int (*func)(clock_t *clock))
{
    clock_test_t clock;
    clock_init_safe((clock_t *)&clock);

    clock.base.cache_now = clock_test_cache_now;
    clock.fake_now = 55;

    if (!func((clock_t *)&clock))
    {
        fprintf(stderr, "TEST %s FAILED\n", name);
        tests_failed++;
    }
    else
    {
        tests_succeded++;
    } 
}