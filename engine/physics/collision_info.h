#ifndef FROGGER_COLLISION_INFO_HEADER
#define FROGGER_COLLISION_INFO_HEADER

#include "vector2.h"

typedef struct collision_info
{
    vector2_t delta;
    void *collider;

}collision_info_t;

#define COLLIDER_TYPE_PLAYER 1
#define COLLIDER_TYPE_CAR 2
#define COLLIDER_TYPE_OBASTACLE 4
#define COLLIDER_TYPE_END 8
#define COLLIDER_TYPE_WATER 16
#define COLLIDER_TYPE_LOG 0

void collision_info_init(collision_info_t *collision_info);

#ifdef _TEST
void test_wrapper(const char *name, int (*func)(void));
#define RUN_TEST_COLLISION_INFO(func) test_wrapper(#func, func);

void test_collision_info();

#endif
#include "collision_info.c"
#endif