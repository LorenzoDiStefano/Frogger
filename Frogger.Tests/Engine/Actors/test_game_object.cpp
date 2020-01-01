#include "pch.h"
#include "Actors/game_object.h"

TEST(game_object_tests, init)
{
    game_object_t game_object;
    game_object_init(&game_object);

    EXPECT_TRUE
    (
        game_object.is_active == 0 &&
        game_object.collider_type == 0 &&
        game_object.sprite == NULL &&
        game_object.update == game_object_update &&
        game_object.position.x == 0 &&
        game_object.position.y == 0
    );
}

TEST(game_object_tests, init_with_vectors)
{
    game_object_t game_object;
    vector2_t position, velocity;
    vector2_init_safe(&position, 100, 100);
    vector2_init_safe(&velocity, 50, 50);

    game_object_init_with_vectors(&game_object, &position, &velocity);
    EXPECT_TRUE
    (
        game_object.is_active == 0 &&
        game_object.collider_type == 0 &&
        game_object.sprite == NULL &&
        game_object.update == game_object_update &&
        game_object.position.x == 100 &&
        game_object.position.y == 100
    );
}

TEST(game_object_tests, update)
{
    game_object_t game_object;
    rigid_body_t rigid_body;

    rigid_body_init(&rigid_body);
    game_object_init(&game_object);

    game_object.rigid_body = &rigid_body;
    game_object.is_active = 1;
    game_object_update(&game_object, 1);

    EXPECT_TRUE
    (
        game_object.position.x == 0 &&
        game_object.position.y == 0
    );
}

TEST(game_object_tests, update_moving)
{
    game_object_t game_object;
    rigid_body_t rigid_body;

    rigid_body_init(&rigid_body);
    game_object_init(&game_object);

    game_object.rigid_body = &rigid_body;
    game_object.is_active = 1;
    game_object.rigid_body->is_active = 1;

    rigid_body.velocity.x = 5;
    rigid_body_update(&rigid_body, 1);
    game_object_update(&game_object, 1);

    EXPECT_TRUE(game_object.position.y == 0);
    EXPECT_TRUE(game_object.position.x == 5);
}

TEST(game_object_tests, set_velocity_x)
{
    game_object_t game_object;
    rigid_body_t rigid_body;

    rigid_body_init(&rigid_body);
    game_object_init(&game_object);

    game_object.rigid_body = &rigid_body;
    game_object_set_velocity_x(&game_object, 1);

    EXPECT_TRUE
    (
        game_object.rigid_body->velocity.x == 1 &&
        game_object.rigid_body->velocity.y == 0
    );
}

TEST(game_object_tests, set_velocity_y)
{
    game_object_t game_object;
    rigid_body_t rigid_body;

    rigid_body_init(&rigid_body);
    game_object_init(&game_object);

    game_object.rigid_body = &rigid_body;
    game_object_set_velocity_y(&game_object, 1);

    EXPECT_TRUE
    (
        game_object.rigid_body->velocity.x == 0 &&
        game_object.rigid_body->velocity.y == 1
    );
}

TEST(game_object_tests, set_velocity)
{
    game_object_t game_object;
    rigid_body_t rigid_body;
    vector2_t new_velocity;

    rigid_body_init(&rigid_body);
    vector2_init_safe(&new_velocity, 50, 40);
    game_object_init(&game_object);

    game_object.rigid_body = &rigid_body;
    game_object_set_velocity(&game_object, new_velocity);

    EXPECT_TRUE
    (
        game_object.rigid_body->velocity.x == 50 &&
        game_object.rigid_body->velocity.y == 40
    );
}

TEST(game_object_tests, set_position_x)
{
    game_object_t game_object;
    game_object_init(&game_object);
    game_object_set_position_x(&game_object, 1);

    EXPECT_TRUE
    (
        game_object.position.x == 1 &&
        game_object.position.y == 0
    );
}

TEST(game_object_tests, set_position_y)
{
    game_object_t game_object;
    game_object_init(&game_object);
    game_object_set_position_y(&game_object, 1);

    EXPECT_TRUE
    (
        game_object.position.x == 0 &&
        game_object.position.y == 1
    );
}


TEST(game_object_tests, set_position)
{
    game_object_t game_object;
    vector2_t new_position;
    vector2_init_safe(&new_position, 50, 40);
    game_object_init(&game_object);
    game_object_set_position(&game_object, 100, 40);

    EXPECT_TRUE
    (
        game_object.position.x == 100 &&
        game_object.position.y == 40
    );
}