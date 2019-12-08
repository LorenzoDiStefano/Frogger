#define SDL_MAIN_HANDLED
#include <SDL.h>

typedef struct game_clock
{
    double delta_time_cached;
    Uint64 now;
    Uint64 last;

    void (*cache_now)(struct game_clock *clock); 
    double (*get_delta_time)(struct game_clock *clock); 

}game_clock_t;

void clock_init_safe(game_clock_t *clock);

#ifdef _TEST
void test_wrapper(const char *name, int (*func)());
#define RUN_TEST_CLOCK(func) test_wrapper(#func, func);

void test_clock();

#endif