#define SDL_MAIN_HANDLED
#include <SDL.h>

typedef struct clock
{
    double delta_time_cached;
    Uint64 now;
    Uint64 last;

    void (*cache_now)(struct clock *clock); 
    double (*get_delta_time)(struct clock *clock); 

}clock_t;

void clock_init_safe(clock_t *clock);

#ifdef _TEST
void clock_test_wrapper(const char *name, int (*func)(clock_t *clock));
#define RUN_TEST_CLOCK(func) clock_test_wrapper(#func, func);

void test_clock();

#endif