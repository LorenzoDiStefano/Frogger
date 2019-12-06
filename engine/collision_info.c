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
#include "engine/collision_info.h"

#ifdef _TEST

#include "engine/vector2.c"
#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/test_vector2.c"

#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

void collision_info_init(collision_info_t *collision_info)
{
    collision_info->collider = NULL;
    vector2_init(&collision_info->delta);
}


#ifdef _TEST

static int test_collision_info_init(collision_info_t *collision_info)
{
    collision_info_init(collision_info);
    return collision_info->collider == NULL &&
    collision_info->delta.x == 0 &&
    collision_info->delta.y == 0;
}

void test_collision_info()
{
    RUN_TEST_COLLISION_INFO(test_collision_info_init);
}

#endif