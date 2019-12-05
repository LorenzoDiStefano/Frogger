#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/vector2.h"
#include "tests/tests.c"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

int vector2_init(vector2_t *vector2)
{
    if(vector2==NULL)
        return 0;
    
    vector2->x = 0;
    vector2->y = 0;
    return 1;
}

int vector2_init_safe(vector2_t *vector2, float x,float y)
{
    if(vector2==NULL)
        return 0;
    
    vector2->x = x;
    vector2->y = y;
    return 1;
}

vector2_t vector2_add(vector2_t *first_value,vector2_t *second_value)
{
    vector2_t result;
    result.x = (first_value->x) + (second_value->x);
    result.y = (first_value->y) + (second_value->y);
    return result;
}

vector2_t vector2_sub(vector2_t *first_value,vector2_t *second_value)
{
    vector2_t result;
    result.x = (first_value->x) - (second_value->x);
    result.y = (first_value->y) - (second_value->y);
    return result;
}

#ifdef _TEST

static int test_init(vector2_t *vector2)
{
    int ret_val = vector2_init(vector2);
    return vector2->x==0 && vector2->y==0 && ret_val == 1;
}

static int test_init_safe(vector2_t *vector2)
{
    int ret_val = vector2_init_safe(vector2,50,70);
    return vector2->x==50 && vector2->y==70 && ret_val == 1;
}

static int test_add(vector2_t *vector2)
{
    vector2_t second_vector2;
    vector2_init_safe(vector2,50,70);
    vector2_init_safe(&second_vector2,50,70);
    second_vector2= vector2_add(vector2, &second_vector2);
    return second_vector2.x==100 && second_vector2.y==140;
}

static int test_sub(vector2_t *vector2)
{
    vector2_t second_vector2;
    vector2_init_safe(vector2,50,70);
    vector2_init_safe(&second_vector2,50,70);
    second_vector2= vector2_sub(vector2, &second_vector2);
    return second_vector2.x==0 && second_vector2.y==0;
}

void test_vector2()
{
    RUN_TEST_VECTOR2(test_init);
    RUN_TEST_VECTOR2(test_init_safe);
    RUN_TEST_VECTOR2(test_add);
    RUN_TEST_VECTOR2(test_sub);
}
#endif