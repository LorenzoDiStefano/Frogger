#include "pch.h"
#include "Actors/game_object.h"
#include "Physics/rect.h"

TEST(rect_tests, rect_init)
{
    rect_t rect;
    rect_init(&rect);

    EXPECT_TRUE
    (
        rect.owner == NULL &&
        rect.height == 0 &&
        rect.width == 0 &&
        rect.half_height == 0 &&
        rect.half_width == 0 &&
        rect.position.x == 0 &&
        rect.position.y == 0
    );
}

TEST(rect_tests, rect_init_safe)
{
    rect_t rect;
    game_object_t owner;
    vector2_t position;
    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&rect, 100, 50, position, &owner);

    EXPECT_TRUE
    (
        rect.owner == &owner &&
        rect.width == 100 &&
        rect.height == 50 &&
        rect.half_width == 50 &&
        rect.half_height == 25 &&
        rect.position.x == 20 &&
        rect.position.y == 30
    );
}

TEST(rect_tests, set_position_x)
{
    rect_t rect;
    rect_init(&rect);
    rect_set_position_x(&rect, 100);

    EXPECT_TRUE(
        rect.position.x == 100 &&
        rect.position.y == 0);
}

TEST(rect_tests, set_position_y) 
{
    rect_t rect;
    rect_init(&rect);
    rect_set_position_y(&rect, 100);
    EXPECT_TRUE( rect.position.x == 0 && rect.position.y == 100);
}

TEST(rect_tests, set_position)
{
    rect_t rect;
    vector2_t new_position;
    vector2_init_safe(&new_position, 100, 50);
    rect_set_position(&rect, new_position);

    EXPECT_TRUE(
        rect.position.x == 100 &&
        rect.position.y == 50);
}

TEST(rect_tests, test_rect_collision_successful)
{
    rect_t first_rect, second_rect;
    collision_info_t collision_info;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&second_rect, 50, 50, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect, &collision_info);
    EXPECT_TRUE(collision == 1);
}

TEST(rect_tests, test_rect_collision_failed)
{
    rect_t first_rect, second_rect;
    collision_info_t collisio_info;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 51, 30);
    rect_init_safe(&second_rect, 5, 5, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect, &collisio_info);
    
    EXPECT_TRUE(collision == -1);
}
