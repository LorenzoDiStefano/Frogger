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
#include "engine/collision_info.h"
#include "engine/collision_info.c"

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

typedef struct rect
{
    vector2_t position;
    void *owner;//should be game_object
    int width, height;
    float half_width, half_height;
} rect_t;

void rect_init(rect_t* rect);
void rect_set_size(rect_t* rect, int width, int height);
void rect_init_safe(rect_t* rect, int width, int height, vector2_t position, void *owner);
void rect_set_position(rect_t* rect, vector2_t new_position);
void rect_set_position_x(rect_t *game_object, float new_position_x);
void rect_set_position_y(rect_t *game_object, float new_position_y);

//to do, return collision info instead of int
int rect_check_collision(rect_t *first_rect, rect_t *second_rect, collision_info_t *collision);

#ifdef _TEST
void rect_test_wrapper(const char *name, int (*func)(rect_t *rect));
#define RUN_TEST_RECT(func) rect_test_wrapper(#func, func);

void test_rect();

#endif