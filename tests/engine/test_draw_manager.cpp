#include "../pch.h"

TEST(draw_manager_tests, init)
{
    draw_manager_t draw_manager;
    int return_value = draw_manager_init(&draw_manager);

    EXPECT_TRUE
    (
        !return_value &&
        draw_manager.max_sprites == 100 &&
        draw_manager.sprites_to_draw == 0
    );
}