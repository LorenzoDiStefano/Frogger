#include <engine/gfx/draw_manager.h>
#include <engine/gfx/sprite.h>
#include <engine/gfx/interface_gpu_api.h>

void draw_scene(draw_manager_t *draw_manager)
{
    SDL_SetRenderDrawColor(draw_manager->renderer, 67, 33, 33, 255);
    SDL_RenderClear(draw_manager->renderer);

    for (int i = 0; i < draw_manager->bg_sprites_to_draw; i++)
    {
        sprite_t *sprite_address = draw_manager->bg_sprites[i];
        SDL_RenderCopy(draw_manager->renderer, sprite_address->texture, NULL, &sprite_address->sprite_rect);
    }

    for (int i = 0; i < draw_manager->sprites_to_draw; i++)
    {
        sprite_t *sprite_address = draw_manager->sprites[i];
        SDL_RenderCopy(draw_manager->renderer, sprite_address->texture, NULL, &sprite_address->sprite_rect);
    }

    SDL_RenderPresent(draw_manager->renderer);
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

    init_interface_gpu_api(&draw_manager->gpu);

    draw_manager->iwindow = draw_manager->gpu.create_window("Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    void* window_raw_data = draw_manager->iwindow->raw_data;

    if(!window_raw_data)
    {
        return -1;
    }

    draw_manager->renderer = SDL_CreateRenderer(window_raw_data, -1,SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);

    if(!draw_manager->renderer)
    {
        return -1;
    }

    SDL_SetRenderDrawBlendMode(draw_manager->renderer, SDL_BLENDMODE_BLEND);

    draw_manager->sprites_to_draw = 0;
    draw_manager->max_sprites = 100;

    draw_manager->bg_sprites_to_draw = 0;
    draw_manager->bg_max_sprites = 0;

    return 0;
}