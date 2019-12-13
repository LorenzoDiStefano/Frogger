#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "clock.h"
#include <stdint.h>

void cache_now(game_clock_t *clock)
{
    clock->last = clock->now;
    clock->now = SDL_GetPerformanceCounter();
}

void fake_cache_now(game_clock_t *clock, Uint64 value)
{
    clock->last = clock->now;
    clock->now = value;
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

#ifdef _TEST

static int test_cache_now()
{
    game_clock_t clock;
    clock_init_safe(&clock);
    clock.last = 0;
    clock.now = 5;
    fake_cache_now(&clock, 55);
    return clock.last == 5 && clock.now == 55;
}

static int test_get_delta_time()
{
    game_clock_t clock;
    clock_init_safe(&clock);
    clock.last = 0;
    clock.now = 5;
    clock.get_delta_time(&clock);
    return clock.delta_time_cached<=0.0005100 && clock.delta_time_cached>=0.0004999;
}

void test_clock()
{
    RUN_TEST_CLOCK(test_cache_now);
    RUN_TEST_CLOCK(test_get_delta_time);
}
#endif