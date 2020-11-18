#ifndef FROGGER_GAMECLOCK
#define FROGGER_GAMECLOCK
#pragma once 

#include <stdint.h>

typedef struct game_clock
{
    double delta_time_cached;
    uint64_t now;
    uint64_t last;

    void (*cache_now)(struct game_clock *clock); 
    double (*get_delta_time)(struct game_clock *clock); 

}game_clock_t;

void clock_init_safe(game_clock_t *clock);

#endif // !FROGGER_GAMECLOCK