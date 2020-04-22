#include "../../pch.h"

TEST(rigid_body_tests, init)
{
    rigid_body_t rigid_body;
    vector2_t vector2_control;
    vector2_t vector2_normalized_default_direction;

    vector2_set(&vector2_normalized_default_direction, 1, 1);
    vector2_normalize(&vector2_normalized_default_direction);

    rigid_body_init(&rigid_body);

    int return_value = vector2_set(&vector2_control, 0, 0);

    EXPECT_TRUE
    (
        !return_value &&
        vector2_equals(&rigid_body.position, &vector2_control) &&
        vector2_equals(&rigid_body.velocity, &vector2_control) &&
        vector2_equals(&rigid_body.direction, &vector2_normalized_default_direction) &&
        rigid_body.update == rigid_body_update &&
        rigid_body.on_collision == rigid_body_on_collision &&
        rigid_body.is_active == 0
    );
}

TEST(rigid_body_tests, init_exit)
{
    EXPECT_EXIT(rigid_body_init(NULL), ::testing::ExitedWithCode(1), ".*");
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
    rigid_body_set_direction(&rigid_body, 1, 0);
    
    rigid_body.update(&rigid_body, 1);

    EXPECT_TRUE
    (
        rigid_body.position.x == 5
    );
}

TEST(rigid_body_tests, set_direction)
{
    rigid_body_t rigid_body;

    rigid_body_init(&rigid_body);

    rigid_body_set_direction(&rigid_body, 10, 0);

    EXPECT_TRUE(rigid_body.direction.x == 1);
    EXPECT_TRUE(rigid_body.direction.y == 0);
}

TEST(rigid_body_tests, set_owner_exit_NULL_args)
{
    EXPECT_EXIT(rigid_body_set_owner(NULL, NULL), ::testing::ExitedWithCode(1), ".*");
}

TEST(rigid_body_tests, set_owner_exit_NULL_rigid_body)
{
    game_object_t owner;
    EXPECT_EXIT(rigid_body_set_owner(NULL, &owner), ::testing::ExitedWithCode(1), ".*");
}

TEST(rigid_body_tests, set_owner_exit_NULL_owner)
{
    rigid_body_t rigi_body;
    EXPECT_EXIT(rigid_body_set_owner(&rigi_body, NULL), ::testing::ExitedWithCode(1), ".*");
}

TEST(rigid_body_tests, set_owner)
{
    rigid_body_t rigid_body;
    game_object_t owner;

    rigid_body_init(&rigid_body);

    rigid_body_set_direction(&rigid_body, 10, 0);
    rigid_body_set_owner(&rigid_body, &owner);

    EXPECT_TRUE(rigid_body.owner == &owner);

}