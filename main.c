#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


static int game_state = 1;
#include "engine/clock.c"
#include "engine/engine.c"

#ifdef _TEST

#include "tests/tests.c"

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

    physics_manager_t physics_manager;
    physics_manager_init(&physics_manager);

    car_t log;
    car_init(&log,&draw_manager,&physics_manager,"assets/ph_log.png");
    game_object_set_position(&log.game_object, 0, 78*5);
    log.game_object.collider_type = COLLIDER_TYPE_LOG;

    backgound_t road;
    backgound_init(&road, &draw_manager, &physics_manager, "assets/ph_road_bg.png");
    game_object_set_position(&road.game_object, 0, 78);

    backgound_t road2;
    backgound_init(&road2, &draw_manager, &physics_manager, "assets/ph_road_bg.png");
    game_object_set_position(&road2.game_object, 0, 78*2);

    backgound_t end_bg;
    backgound_init(&end_bg, &draw_manager, &physics_manager, "assets/ph_victory_bg.png");
    game_object_set_position(&end_bg.game_object, 0, 0);
    end_bg.game_object.collider_type = COLLIDER_TYPE_END;

    backgound_t water_bg;
    backgound_init(&water_bg, &draw_manager, &physics_manager, "assets/ph_water_bg.png");
    game_object_set_position(&water_bg.game_object, 0, 78*5);
    water_bg.game_object.collider_type = COLLIDER_TYPE_WATER;

    player_t player;
    player_init(&player,&draw_manager,&physics_manager);
    /*
    wall_t wall;
    wall_init(&wall,&draw_manager,&physics_manager);
    wall_t wall2;
    wall_init(&wall2,&draw_manager,&physics_manager);
    wall2.game_object.position.x=300;
    wall2.game_object.position.y=0;
    */

    car_t car;
    car_init(&car,&draw_manager,&physics_manager,"assets/ph_car.png");

    car_t car2;
    car_init(&car2,&draw_manager,&physics_manager,"assets/ph_car.png");
    //car2.game_object
    game_object_set_position(&car2.game_object, 200, 200);

    while(game_state)
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
        physics_manager_update(&physics_manager, frame_time*0.001);
        physics_manager_check_collisions(&physics_manager);
        draw_manager.draw_scene(&draw_manager);
    }

    return 1;
}

int main (int argc, char **argv)
{
    #ifdef _TEST

    printf("Executing tests\n");
    return run_tests();

    #endif
    
    return game();
}


