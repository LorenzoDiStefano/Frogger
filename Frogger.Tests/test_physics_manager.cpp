#include "pch.h"
#include "Engine/Physics/physics_manager.h"

TEST(physics_manager_test, init)
{
    int return_value;
    physics_manager_t physics_manager;

    return_value = physics_manager_init(&physics_manager);

    EXPECT_TRUE
    (
        physics_manager.max_rb == 100 &&
        physics_manager.player_rb == NULL &&
        physics_manager.rb_count == 0 &&
        return_value == 0
    );
}

TEST(physics_manager_test, init_fail)
{
    int return_value;

    return_value = physics_manager_init(NULL);

    EXPECT_TRUE
    (
        return_value == 1
    );
}

TEST(physics_manager_test, add_rigid_body)
{
    physics_manager_t physics_manager;
    rigid_body_t rigid_body;

    physics_manager_init(&physics_manager);
    rigid_body_init(&rigid_body);

    physics_manager_add_rigid_body(&physics_manager, &rigid_body);

    EXPECT_TRUE
    (
        physics_manager.max_rb == 100 &&
        physics_manager.player_rb == NULL &&
        physics_manager.rb_count == 1
    );
}

TEST(physics_manager_test, add_player_rigid_body)
{
    physics_manager_t physics_manager;
    rigid_body_t rigid_body;

    physics_manager_init(&physics_manager);
    rigid_body_init(&rigid_body);

    physics_manager_add_player(&physics_manager, &rigid_body);

    EXPECT_TRUE
    (
        physics_manager.max_rb == 100 &&
        physics_manager.player_rb == &rigid_body &&
        physics_manager.rb_count == 0
    );
}

TEST(physics_manager_test, update_rb)
{
    physics_manager_t physics_manager;
    rigid_body_t player_rigid_body, obstacle_rigid_body;

    physics_manager_init(&physics_manager);
    rigid_body_init(&player_rigid_body);
    rigid_body_init(&obstacle_rigid_body);

    player_rigid_body.velocity.x = 5;
    player_rigid_body.is_active = 1;

    obstacle_rigid_body.velocity.y = 10;
    obstacle_rigid_body.velocity.x = -5;
    obstacle_rigid_body.is_active = 1;

    physics_manager_add_player(&physics_manager, &player_rigid_body);
    physics_manager_add_rigid_body(&physics_manager, &obstacle_rigid_body);
    physics_manager_update_rb(&physics_manager, 1);

    EXPECT_TRUE
    (
        physics_manager.max_rb == 100 &&
        physics_manager.player_rb == &player_rigid_body &&
        physics_manager.rb_count == 1 &&
        player_rigid_body.position.x == 5 * player_rigid_body.direction.x &&
        player_rigid_body.position.y == 0 * player_rigid_body.direction.y &&
        obstacle_rigid_body.position.x == -5 * obstacle_rigid_body.direction.x &&
        obstacle_rigid_body.position.y == 10 * obstacle_rigid_body.direction.y
    );
}