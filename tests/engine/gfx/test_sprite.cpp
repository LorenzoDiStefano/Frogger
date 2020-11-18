#include "../../pch.h"

//TEST(sprite_test, init)
//{
//    draw_manager_t draw_manager;
//    sprite_t sprite;
//    texture_manager_t tm;
//    int texture_index;
//
//    draw_manager_init(&draw_manager);
//    texture_manager_init(&tm);
//
//    texture_manager_set_renderer(&tm, draw_manager.renderer);
//    texture_index = texture_manager_load_texture(&tm, "../assets/ph_spawn_bg.png");
//
//    sprite_init(&sprite, &tm.textures[texture_index], draw_manager.renderer, 1);
//
//    EXPECT_TRUE(sprite.renderer == draw_manager.renderer);
//    EXPECT_TRUE(sprite.scale == 1);
//    EXPECT_TRUE(sprite.sprite_rect.w == tm.textures[texture_index].width);
//    EXPECT_TRUE(sprite.sprite_rect.h == tm.textures[texture_index].height);
//    EXPECT_TRUE(sprite.sprite_rect.x == 0);
//    EXPECT_TRUE(sprite.sprite_rect.y == 0);
//    EXPECT_TRUE(sprite.texture == tm.textures[texture_index].texture);
//}