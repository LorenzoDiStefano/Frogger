#ifndef FROGGER_RIGID_BODY_HEADER
#define FROGGER_RIGID_BODY_HEADER

#include "rect.h"
#include "collision_info.h"

typedef struct rigid_body
{
    int is_active;
    vector2_t position;
    vector2_t velocity;
    vector2_t direction;
    rect_t bounding_box;

    void (*on_collision)(struct rigid_body *rigid_body, collision_info_t *collision);
    void (*update)(struct rigid_body *rigid_body, const double delta_time);
}rigid_body_t;

int rigid_body_init(rigid_body_t *rigid_body);
void rigid_body_set_position(rigid_body_t *rigid_body, const float x, const float y);
void rigid_body_set_position_with_vectors(rigid_body_t *rigid_body, const vector2_t new_value);

#ifdef _TEST
void test_wrapper(const char *name, int (*func)(void));
#define RUN_TEST_RIGID_BODY(func) test_wrapper(#func, func);
void test_rigid_body();
#endif
#endif