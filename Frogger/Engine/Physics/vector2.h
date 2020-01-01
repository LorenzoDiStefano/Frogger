#ifndef FROGGER_VECTOR2_HEADER
#define FROGGER_VECTOR2_HEADER

#include <stdio.h>
#include <stdlib.h>

typedef struct vector2
{
    float x;
    float y;

}vector2_t;

vector2_t vector2_add(const vector2_t *first_value, const vector2_t *second_value);
vector2_t vector2_sub(const vector2_t *first_value, const vector2_t *second_value);
vector2_t vector2_mul(const vector2_t *first_value, const double value);
vector2_t vector2_mul_vec2(const vector2_t *first_value, const vector2_t *second_value);
vector2_t vector2_get_deep_copy(const vector2_t *vector2);

int vector2_init(vector2_t *vector2);
int vector2_init_safe(vector2_t *vector2, float x, float y);
int vector2_equals(const vector2_t *first_value, const vector2_t *second_value);

#endif