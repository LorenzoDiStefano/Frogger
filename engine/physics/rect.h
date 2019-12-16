#ifndef FROGGER_RECT_HEADER
#define FROGGER_RECT_HEADER

#include "vector2.h"

typedef struct game_object game_object_t;

typedef struct rect
{
    vector2_t position;
    game_object_t *owner;//should be game_object
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
//int rect_check_collision(rect_t *first_rect, rect_t *second_rect, collision_info_t *collision);

#ifdef _TEST
void test_wrapper(const char *name, int (*func)());
#define RUN_TEST_RECT(func) test_wrapper(#func, func);

void test_rect();

#endif

#include "rect.c"
#endif