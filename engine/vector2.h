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
#include "engine/vector2.c"

#ifdef _TEST

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

typedef struct vector2
{
    float x,y;

}vector2_t;

vector2_t vector2_add(vector2_t *first_value, vector2_t *second_value);//return first_value+second_value
vector2_t vector2_sub(vector2_t *first_value, vector2_t *second_value);//return first_value-second_value
vector2_t vector2_mul(vector2_t *first_value, double value);
vector2_t vector2_get_deep_copy(vector2_t *vector2);
int vector2_init(vector2_t *vector2);
int vector2_init_safe(vector2_t *vector2, float x, float y);


#ifdef _TEST
void vector2_test_wrapper(const char *name, int (*func)(vector2_t *vector2));
#define RUN_TEST_VECTOR2(func) vector2_test_wrapper(#func, func);

void test_vector2();

#endif