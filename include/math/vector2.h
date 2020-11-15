#ifndef FROGGER_VECTOR2
#define FROGGER_VECTOR2
#pragma once

typedef struct vector2
{
    float x;
    float y;
}vector2_t;

vector2_t vector2_add(const vector2_t *first_value, const vector2_t *second_value);
vector2_t vector2_sub(const vector2_t *first_value, const vector2_t *second_value);
vector2_t vector2_mul(const vector2_t *first_value, const double value);
vector2_t vector2_mul_vec2(const vector2_t *first_value, const vector2_t *second_value);

int vector2_init(vector2_t *vector2);
int vector2_set(vector2_t *vector2, float x, float y);
int vector2_equals(const vector2_t *first_value, const vector2_t *second_value);
void vector2_normalize(vector2_t* p);
double vector2_length(vector2_t* p);

#endif // !FROGGER_VECTOR2