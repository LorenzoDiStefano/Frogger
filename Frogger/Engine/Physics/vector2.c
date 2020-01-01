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

vector2_t vector2_mul_vec2(const vector2_t *first_value, const vector2_t *second_value)
{
    vector2_t result;

    result.x = first_value->x * second_value->x;
    result.y = first_value->y * second_value->y;

    return result;    
}

vector2_t vector2_get_deep_copy(const vector2_t *vector2)
{
    vector2_t result;

    result.x = vector2->x;
    result.y = vector2->y;

    return result;
}

int vector2_equals(const vector2_t *first_value, const vector2_t *second_value)
{
    return first_value->x == second_value->x && first_value->y == second_value->y;
}