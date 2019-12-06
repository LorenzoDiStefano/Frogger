#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "engine/clock.c"
#include "engine/engine.c"

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

    physics_manager_t physics_manager;
    physics_manager_init(&physics_manager);

    player_t player;
    player_init(&player,&draw_manager,&physics_manager);
    wall_t wall;
    wall_init(&wall,&draw_manager,&physics_manager);
    wall_t wall2;
    wall_init(&wall2,&draw_manager,&physics_manager);
    wall2.game_object.position.x=300;
    wall2.game_object.position.y=0;


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
            //printf("rendering new frame\n");
            //printf("fps time: %f\n",frame_time);
        }
        else
        {
            continue;
        }

        player_read_input(&player);
        //game_object_update(&player.game_object,frame_time*0.001);
        //game_object_update(&wall.game_object,frame_time*0.001);
        //game_object_update(&wall2.game_object,frame_time*0.001);
        physics_manager_update(&physics_manager, frame_time*0.001);
        physics_manager_check_collisions(&physics_manager);
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


