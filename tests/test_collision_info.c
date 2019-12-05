#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/vector2.h"
#include "engine/clock.c"
#include "engine/rect.c"
#include "engine/rect.h"
#include "engine/collision_info.h"
#include "engine/collision_info.c"
#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/tests.c"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

void collision_info_test_wrapper(const char *name, int (*func)(collision_info_t *collision_info))
{
    collision_info_t collision_info;
    collision_info_init((collision_info_t *)&collision_info);

    if (!func((collision_info_t *)&collision_info))
    {
        fprintf(stderr, "TEST %s FAILED\n", name);
        tests_failed++;
    }
    else
    {
        tests_succeded++;
    } 
}