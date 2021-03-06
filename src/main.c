#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#include <SDL.h>
#endif

static int game_state = 1;

#include <engine/utilities/game_clock.h>
#include <engine/gfx/sprite.h>
#include <frogger/player.h>
#include <frogger/obstacle.h>
#include <frogger/background.h>
#include <engine/gfx/draw_manager.h>
#include <engine/physics/physics_manager.h>
#include <engine/actors/update_manager.h>
#include <engine/utilities/texture_manager.h>
#include <engine/utilities/collision_info.h>
#include <engine/physics/rigid_body.h>

#define TEXTURE_FROG        0
#define TEXTURE_ROAD        1
#define TEXTURE_WATER       2
#define TEXTURE_WIN         3
#define TEXTURE_CAR         4
#define TEXTURE_LOG         5
#define TEXTURE_SPAWN       6
#define TEXTURE_CAR_FLIP    7
#define TEXTURE_MAX         8

void load_textures(texture_manager_t *tm)
{
    const char* paths[TEXTURE_MAX];
    paths[TEXTURE_FROG] = "assets/frog.png";
    paths[TEXTURE_ROAD] = "assets/ph_road_bg.png";
    paths[TEXTURE_WATER] = "assets/ph_water_bg.png";
    paths[TEXTURE_WIN] = "assets/ph_victory_bg.png";
    paths[TEXTURE_CAR] = "assets/car.png";
    paths[TEXTURE_CAR_FLIP] = "assets/car_flip.png";
    paths[TEXTURE_LOG] = "assets/log.png";
    paths[TEXTURE_SPAWN] = "assets/ph_spawn_bg.png";

    for (size_t i = 0; i < TEXTURE_MAX; i++)
    {
        texture_manager_load_texture(tm, paths[i]);
    }
}

void generate_map(background_t *backgrounds, draw_manager_t *draw_manager,physics_manager_t *physics_manager, image_info_t *texture_info, obstacle_t *obstacles)
{
    int used_obstacles = 0;
    int base_x_velocity = 100;
    int lane_direction;

    for (size_t i = 0; i < 10; i++)
    {
        if(i == 0)
        {
            background_init(&backgrounds[i], draw_manager, physics_manager, &texture_info[TEXTURE_WIN]);
            backgrounds[i].game_object.collider_type = COLLIDER_TYPE_END;
            rigid_body_set_owner(backgrounds[i].game_object.rigid_body, &backgrounds[i].game_object);
            physics_manager_add_rigid_body(physics_manager, backgrounds[i].game_object.rigid_body);
        }
        else if(i == 10)
        {
            background_init(&backgrounds[i], draw_manager, physics_manager, &texture_info[TEXTURE_SPAWN]);
        }
        else
        {
            int random_bg = (rand() % 2);
            lane_direction = (rand() % 2) * 2 - 1;
            float random_additive_velocity = ((float)rand() / (float)(RAND_MAX)) * base_x_velocity;
            float lane_velocity = (random_additive_velocity + base_x_velocity) * lane_direction;
            if(random_bg)
            {
                background_init(&backgrounds[i],draw_manager,physics_manager, &texture_info[TEXTURE_WATER]);
                backgrounds[i].game_object.collider_type = COLLIDER_TYPE_WATER;

                game_object_set_position(&obstacles[used_obstacles].game_object, (rand() % 3) * TILE_SIZE, TILE_SIZE * i);
                game_object_set_velocity_x(&obstacles[used_obstacles].game_object, lane_velocity);
                obstacles[used_obstacles].game_object.collider_type = COLLIDER_TYPE_LOG;
                obstacles[used_obstacles].game_object.sprite->texture = texture_info[TEXTURE_LOG].texture;

                obstacles[used_obstacles].game_object.sprite->sprite_rect.h = texture_info[TEXTURE_LOG].height;
                obstacles[used_obstacles].game_object.sprite->sprite_rect.w = texture_info[TEXTURE_LOG].width;

                rect_set_size(&obstacles[used_obstacles].game_object.rigid_body->bounding_box, 
                obstacles[used_obstacles].game_object.sprite->sprite_rect.w, obstacles[used_obstacles].game_object.sprite->sprite_rect.h);

                rigid_body_set_owner(backgrounds[i].game_object.rigid_body, &backgrounds[i].game_object);
                physics_manager_add_rigid_body(physics_manager, backgrounds[i].game_object.rigid_body);

                rigid_body_set_direction(obstacles[used_obstacles].game_object.rigid_body, lane_direction, 0);;
                used_obstacles++;

                if((rand()%2))
                {
                    game_object_set_position(&obstacles[used_obstacles].game_object, ((rand()%5)+5)*TILE_SIZE, TILE_SIZE*i);
                    game_object_set_velocity_x(&obstacles[used_obstacles].game_object, lane_velocity);
                    obstacles[used_obstacles].game_object.collider_type = COLLIDER_TYPE_LOG;
                    obstacles[used_obstacles].game_object.sprite->texture = texture_info[TEXTURE_LOG].texture;
                    
                    obstacles[used_obstacles].game_object.sprite->sprite_rect.h = texture_info[TEXTURE_LOG].height;
                    obstacles[used_obstacles].game_object.sprite->sprite_rect.w = texture_info[TEXTURE_LOG].width;

                    rect_set_size(&obstacles[used_obstacles].game_object.rigid_body->bounding_box, 
                    obstacles[used_obstacles].game_object.sprite->sprite_rect.w, obstacles[used_obstacles].game_object.sprite->sprite_rect.h);

                    rigid_body_set_direction(obstacles[used_obstacles].game_object.rigid_body, lane_direction, 0);;
                    used_obstacles++;
                }
            }
            else
            {
                background_init(&backgrounds[i], draw_manager,physics_manager, &texture_info[TEXTURE_ROAD]);
                
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
                    rigid_body_set_direction(obstacles[used_obstacles].game_object.rigid_body, lane_direction, 0);;
                    used_obstacles++;
                }
            }
            
        }            

        game_object_set_position(&backgrounds[i].game_object, 0, TILE_SIZE * i);
    }
}

int crash()
{
    SDL_Log("window error %s",SDL_GetError());
    SDL_Quit();
    return 1;
}

int end()
{
    SDL_Quit();
    return 0;
}

int game()
{
    
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("error %s", SDL_GetError());
        return 1;
    }

    int fps = 60;
    double frame_time = (double)1000 / fps;
    double accumulator = 0;
    srand(time(NULL));

    game_clock_t game_clock;
    clock_init_safe(&game_clock);

    update_manager_t update_manager;
    update_manager_init(&update_manager);

    draw_manager_t draw_manager;
    draw_manager_init(&draw_manager);

    physics_manager_t physics_manager;
    physics_manager_init(&physics_manager);

    texture_manager_t tm;
    texture_manager_init(&tm);
    texture_manager_set_renderer(&tm, draw_manager.renderer);
    load_textures(&tm);

    obstacle_t obstacles[20];

    for (size_t i = 0; i < 20; i++)
    {
        obstacle_init(&obstacles[i], &draw_manager, &physics_manager, &tm.textures[TEXTURE_CAR]);
        update_manager_add_game_object(&update_manager, &obstacles[i].game_object);
    }

    background_t backrounds[11];
    generate_map(backrounds, &draw_manager, &physics_manager, &tm.textures, obstacles);

    player_t player;
    player_init(&player,&draw_manager, &tm.textures[TEXTURE_FROG]);
    update_manager_add_game_object(&update_manager, &player.game_object);
    physics_manager_add_player(&physics_manager, player.game_object.rigid_body);

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
        
        if(accumulator >= frame_time)
        {
            accumulator -= frame_time;
            //printf("rendering new frame\n");
            //printf("fps time: %f\n",frame_time);
        }
        else
        {
            continue;
        }

        player_read_input(&player);
        update_manager_update(&update_manager, frame_time / 1000);
        physics_manager_update_rb(&physics_manager, frame_time / 1000);
        physics_manager_check_collisions(&physics_manager);
        draw_scene(&draw_manager);
    }

    return 1;
}

int main (int argc, char **argv)
{
    return game();
}


