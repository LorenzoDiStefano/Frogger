#define SDL_MAIN_HANDLED
#include <SDL.h>


#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

static uint64_t tests_succeded = 0;
static uint64_t tests_failed = 0;

void test_init()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO))
    {
        SDL_Log("error %s",SDL_GetError());
    }
}

void test_wrapper(const char *name, int (*func)())
{

    if (!func())
    {
        //printf("executing: %s Result: ",name);
        //printf("FAILED\n");
        fprintf(stderr, "TEST %s FAILED\n", name);
        tests_failed++;
    }
    else
    {
        //printf("SUCCESSFUL\n");
        tests_succeded++;
    } 
}


int run_tests()
{
    test_init();
    test_clock();
    test_vector2();
    test_game_object();
    test_rect();
    test_collision_info();
    test_draw_manager();
    fprintf(stdout, "Tests succeded: %llu failed: %llu\n", tests_succeded, tests_failed);
    return 0;
}