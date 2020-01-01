#include "rigid_body.h"

int rigid_body_init(rigid_body_t *rigid_body)
{
    if(!rigid_body)
        return 1;

    rect_init(&rigid_body->bounding_box);
    vector2_init(&rigid_body->position);
    vector2_init(&rigid_body->velocity);
    vector2_init(&rigid_body->direction);
    rigid_body->update = rigid_body_update;
    rigid_body->on_collision = rigid_body_on_collision;
    rigid_body->is_active = 0;

    return 0;
}

void rigid_body_set_position(rigid_body_t *rigid_body, const float x, const float y)
{
    vector2_init_safe(&rigid_body->position, x, y);
    rigid_body->bounding_box.position = rigid_body->position;
}

void rigid_body_set_position_with_vectors(rigid_body_t *rigid_body, const vector2_t new_value)
{
    rigid_body->position = new_value;
    rigid_body->bounding_box.position = rigid_body->position;
}

void rigid_body_update(rigid_body_t *rigid_body, const double delta_time)
{
    if(rigid_body->is_active)
    {
        rigid_body->position.x += rigid_body->velocity.x * delta_time;
        rigid_body->position.y += rigid_body->velocity.y * delta_time;

        rigid_body->bounding_box.position.x = rigid_body->position.x;
        rigid_body->bounding_box.position.y = rigid_body->position.y;      
    }
}

void rigid_body_on_collision(rigid_body_t *rigid_body, collision_info_t *collision)
{
    if(rigid_body->is_active)
    {

    }
}