#include "../../pch.h"

TEST(vector2_tests, init)
{
    int return_value;
	vector2_t vector2;
	return_value = vector2_init(&vector2);
	EXPECT_EQ(vector2.x, 0);
    EXPECT_EQ(vector2.y, 0);
    EXPECT_EQ(return_value, 0);
}

TEST(vector2_tests, init_null)
{
    int return_value;
	return_value = vector2_init(NULL);
    EXPECT_EQ(return_value, 1);
}

TEST(vector2_tests, set)
{
    vector2_t vector2;
    int ret_val = vector2_set(&vector2, 50, 70);
    EXPECT_TRUE(vector2.x == 50 && vector2.y == 70 && ret_val == 0);
}

TEST(vector2_tests, add)
{
    vector2_t second_vector2, vector2;
    vector2_set(&vector2, 50, 70);
    vector2_set(&second_vector2, 50, 70);
    second_vector2 = vector2_add(&vector2, &second_vector2);
    EXPECT_TRUE(second_vector2.x == 100 && second_vector2.y == 140);
}

TEST(vector2_tests, sub)
{
    vector2_t second_vector2, vector2;
    vector2_set(&vector2, 50, 70);
    vector2_set(&second_vector2, 50, 70);
    second_vector2 = vector2_sub(&vector2, &second_vector2);
    EXPECT_TRUE(second_vector2.x == 0 && second_vector2.y == 0);
}

TEST(vector2_tests, mul)
{
    vector2_t second_vector2, vector2;
    vector2_set(&vector2, 10, 2);
    second_vector2 = vector2_mul(&vector2, 4);
    EXPECT_TRUE(second_vector2.x == 40 && second_vector2.y == 8);
}

TEST(vector2_tests, mul_vec2)
{
    vector2_t second_vector2, vector2;
    vector2_set(&vector2, 10, 2);
    vector2_set(&second_vector2, 2, 4);
    second_vector2 = vector2_mul_vec2(&vector2, &second_vector2);
    EXPECT_TRUE(second_vector2.x == 20 && second_vector2.y == 8);
}

TEST(vector2_tests, equal)
{
    vector2_t second_vector2, vector2;

    vector2_set(&second_vector2, 5, 10);
    vector2_set(&vector2, 5, 10);

    EXPECT_TRUE(vector2_equals(&second_vector2, &vector2));
}

TEST(vector2_tests, not_equal)
{
    vector2_t second_vector2, vector2;

    vector2_set(&second_vector2, 5, 10);
    vector2_set(&vector2, 10, 10);

    EXPECT_TRUE(!vector2_equals(&second_vector2, &vector2));
}

TEST(vector2_tests, length_negative)
{
    vector2_t point;
    double return_value;

    vector2_set(&point, -2, 0);

    return_value = vector2_length(&point);

    EXPECT_TRUE(return_value == 2);
}

TEST(vector2_tests, length)
{
    vector2_t point;
    double return_value;

    vector2_set(&point, 0, 2);

    return_value = vector2_length(&point);

    EXPECT_TRUE(return_value == 2);
}