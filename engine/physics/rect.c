#ifndef FROGGER_RECT
#define FROGGER_RECT

#include "rect.h"
#include "vector2.h"
#include "collision_info.h"
#include "../actors/game_object.h"

void rect_init(rect_t* rect)
{
    rect->owner = NULL;
    rect->height = 0;
    rect->width = 0;
    rect->half_height = 0;
    rect->half_width = 0;
    vector2_init(&rect->position);
}

void rect_init_safe(rect_t* rect, const int width, const int height, const vector2_t position, game_object_t *owner)
{
    rect->owner = owner;
    rect->height = height;
    rect->width = width;
    rect->half_height = (float)height / 2;
    rect->half_width = (float)width / 2;
    rect->position = vector2_get_deep_copy(&position);
}

void rect_set_size(rect_t* rect, const int width, const int height)
{
    rect->height = height;
    rect->width = width;
    rect->half_height = (float)height / 2;
    rect->half_width = (float)width / 2;
}

void rect_set_position(rect_t* rect, const vector2_t new_position)
{
    rect_set_position_x(rect, new_position.x);
    rect_set_position_y(rect, new_position.y);
}

void rect_set_position_x(rect_t *rect, const float new_position_x)
{
    rect->position.x = new_position_x;
}

void rect_set_position_y(rect_t *rect, const float new_position_y)
{
    rect->position.y = new_position_y;
}

int rect_check_collision(rect_t *first_rect, rect_t *second_rect, collision_info_t *collision)
{
    if(first_rect->position.x < second_rect->position.x + second_rect->width &&
        first_rect->position.x + first_rect->width > second_rect->position.x &&
        first_rect->position.y < second_rect->position.y + second_rect->height &&
        first_rect->position.y + first_rect->height > second_rect ->position.y)
    {
        float x = 0;
        float y = 0;

        if(first_rect->position.x < second_rect->position.x)
            x = (first_rect->position.x + first_rect->width) - second_rect->position.x;
        else
            x = ((first_rect->position.x) - (second_rect->position.x + second_rect->width));

        if(first_rect->position.y < second_rect->position.y)
            y = (first_rect->position.y + first_rect->height) - second_rect->position.y;
        else
            y = ((first_rect->position.y) - (second_rect->position.y + second_rect->height));

        vector2_init_safe(&collision->delta, x, y);
        collision->collider = second_rect->owner;
        return 1;
    }

    return -1;
}

#ifdef _TEST

static int test_rect_init()
{
    rect_t rect;
    rect_init(&rect);

    return rect.owner == NULL &&
    rect.height == 0 &&
    rect.width == 0 &&
    rect.half_height == 0 &&
    rect.half_width == 0 &&
    rect.position.x == 0 &&
    rect.position.y == 0;
}

static int test_rect_init_safe()
{
    rect_t rect;
    game_object_t owner;
    vector2_t position;
    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&rect, 100, 50, position, &owner);

    return 
    rect.owner == &owner &&
    rect.width == 100 &&
    rect.height == 50 &&
    rect.half_width == 50 &&
    rect.half_height == 25 &&
    rect.position.x == 20 &&
    rect.position.y == 30;
}

static int test_rect_set_position()
{
    rect_t rect;
    vector2_t new_position;
    vector2_init_safe(&new_position, 100, 50);
    rect_set_position(&rect, new_position);

    return 
    rect.position.x == 100 && 
    rect.position.y == 50;
}

static int test_rect_set_position_x()
{
    rect_t rect;
    rect_init(&rect);
    rect_set_position_x(&rect, 100);

    return 
    rect.position.x == 100 && 
    rect.position.y == 0;
}

static int test_rect_set_position_y()
{
    rect_t rect;
    rect_init(&rect);
    rect_set_position_y(&rect, 100);
    return rect.position.x == 0 && rect.position.y == 100;
}

static int test_rect_collision_successful()
{
    rect_t first_rect, second_rect;
    collision_info_t collision_info;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&second_rect, 50, 50, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect, &collision_info);
    return collision == 1;
}

static int test_rect_collision_failed()
{
    rect_t first_rect, second_rect;
    collision_info_t collisio_info;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 51, 30);
    rect_init_safe(&second_rect, 5, 5, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect, &collisio_info);
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

#endif