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
#include "engine/game_object.h"
#include "engine/game_object.c"

#ifdef _TEST

#include "engine/vector2.c"
#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/test_vector2.c"
#include "tests/test_collision_info.c"

#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

typedef struct collision_info
{
    vector2_t delta;
    game_object_t *first_collider, *second_collider;

}collision_info_t;

#define COLLIDER_TYPE_PLAYER 1
#define COLLIDER_TYPE_WALL 2
#define COLLIDER_TYPE_OBASTACLE 4

void collision_info_init(collision_info_t *collision_info);

#ifdef _TEST
void collision_info_test_wrapper(const char *name, int (*func)(collision_info_t *collision_info));
#define RUN_TEST_COLLISION_INFO(func) collision_info_test_wrapper(#func, func);

void test_collision_info();

#endif