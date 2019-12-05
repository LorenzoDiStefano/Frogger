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
#include "engine/rect.c"
#include "engine/rect.h"
#include "engine/vector2.c"
#include "engine/game_object.h"
#include "engine/game_object.c"

#ifdef _TEST

#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/test_vector2.c"
#include "tests/test_game_object.c"
#include "tests/test_rect.c"

#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#endif

void rect_init(rect_t* rect)
{
    rect->owner = NULL;
    rect->height = 0;
    rect->width = 0;
    rect->half_height = 0;
    rect->half_width = 0;
    vector2_init(&rect->position);
}

void rect_init_safe(rect_t* rect, int width, int height, vector2_t position, game_object_t *owner)
{
    rect->owner = owner;
    rect->height = height;
    rect->width = width;
    rect->half_height = height/2;
    rect->half_width = width/2;
    rect->position = vector2_get_deep_copy(&position);
}

void rect_set_position(rect_t* rect, vector2_t new_position)
{
    rect_set_position_x(rect, new_position.x);
    rect_set_position_y(rect, new_position.y);
}

void rect_set_position_x(rect_t *rect, float new_position_x)
{
    rect->position.x=new_position_x;
}

void rect_set_position_y(rect_t *rect, float new_position_y)
{
    rect->position.y=new_position_y;
}

//TODO:, return collision info instead of int, for now, return -1 on non collision, 1 on collision
int rect_check_collision(rect_t *first_rect, rect_t *second_rect)
{
    vector2_t distance = vector2_sub(&first_rect->position, &second_rect->position);

    float deltaX = fabs(distance.x) - (first_rect->half_width + second_rect->half_width);
    float deltaY = fabs(distance.y) - (first_rect->half_height + second_rect->half_height);

    if (deltaX <= 0 && deltaY <= 0)
    {
        //TODO: setting collision's info, something like this
        //collisionInfo.Type = Collision.CollisionType.RectsIntersection;
        //collisionInfo.Delta = new Vector2(-deltaX, -deltaY);

        return 1;
    }
    return -1;
}


#ifdef _TEST

static int test_rect_init(rect_t *rect)
{
    rect_init(rect);
    return rect->owner == NULL &&
    rect->height == 0 &&
    rect->width == 0 &&
    rect->half_height == 0 &&
    rect->half_width == 0 &&
    rect->position.x == 0 &&
    rect->position.y == 0;
}

static int test_rect_init_safe(rect_t *rect)
{
    game_object_t owner;
    vector2_t position;
    vector2_init_safe(&position,20,30);
    rect_init_safe(rect, 100, 50, position, &owner);

    return rect->owner == &owner &&
    rect->width == 100 &&
    rect->height == 50 &&
    rect->half_width == 50 &&
    rect->half_height == 25 &&
    rect->position.x == 20 &&
    rect->position.y == 30;
}

static int test_rect_set_position(rect_t *rect)
{
    vector2_t new_position;
    vector2_init_safe(&new_position, 100, 50);
    rect_set_position(rect,new_position);
    return rect->position.x == 100 && rect->position.y == 50;
}

static int test_rect_set_position_x(rect_t *rect)
{
    rect_set_position_x(rect, 100);
    return rect->position.x == 100 && rect->position.y == 0;
}

static int test_rect_set_position_y(rect_t *rect)
{
    rect_set_position_y(rect, 100);
    return rect->position.x == 0 && rect->position.y == 100;
}

static int test_rect_collision_successful(rect_t *rect)
{
    rect_t first_rect, second_rect;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&second_rect, 50, 50, position, NULL);

    rect_init_safe(rect, 100, 50, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect);
    return collision == 1;
}

static int test_rect_collision_failed(rect_t *rect)
{
    rect_t first_rect, second_rect;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&second_rect, 5, 5, position, NULL);

    rect_init_safe(rect, 100, 50, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect);
    return collision == -1;
}

void test_rect()
{
    RUN_TEST_RECT(test_rect_init);
    RUN_TEST_RECT(test_rect_init_safe);
    RUN_TEST_RECT(test_rect_set_position);
    RUN_TEST_RECT(test_rect_set_position_x);
    RUN_TEST_RECT(test_rect_set_position_y);
    RUN_TEST_RECT(test_rect_collision_successful);
    RUN_TEST_RECT(test_rect_collision_failed);
}

#endif