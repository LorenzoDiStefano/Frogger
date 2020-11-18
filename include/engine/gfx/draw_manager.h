#ifndef FROGGER_DRAWMANAGER
#define FROGGER_DRAWMANAGER
#pragma once

typedef struct sprite sprite_t;
struct interface_renderer typedef interface_renderer_t;
struct interface_window typedef interface_window_t;

typedef struct draw_manager
{
    interface_window_t* window;
    interface_renderer_t* renderer;

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

#endif // !FROGGER_DRAWMANAGER