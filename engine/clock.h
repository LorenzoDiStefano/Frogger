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

typedef struct clock
{
    double delta_time_cached;
    Uint64 now;
    Uint64 last;

    void (*cache_now)(struct clock *clock); 
    double (*get_delta_time)(struct clock *clock); 

}clock_t;

void clock_init_safe(clock_t *clock);

#ifdef _TEST
void clock_test_wrapper(const char *name, int (*func)(clock_t *clock));
#define RUN_TEST(func) clock_test_wrapper(#func, func);

void test_clock();

#endif