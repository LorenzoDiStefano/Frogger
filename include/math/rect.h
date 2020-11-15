#ifndef FROGGER_RECT
#define FROGGER_RECT
#pragma once

#include <engine/utilities/collision_info.h>

typedef struct game_object game_object_t;

typedef struct rect
{
    vector2_t position;
    game_object_t *owner;
    int width, height;
    float half_width, half_height;
} rect_t;

void rect_init(rect_t* rect);
void rect_set_size(rect_t* rect, const int width, const int height);
void rect_init_safe(rect_t* rect, const int width, const int height, const vector2_t position, game_object_t *owner);
void rect_set_position(rect_t* rect, const vector2_t new_position);
void rect_set_position_x(rect_t *game_object, const float new_position_x);
void rect_set_position_y(rect_t *game_object, const float new_position_y);
int rect_check_collision(rect_t *first_rect, rect_t *second_rect, collision_info_t *collision);

#endif // !FROGGER_RECT