#include "pch.h"
#include "Physics/rigid_body.h"

TEST(rigid_body_tests, init)
{
    rigid_body_t rigid_body;
    vector2_t vector2_control;

    rigid_body_init(&rigid_body);

    int return_value = vector2_init_safe(&vector2_control, 0, 0);

    EXPECT_TRUE
    (
        !return_value &&
        vector2_equals(&rigid_body.position, &vector2_control) &&
        vector2_equals(&rigid_body.direction, &vector2_control) &&
        vector2_equals(&rigid_body.velocity, &vector2_control) &&
        rigid_body.update == rigid_body_update &&
        rigid_body.on_collision == rigid_body_on_collision &&
        rigid_body.is_active == 0
    );
}

TEST(rigid_body_tests, init_fail)
{
    int return_value = rigid_body_init(NULL);

    EXPECT_TRUE
    (
        return_value
    );
}

TEST(rigid_body_tests, update_not_active)
{
    rigid_body_t rigid_body;
    rigid_body_init(&rigid_body);
    rigid_body.velocity.x = 5;
    rigid_body.update(&rigid_body, 1);

    EXPECT_TRUE
    (
        rigid_body.position.x == 0
    );
}

TEST(rigid_body_tests, update_active)
{
    rigid_body_t rigid_body;
    rigid_body_init(&rigid_body);
    rigid_body.velocity.x = 5;
    rigid_body.is_active = 1;
    rigid_body.update(&rigid_body, 1);

    EXPECT_TRUE
    (
        rigid_body.position.x == 5
    );
}
