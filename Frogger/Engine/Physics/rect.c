#ifndef FROGGER_RECT
#define FROGGER_RECT

#include "../actors/game_object.h"
#include "rect.h"

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
    rect->position = position;
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

        vector2_set(&collision->delta, x, y);
        collision->collider = second_rect->owner;
        return 1;
    }

    return -1;
}

#endif