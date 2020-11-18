#include <engine/gfx/draw_manager.h>
#include <engine/gfx/interface_window.h>
#include <engine/gfx/interface_renderer.h>
#include <engine/gfx/sprite.h>
#include <SDL.h>

void draw_scene(draw_manager_t *draw_manager)
{
    interface_renderer_t* renderer = draw_manager->renderer;

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
    //creating window
    draw_manager->window = create_interface_window("Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    //if this pointer is null something went relly wrong
    if(!draw_manager->window->raw_data)
    {
        return -1;
    }

    //creating renderer
    draw_manager->renderer = create_interface_renderer(draw_manager->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    //if this pointer is null something went relly wrong
    if(!draw_manager->renderer->raw_data)
    {
        return -1;
    }

    draw_manager->renderer->set_draw_blend_mode(draw_manager->renderer, SDL_BLENDMODE_BLEND);

    //initializing "layers" data
    draw_manager->sprites_to_draw = 0;
    draw_manager->max_sprites = 100;

    draw_manager->bg_sprites_to_draw = 0;
    draw_manager->bg_max_sprites = 0;

    return 0;
}