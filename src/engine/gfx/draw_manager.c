#include <engine/gfx/draw_manager.h>
#include <engine/gfx/sprite.h>
#include <engine/gfx/interface_gpu_api.h>
#include <SDL.h>

void draw_scene(draw_manager_t *draw_manager)
{
    interface_renderer_t* renderer = draw_manager->irenderer;

    renderer->set_draw_color(renderer, 67, 33, 33, 255);
    renderer->clear(renderer);

    for (int i = 0; i < draw_manager->bg_sprites_to_draw; i++)
    {
        sprite_t *sprite_address = draw_manager->bg_sprites[i];
        renderer->copy(renderer, sprite_address->texture, &sprite_address->sprite_rect);
    }

    for (int i = 0; i < draw_manager->sprites_to_draw; i++)
    {
        sprite_t *sprite_address = draw_manager->sprites[i];
        renderer->copy(renderer, sprite_address->texture, &sprite_address->sprite_rect);
    }

    renderer->present(renderer);
}

void draw_manager_add_sprite(draw_manager_t *draw_manager, sprite_t *sprite)
{
    draw_manager->sprites[draw_manager->sprites_to_draw] = sprite;
    draw_manager->sprites_to_draw++;
}

void draw_manager_add_sprite_bg(draw_manager_t *draw_manager, sprite_t *sprite)
{
    draw_manager->bg_sprites[draw_manager->bg_sprites_to_draw] = sprite;
    draw_manager->bg_sprites_to_draw++;
}

int draw_manager_init(draw_manager_t* draw_manager)
{
    //initializing graphics api used
    init_interface_gpu_api(&draw_manager->gpu);

    //creating window
    draw_manager->iwindow = draw_manager->gpu.create_window("Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    //if this pointer is null something went relly wrong
    if(!draw_manager->iwindow->raw_data)
    {
        return -1;
    }

    //creating renderer
    draw_manager->irenderer = draw_manager->gpu.create_renderer(draw_manager->iwindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    //if this pointer is null something went relly wrong
    if(!draw_manager->irenderer->raw_data)
    {
        return -1;
    }

    draw_manager->irenderer->set_draw_blend_mode(draw_manager->irenderer, SDL_BLENDMODE_BLEND);

    //initializing "layers" data
    draw_manager->sprites_to_draw = 0;
    draw_manager->max_sprites = 100;

    draw_manager->bg_sprites_to_draw = 0;
    draw_manager->bg_max_sprites = 0;

    return 0;
}