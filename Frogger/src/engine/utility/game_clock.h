#ifndef FROGGER_GAME_CLOCK_HEADER
#define FROGGER_GAME_CLOCK_HEADER

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#include <SDL.h>
#endif

typedef struct game_clock
{
    double delta_time_cached;
    Uint64 now;
    Uint64 last;

    void (*cache_now)(struct game_clock *clock); 
    double (*get_delta_time)(struct game_clock *clock); 

}game_clock_t;

void clock_init_safe(game_clock_t *clock);

#endif