
#ifndef FROGGER_VECTOR2
#define FROGGER_VECTOR2

#include "vector2.h"

int vector2_init(vector2_t *vector2)
{
    if(vector2 == NULL)
    {
        return 1;
    }
    
    vector2->x = 0;
    vector2->y = 0;
    return 0;
}

int vector2_init_safe(vector2_t *vector2, float x, float y)
{
    if(vector2 == NULL)
    {
        return 1;
    }
    
    vector2->x = x;
    vector2->y = y;
    return 0;
}

vector2_t vector2_add(const vector2_t *first_value, const vector2_t *second_value)
{
    vector2_t result;
    result.x = (first_value->x) + (second_value->x);
    result.y = (first_value->y) + (second_value->y);
    return result;
}

vector2_t vector2_sub(const vector2_t *first_value, const vector2_t *second_value)
{
    vector2_t result;
    result.x = (first_value->x) - (second_value->x);
    result.y = (first_value->y) - (second_value->y);
    return result;
}

vector2_t vector2_mul(const vector2_t *first_value, const double value)
{
    vector2_t result;

    result.x = first_value->x * value;
    result.y = first_value->y * value;

    return result;
}

vector2_t vector2_get_deep_copy(const vector2_t *vector2)
{
    vector2_t result;

    result.x = vector2->x;
    result.y = vector2->y;

    return result;
}

#ifdef _TEST

static int test_vector2_init()
{
    vector2_t vector2;
    int ret_val = vector2_init(&vector2);
    return vector2.x == 0 && vector2.y == 0 && ret_val == 0;
}

static int test_vector2_init_safe()
{
    vector2_t vector2;
    int ret_val = vector2_init_safe(&vector2, 50, 70);
    return vector2.x == 50 && vector2.y == 70 && ret_val == 0;
}

static int test_vector2_add()
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_init_safe(&second_vector2, 50, 70);
    second_vector2 = vector2_add(&vector2, &second_vector2);
    return second_vector2.x == 100 && second_vector2.y == 140;
}

static int test_vector2_sub()
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_init_safe(&second_vector2, 50, 70);
    second_vector2 = vector2_sub(&vector2, &second_vector2);
    return second_vector2.x == 0 && second_vector2.y == 0;
}

static int test_vector2_deep_copy()
{
    vector2_t vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_t second_vector2 = vector2_get_deep_copy(&vector2);
    return second_vector2.x == 50 && second_vector2.y == 70 &&
    &(second_vector2.y) != &(vector2.y) && &(second_vector2.x) != &(vector2.x);
}

static int test_vector2_mul()
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 10, 2);
    second_vector2 = vector2_mul(&vector2, 4);
    return second_vector2.x == 40 && second_vector2.y == 8;
}

void test_vector2()
{
    RUN_TEST_VECTOR2(test_vector2_init);
    RUN_TEST_VECTOR2(test_vector2_init_safe);
    RUN_TEST_VECTOR2(test_vector2_add);
    RUN_TEST_VECTOR2(test_vector2_sub);
    RUN_TEST_VECTOR2(test_vector2_mul);
    RUN_TEST_VECTOR2(test_vector2_deep_copy);
}
#endif
#endif