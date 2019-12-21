#include "collision_info.h"

void collision_info_init(collision_info_t *collision_info)
{
    collision_info->collider = NULL;
    vector2_init(&collision_info->delta);
}

#ifdef _TEST

static int test_collision_info_init()
{
    collision_info_t collision_info;
    collision_info_init(&collision_info);
    return collision_info.collider == NULL &&
    collision_info.delta.x == 0 &&
    collision_info.delta.y == 0;
}

void test_collision_info()
{
    RUN_TEST_COLLISION_INFO(test_collision_info_init);
}

#endif