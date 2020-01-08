#ifndef FROGGER_RIGID_BODY_HEADER
#define FROGGER_RIGID_BODY_HEADER

#include "rect.h"
#include "collision_info.h"

typedef struct game_object game_object_t;

typedef struct rigid_body
{
    int is_active;
    vector2_t position;
    vector2_t velocity;
    vector2_t direction;
    rect_t bounding_box;
    game_object_t *owner;

    void (*on_collision)(struct rigid_body *rigid_body, collision_info_t *collision);
    void (*update)(struct rigid_body *rigid_body, const double delta_time);
}rigid_body_t;

int rigid_body_init(rigid_body_t *rigid_body);
int rigid_body_set_owner(rigid_body_t* rigid_body, game_object_t *owner);
void rigid_body_set_position(rigid_body_t *rigid_body, const float x, const float y);
void rigid_body_set_position_with_vectors(rigid_body_t *rigid_body, const vector2_t new_value);
void rigid_body_update(rigid_body_t* rigid_body, const double delta_time);
void rigid_body_on_collision(rigid_body_t* rigid_body, collision_info_t *collision);

#endif