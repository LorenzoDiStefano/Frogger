#include "rigid_body.h"

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

#ifdef _TEST

static int rigid_body_init_test()
{
    rigid_body_t rigid_body;
    rigid_body_init(&rigid_body);

    vector2_t vector2_control;
    int return_value = vector2_init_safe(&vector2_control, 0, 0);

    return
    !return_value &&
    vector2_equals(&rigid_body.position, &vector2_control) &&
    vector2_equals(&rigid_body.direction, &vector2_control) &&
    vector2_equals(&rigid_body.velocity, &vector2_control) &&
    rigid_body.update == rigid_body_update &&
    rigid_body.on_collision == rigid_body_on_collision &&
    rigid_body.is_active == 0;
}

static int rigid_body_init_test_error()
{
    int return_value = vector2_init_safe(NULL, 0, 0);

    return
    return_value;
}

static int test_rigid_body_update_not_active()
{
    rigid_body_t rigid_body;
    rigid_body_init(&rigid_body);
    rigid_body.velocity.x = 5;
    rigid_body.update(&rigid_body, 1);
    return rigid_body.position.x == 0;
}

static int test_rigid_body_update_active()
{
    rigid_body_t rigid_body;
    rigid_body_init(&rigid_body);
    rigid_body.velocity.x = 5;
    rigid_body.is_active = 1;
    rigid_body.update(&rigid_body, 1);
    return rigid_body.position.x == 5;
}

void test_rigid_body()
{
    RUN_TEST_RIGID_BODY(test_rigid_body_update_not_active);
    RUN_TEST_RIGID_BODY(test_rigid_body_update_active);
    RUN_TEST_RIGID_BODY(rigid_body_init_test);
    RUN_TEST_RIGID_BODY(rigid_body_init_test_error);
}
#endif