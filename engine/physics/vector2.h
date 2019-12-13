
#ifndef FROGGER_VECTOR2_HEADER
#define FROGGER_VECTOR2_HEADER

#include <stdio.h>
#include <stdlib.h>

typedef struct vector2
{
    float x,y;

}vector2_t;

vector2_t vector2_add(vector2_t *first_value, vector2_t *second_value);//return first_value+second_value
vector2_t vector2_sub(vector2_t *first_value, vector2_t *second_value);//return first_value-second_value
vector2_t vector2_mul(vector2_t *first_value, double value);
vector2_t vector2_get_deep_copy(vector2_t *vector2);

int vector2_init(vector2_t *vector2);
int vector2_init_safe(vector2_t *vector2, float x, float y);

#ifdef _TEST
void test_wrapper(const char *name, int (*func)());
#define RUN_TEST_VECTOR2(func) test_wrapper(#func, func);
void test_vector2();
#endif

#endif