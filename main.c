#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/clock.c"
#include "engine/draw_manager.h"
#include "engine/draw_manager.c"
#include "engine/vector2.h"
#include "engine/vector2.c"
#include "engine/game_object.h"
#include "engine/game_object.c"
#include "engine/rect.h"
#include "engine/rect.c"
#include "engine/collision_info.h"
#include "engine/collision_info.c"

#ifdef _TEST

#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/test_vector2.c"
#include "tests/test_game_object.c"
#include "tests/test_rect.c"
#include "tests/test_collision_info.c"

#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#endif

int crash()
{
    SDL_Log("window error %s",SDL_GetError());
    SDL_Quit();
    getchar();
    return 1;
}

int end()
{
    SDL_Quit();
    return 0;
}

int game()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO))
    {
        SDL_Log("error %s",SDL_GetError());
        return 1;
    }

    draw_manager_t draw_manager;
    draw_manager_init(&draw_manager);

    clock_t game_clock;
    clock_init_safe(&game_clock);

    int fps = 60;
    double frame_time = (double)1000/fps;
    double accumulator = 0;

    for(;;)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return end();
            }
        }

        game_clock.cache_now(&game_clock);
        accumulator+=game_clock.get_delta_time(&game_clock);
        
        if(accumulator>=frame_time)
        {
            accumulator-=frame_time;
            printf("rendering new frame\n");
            printf("fps time: %f\n",frame_time);
        }
        else
        {
            continue;
        }

        draw_manager.draw_scene(&draw_manager);
    }
}

int main (int argc, char **argv)
{

    #ifdef _TEST

    printf("Executing tests\n");
    return run_tests();

    #endif
    
    return game();
}


