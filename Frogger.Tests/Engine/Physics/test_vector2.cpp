#include "pch.h"
#include "Physics/vector2.h"
TEST(vector2_tests, vector2_init)
{
    int return_value;
	vector2_t vector2;
	return_value = vector2_init(&vector2);
	EXPECT_EQ(vector2.x, 0);
    EXPECT_EQ(vector2.y, 0);
    EXPECT_EQ(return_value, 0);
}

TEST(vector2_tests, vector2_init_null)
{
    int return_value;
	return_value = vector2_init(NULL);
    EXPECT_EQ(return_value, 1);
}

TEST(vector2_tests, vector2_init_safe)
{
    vector2_t vector2;
    int ret_val = vector2_init_safe(&vector2, 50, 70);
    EXPECT_TRUE(vector2.x == 50 && vector2.y == 70 && ret_val == 0);
}

TEST(vector2_tests, vector2_add)
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_init_safe(&second_vector2, 50, 70);
    second_vector2 = vector2_add(&vector2, &second_vector2);
    EXPECT_TRUE(second_vector2.x == 100 && second_vector2.y == 140);
}

TEST(vector2_tests, vector2_sub)
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_init_safe(&second_vector2, 50, 70);
    second_vector2 = vector2_sub(&vector2, &second_vector2);
    EXPECT_TRUE(second_vector2.x == 0 && second_vector2.y == 0);
}

TEST(vector2_tests, vector2_get_deep_copy)
{

    vector2_t vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_t second_vector2 = vector2_get_deep_copy(&vector2);
    EXPECT_TRUE(second_vector2.x == 50 && second_vector2.y == 70 &&
        &(second_vector2.y) != &(vector2.y) && &(second_vector2.x) != &(vector2.x));
}

TEST(vector2_tests, vector2_mul)
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 10, 2);
    second_vector2 = vector2_mul(&vector2, 4);
    EXPECT_TRUE(second_vector2.x == 40 && second_vector2.y == 8);
}

TEST(vector2_tests, vector2_mul_vec2)
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 10, 2);
    vector2_init_safe(&second_vector2, 2, 4);
    second_vector2 = vector2_mul_vec2(&vector2, &second_vector2);
    EXPECT_TRUE(second_vector2.x == 20 && second_vector2.y == 8);
}

TEST(vector2_tests, vector2_equals)
{
    vector2_t second_vector2, vector2;

    vector2_init_safe(&second_vector2, 5, 10);
    vector2_init_safe(&vector2, 5, 10);

    EXPECT_TRUE(vector2_equals(&second_vector2, &vector2));
}

TEST(vector2_tests, vector2_not_equals)
{
    vector2_t second_vector2, vector2;

    vector2_init_safe(&second_vector2, 5, 10);
    vector2_init_safe(&vector2, 10, 10);

    EXPECT_TRUE(!vector2_equals(&second_vector2, &vector2));
}