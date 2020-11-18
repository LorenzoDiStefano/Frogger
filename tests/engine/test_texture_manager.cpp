#include "../pch.h"

//TEST(texture_manager_tests, init)
//{
//    texture_manager_t tm;
//    texture_manager_init(&tm);
//
//    EXPECT_TRUE
//    (
//        tm.stored_texture == 0 &&
//        tm.renderer == NULL
//    );
//}

//TEST(texture_manager_tests, set_renderer)
//{
//    texture_manager_t tm;
//    SDL_Renderer* renderer;
//    SDL_Window* window;
//
//    texture_manager_init(&tm);
//    window = SDL_CreateWindow("Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
//
//    texture_manager_set_renderer(&tm, renderer);
//
//    EXPECT_TRUE
//    (
//        tm.stored_texture == 0 &&
//        tm.renderer == renderer
//    );
//}

//TEST(texture_manager_tests, load_texture)
//{
//    texture_manager_t tm;
//    SDL_Renderer* renderer;
//    SDL_Window* window;
//    int return_val;
//
//    texture_manager_init(&tm);
//    window = SDL_CreateWindow("Game", 50, 50, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
//
//    texture_manager_set_renderer(&tm, renderer);
//    return_val = texture_manager_load_texture(&tm, "../assets/ph_spawn_bg.png");
//
//    EXPECT_TRUE
//    (
//        return_val == 0 &&
//        tm.stored_texture == 1 &&
//        tm.renderer == renderer
//    );
//}