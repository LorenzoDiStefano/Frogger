#ifndef FROGGER_DRAW_MANAGER_HEADER
#define FROGGER_DRAW_MANAGER_HEADER

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "sprite.h"

typedef struct draw_manager
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    sprite_t *sprites[100];
    int max_sprites, sprites_to_draw;

    sprite_t *bg_sprites[100];
    int bg_sprites_to_draw;
    int bg_max_sprites;

} draw_manager_t;

#define WINDOW_WIDTH 858
#define WINDOW_HEIGHT 858
#define TILE_SIZE 78

int draw_manager_init(draw_manager_t* draw_manager);
void draw_manager_add_sprite(draw_manager_t *draw_manager, sprite_t *sprite);
void draw_manager_add_sprite_bg(draw_manager_t *draw_manager, sprite_t *sprite);
void draw_scene(draw_manager_t *draw_manager);

#ifdef _TEST
void test_wrapper(const char *name, int (*func)(void));
#define RUN_TEST_DRAW_MANAGER(func) test_wrapper(#func, func);

void test_draw_manager();

#endif
#endif