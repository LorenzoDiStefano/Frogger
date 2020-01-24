#include "rigid_body.h"

void rigid_body_init(rigid_body_t *rigid_body)
{
    if (!rigid_body)
    {
        printf("rigid body init null pointer");
        exit(1);
    }

    rect_init(&rigid_body->bounding_box);
    vector2_init(&rigid_body->position);
    vector2_init(&rigid_body->velocity);
    vector2_init(&rigid_body->direction);

    rigid_body->update = rigid_body_update;
    rigid_body->on_collision = rigid_body_on_collision;
    rigid_body->is_active = 0;
    rigid_body->owner = NULL;

    rigid_body_set_direction(rigid_body, 1, 1);
}

void rigid_body_set_position(rigid_body_t *rigid_body, const float x, const float y)
{
    if (!rigid_body)
    {
        printf("rigid body set position null pointer");
        exit(1);
    }

    vector2_set(&rigid_body->position, x, y);
    rigid_body->bounding_box.position = rigid_body->position;
}

void rigid_body_set_position_with_vector2(rigid_body_t *rigid_body, const vector2_t new_value)
{
    if (!rigid_body)
    {
        printf("rigid_body_set_position_with_vectors null pointer");
        exit(1);
    }

    rigid_body->position = new_value;
    rigid_body->bounding_box.position = rigid_body->position;
}

void rigid_body_update(rigid_body_t *rigid_body, const double delta_time)
{
    if (!rigid_body)
    {
        printf("rigid rigid_body_update null pointer");
        exit(1);
    }

    if(rigid_body->is_active)
    {
        rigid_body->position.x += rigid_body->velocity.x * delta_time * rigid_body->direction.x;
        rigid_body->position.y += rigid_body->velocity.y * delta_time * rigid_body->direction.x;

        rigid_body->bounding_box.position.x = rigid_body->position.x;
        rigid_body->bounding_box.position.y = rigid_body->position.y;      
    }
}

void rigid_body_on_collision(rigid_body_t *rigid_body, collision_info_t *collision)
{
    if (!rigid_body || !collision)
    {
        printf("rigid_body_on_collision null pointer");
        exit(1);
    }
}

void rigid_body_set_owner(rigid_body_t* rigid_body, game_object_t* owner)
{
    if (!rigid_body || !owner)
    {
        printf("rigid_body_set_owner null pointer");
        exit(1);
    }

    rigid_body->owner = owner;
}

void rigid_body_set_direction(rigid_body_t* rigid_body, const float x, const float y)
{
    if (!rigid_body)
    {
        printf("rigid_body_set_direction null pointer");
        exit(1);
    }

    vector2_set(&rigid_body->direction, x, y);
    vector2_normalize(&rigid_body->direction);
}

void rigid_body_set_direction_with_vector2(rigid_body_t* rigid_body, const vector2_t new_value)
{
    if (!rigid_body)
    {
        printf("rigid_body_set_direction_with_vector2 null pointer");
        exit(1);
    }

    rigid_body->direction = new_value;
    vector2_normalize(&rigid_body->direction);
}