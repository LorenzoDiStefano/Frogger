#include <math/vector2.h>
#include <stdio.h>
#include <math.h>

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

int vector2_set(vector2_t *vector2, float x, float y)
{
    if(vector2 == NULL)
    {
        printf("function: %s\n null argument vector2",__func__);
        exit(1);
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

int vector2_equals(const vector2_t *first_value, const vector2_t *second_value)
{
    return first_value->x == second_value->x && first_value->y == second_value->y;
}

double vector2_length(vector2_t* p)
{
    return sqrt(p->x * p->x + p->y * p->y);
}

void vector2_normalize(vector2_t* p)
{
    double w = vector2_length(p);
    p->x /= w;
    p->y /= w;
}