#include "../../pch.h"

TEST(collision_info_test, init)
{
    collision_info_t collision_info;
    collision_info_init(&collision_info);
	EXPECT_TRUE(
        collision_info.collider == NULL &&
        collision_info.delta.x == 0 &&
        collision_info.delta.y == 0
	);
}
