#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

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
#define TEXTURE_SPAWN   6
#define TEXTURE_CAR_FLIP     7
#define TEXTURE_MAX     8

void load_textures(image_info_t texture[], SDL_Renderer *renderer)
{
    /*
    char *paths[10];
    paths[0] = "assets/frog.png";
    paths[1] = "assets/ph_road_bg.png";

    for (size_t i = 0; i < 2; i++)
    {
        image_info_t texture_inf;
        load_image(&texture_inf, (const char)paths[i]);
        load_texture(&texture_inf, renderer);
        texture[i] = texture_inf;
    }
    */

    image_info_t frog_texture_inf;
    load_image(&frog_texture_inf, "assets/frog.png");
    load_texture(&frog_texture_inf, renderer);
    texture[TEXTURE_FROG] = frog_texture_inf;

    image_info_t road_texture_inf;
    load_image(&road_texture_inf, "assets/ph_road_bg.png");
    load_texture(&road_texture_inf, renderer);
    texture[TEXTURE_ROAD] = road_texture_inf;

    image_info_t water_texture_inf;
    load_image(&water_texture_inf, "assets/ph_water_bg.png");
    load_texture(&water_texture_inf, renderer);
    texture[TEXTURE_WATER] = water_texture_inf;

    image_info_t win_texture_inf;
    load_image(&win_texture_inf, "assets/ph_victory_bg.png");
    load_texture(&win_texture_inf, renderer);
    texture[TEXTURE_WIN] = win_texture_inf;

    image_info_t car_texture_inf;
    load_image(&car_texture_inf, "assets/car.png");
    load_texture(&car_texture_inf, renderer);
    texture[TEXTURE_CAR] = car_texture_inf;

    image_info_t flip_car_texture_inf;
    load_image(&flip_car_texture_inf, "assets/car_flip.png");
    load_texture(&flip_car_texture_inf, renderer);
    texture[TEXTURE_CAR_FLIP] = flip_car_texture_inf;

    image_info_t log_texture_inf;
    load_image(&log_texture_inf, "assets/log.png");
    load_texture(&log_texture_inf, renderer);
    texture[TEXTURE_LOG] = log_texture_inf;

    image_info_t spawn_texture_inf;
    load_image(&spawn_texture_inf, "assets/ph_spawn_bg.png");
    load_texture(&spawn_texture_inf, renderer);
    texture[TEXTURE_SPAWN] = spawn_texture_inf;
}

void generate_map(backgound_t *backgrounds, draw_manager_t *draw_manager,physics_manager_t *physics_manager, image_info_t *texture_info, car_t *obstacles)
{
    int used_obstacles = 0;
    int base_x_velocity = 100;
    int lane_direction;

    for (size_t i = 0; i < 10; i++)
    {
        if(i == 0)
        {
            backgound_init(&backgrounds[i], draw_manager, physics_manager, &texture_info[TEXTURE_WIN]);
            backgrounds[i].game_object.collider_type = COLLIDER_TYPE_END;
        }
        else if(i == 9)
        {
            backgound_init(&backgrounds[i], draw_manager, physics_manager, &texture_info[TEXTURE_SPAWN]);
        }
        else
        {
            int random_bg = (rand() % 2);
            lane_direction = (rand() % 2) * 2 - 1;
            float random_additive_velocity = ((float)rand() / (float)(RAND_MAX)) * base_x_velocity;
            float lane_velocity = (random_additive_velocity + base_x_velocity) * lane_direction;
            if(random_bg)
            {
                backgound_init(&backgrounds[i],draw_manager,physics_manager, &texture_info[TEXTURE_WATER]);
                backgrounds[i].game_object.collider_type = COLLIDER_TYPE_WATER;

                game_object_set_position(&obstacles[used_obstacles].game_object, (rand() % 3) * TILE_SIZE, TILE_SIZE * i);
                game_object_set_velocity_x(&obstacles[used_obstacles].game_object, lane_velocity);
                obstacles[used_obstacles].game_object.collider_type = COLLIDER_TYPE_LOG;
                obstacles[used_obstacles].game_object.sprite->texture = texture_info[TEXTURE_LOG].texture;

                obstacles[used_obstacles].game_object.sprite->sprite_rect.h = texture_info[TEXTURE_LOG].height;
                obstacles[used_obstacles].game_object.sprite->sprite_rect.w = texture_info[TEXTURE_LOG].width;

                rect_set_size(&obstacles[used_obstacles].game_object.bounding_box, 
                obstacles[used_obstacles].game_object.sprite->sprite_rect.w, obstacles[used_obstacles].game_object.sprite->sprite_rect.h);

                used_obstacles++;

                if((rand()%2))
                {
                    game_object_set_position(&obstacles[used_obstacles].game_object, ((rand()%5)+5)*TILE_SIZE, TILE_SIZE*i);
                    game_object_set_velocity_x(&obstacles[used_obstacles].game_object, lane_velocity);
                    obstacles[used_obstacles].game_object.collider_type = COLLIDER_TYPE_LOG;
                    obstacles[used_obstacles].game_object.sprite->texture = texture_info[TEXTURE_LOG].texture;
                    
                    obstacles[used_obstacles].game_object.sprite->sprite_rect.h = texture_info[TEXTURE_LOG].height;
                    obstacles[used_obstacles].game_object.sprite->sprite_rect.w = texture_info[TEXTURE_LOG].width;

                    rect_set_size(&obstacles[used_obstacles].game_object.bounding_box, 
                    obstacles[used_obstacles].game_object.sprite->sprite_rect.w, obstacles[used_obstacles].game_object.sprite->sprite_rect.h);

                    used_obstacles++;
                }
            }
            else
            {
                backgound_init(&backgrounds[i], draw_manager,physics_manager, &texture_info[TEXTURE_ROAD]);
                
                game_object_set_position(&obstacles[used_obstacles].game_object, (rand()%3)*TILE_SIZE , TILE_SIZE*i);
                game_object_set_velocity_x(&obstacles[used_obstacles].game_object, lane_velocity);

                if(lane_direction > 0)
                    obstacles[used_obstacles].game_object.sprite->texture = texture_info[TEXTURE_CAR_FLIP].texture;

                used_obstacles++;
                if(rand() % 2)
                {
                    game_object_set_position(&obstacles[used_obstacles].game_object, ((rand()%5)+5) * TILE_SIZE , TILE_SIZE*i);
                    game_object_set_velocity_x(&obstacles[used_obstacles].game_object, lane_velocity);

                    if(lane_direction > 0)
                        obstacles[used_obstacles].game_object.sprite->texture = texture_info[TEXTURE_CAR_FLIP].texture;
                    used_obstacles++;
                }
            }
            
        }            

        game_object_set_position(&backgrounds[i].game_object, 0, TILE_SIZE * i);
    }
}

int game()
{
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO))
    {
        SDL_Log("error %s",SDL_GetError());
        return 1;
    }

    int fps = 60;
    double frame_time = (double)1000 / fps;
    double accumulator = 0;
    srand(time(NULL));

    game_clock_t game_clock;
    clock_init_safe(&game_clock);

    draw_manager_t draw_manager;
    draw_manager_init(&draw_manager);

    physics_manager_t physics_manager;
    physics_manager_init(&physics_manager);

    image_info_t textures_info[TEXTURE_MAX];
    load_textures(textures_info, draw_manager.renderer);

    car_t obstacles[20];

    for (size_t i = 0; i < 20; i++)
    {
        car_init(&obstacles[i], &draw_manager, &physics_manager, &textures_info[TEXTURE_CAR]);
    }

    backgound_t backrounds[10];
    generate_map(backrounds,&draw_manager,&physics_manager,textures_info, obstacles);

    player_t player;
    player_init(&player,&draw_manager, &physics_manager, &textures_info[TEXTURE_FROG]);
    
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
        accumulator += game_clock.get_delta_time(&game_clock);
        
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
        physics_manager_update(&physics_manager, frame_time / 1000);
        physics_manager_check_collisions(&physics_manager);
        //getchar();
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


