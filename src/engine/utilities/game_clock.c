#include <SDL.h>
#include <engine/utilities/game_clock.h>

//this functions should not use sdl2 directly

void cache_now(game_clock_t *clock)
{
    clock->last = clock->now;
    clock->now = SDL_GetPerformanceCounter();
}

double get_delta_time(game_clock_t *clock)
{
    clock->delta_time_cached = (double)((clock->now - clock->last) * 1000 / (double)SDL_GetPerformanceFrequency());
    return clock->delta_time_cached;
}

void clock_init_safe(game_clock_t *clock)
{
    clock->cache_now = cache_now;
    clock->cache_now(clock);
    clock->delta_time_cached = 0;
    clock->get_delta_time = get_delta_time;
}
