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

#define TEXTURE_FROG    0
#define TEXTURE_ROAD    1
#define TEXTURE_WATER   2
#define TEXTURE_WIN     3
#define TEXTURE_CAR     4
#define TEXTURE_LOG     5

void load_textures(image_info_t texture[], SDL_Renderer *renderer)
{

    image_info_t frog_texture_inf;
    load_image(&frog_texture_inf,"assets/frog.png");
    load_texture(&frog_texture_inf,renderer);
    texture[TEXTURE_FROG] = frog_texture_inf;

    image_info_t road_texture_inf;
    load_image(&road_texture_inf,"assets/ph_road_bg.png");
    load_texture(&road_texture_inf,renderer);
    texture[TEXTURE_ROAD] = road_texture_inf;

    image_info_t water_texture_inf;
    load_image(&water_texture_inf,"assets/ph_water_bg.png");
    load_texture(&water_texture_inf,renderer);
    texture[TEXTURE_WATER] = water_texture_inf;

    image_info_t win_texture_inf;
    load_image(&win_texture_inf,"assets/ph_victory_bg.png");
    load_texture(&win_texture_inf,renderer);
    texture[TEXTURE_WIN] = win_texture_inf;

    image_info_t car_texture_inf;
    load_image(&car_texture_inf,"assets/ph_car.png");
    load_texture(&car_texture_inf,renderer);
    texture[TEXTURE_CAR] = car_texture_inf;

    image_info_t log_texture_inf;
    load_image(&log_texture_inf,"assets/ph_log.png");
    load_texture(&log_texture_inf,renderer);
    texture[TEXTURE_LOG] = log_texture_inf;
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

    image_info_t textures_info[10];

    load_textures(textures_info,draw_manager.renderer);

    car_t log;
    car_init(&log,&draw_manager, &physics_manager, &textures_info[TEXTURE_LOG]);
    game_object_set_position(&log.game_object, 0, 78*5);
    game_object_set_velocity_x(&log.game_object, -90);
    log.game_object.collider_type = COLLIDER_TYPE_LOG;

    car_t car;
    car_init(&car,&draw_manager, &physics_manager, &textures_info[TEXTURE_CAR]);
    game_object_set_position(&car.game_object, 78, 78);
    game_object_set_velocity_x(&car.game_object, 90);

    car_t car2;
    car_init(&car2,&draw_manager, &physics_manager, &textures_info[TEXTURE_CAR]);
    game_object_set_position(&car2.game_object, 200, 200);
    game_object_set_velocity_x(&car2.game_object, -120);

    car_t car3;
    car_init(&car3,&draw_manager, &physics_manager, &textures_info[TEXTURE_CAR]);
    game_object_set_position(&car3.game_object, 360, 230);
    game_object_set_velocity_x(&car3.game_object, -90);

    car_t car4;
    car_init(&car4,&draw_manager, &physics_manager, &textures_info[TEXTURE_CAR]);
    game_object_set_velocity_x(&car4.game_object, 110);
    game_object_set_position(&car4.game_object, 460, 360);

    car_t car5;
    car_init(&car5,&draw_manager, &physics_manager, &textures_info[TEXTURE_CAR]);
    game_object_set_position(&car5.game_object, 560, 100);
    game_object_set_velocity_x(&car5.game_object, 100);

    backgound_t road;
    backgound_init(&road, &draw_manager, &physics_manager, &textures_info[TEXTURE_ROAD]);
    game_object_set_position(&road.game_object, 0, 78);

    backgound_t road2;
    backgound_init(&road2, &draw_manager, &physics_manager, &textures_info[TEXTURE_ROAD]);
    game_object_set_position(&road2.game_object, 0, 78*2);

    backgound_t end_bg;
    backgound_init(&end_bg, &draw_manager, &physics_manager, &textures_info[TEXTURE_WIN]);
    game_object_set_position(&end_bg.game_object, 0, 0);
    end_bg.game_object.collider_type = COLLIDER_TYPE_END;

    backgound_t water_bg;
    backgound_init(&water_bg, &draw_manager, &physics_manager, &textures_info[TEXTURE_WATER]);
    game_object_set_position(&water_bg.game_object, 0, 78*5);
    water_bg.game_object.collider_type = COLLIDER_TYPE_WATER;

    player_t player;
    player_init(&player,&draw_manager,&physics_manager,&textures_info[TEXTURE_FROG]);
    
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


