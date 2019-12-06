#ifndef FROGGER_LIBS
#define FROGGER_LIBS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/clock.h"
#include "engine/draw_manager.h"
#include "engine/vector2.h"
#include "engine/draw_manager.c"
#include "engine/clock.c"
#include "engine/vector2.c"
#include "engine/game_object.h"
#include "engine/game_object.c"

#ifdef _TEST

#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/test_vector2.c"

#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif


void game_object_init(game_object_t *game_object)
{
    vector2_init(&(game_object->position));
    vector2_init(&(game_object->velocity));
    game_object->is_active = 0;
}

void game_object_init_with_vectors(game_object_t *game_object, vector2_t *position, vector2_t *velocity)
{
    vector2_init(&(game_object->position));
    game_object->position.x = position->x;
    game_object->position.y = position->y;

    vector2_init(&(game_object->velocity));
    game_object->velocity.x = velocity->x;
    game_object->velocity.y = velocity->y;

    game_object->is_active = 0;
    game_object->sprite = NULL;
}

void game_object_update(game_object_t *game_object, double delta_time)
{
    if(!game_object->is_active)
        return;

    game_object->position.x+=game_object->velocity.x*delta_time;
    game_object->position.y+=game_object->velocity.y*delta_time;

    if(game_object->sprite == NULL)
        return;

    game_object->sprite->sprite_rect.x = (int)game_object->position.x;
    game_object->sprite->sprite_rect.y = (int)game_object->position.y;
}

void game_object_set_position(game_object_t *game_object, vector2_t new_position)
{
    game_object_set_position_x(game_object,new_position.x);
    game_object_set_position_y(game_object,new_position.y);
}

void game_object_set_position_x(game_object_t *game_object, float new_position_x)
{
    game_object->position.x = new_position_x;
}

void game_object_set_position_y(game_object_t *game_object, float new_position_y)
{
    game_object->position.y = new_position_y;
}

void game_object_set_velocity(game_object_t *game_object, vector2_t new_velocity)
{
    game_object_set_velocity_x(game_object,new_velocity.x);
    game_object_set_velocity_y(game_object,new_velocity.y);
}

void game_object_set_velocity_x(game_object_t *game_object, float new_velocity_x)
{
    game_object->velocity.x=new_velocity_x;
}

void game_object_set_velocity_y(game_object_t *game_object, float new_velocity_y)
{
    game_object->velocity.y=new_velocity_y;
}

void game_object_set_sprite(game_object_t *game_object, sprite_t *sprite)
{
    game_object->sprite = sprite;
}

#ifdef _TEST

static int test_game_object_init(game_object_t *game_object)
{
    game_object_init(game_object);
    return game_object->position.x == 0 && game_object->velocity.y == 0;
}

static int test_game_object_init_with_vectors(game_object_t *game_object)
{
    vector2_t position,velocity;
    vector2_init_safe(&position,100,100);
    vector2_init_safe(&velocity,50,50);

    game_object_init_with_vectors(game_object,&position,&velocity);
    
    return game_object->position.x < 100.001 && game_object->position.x > 99.999 &&
    game_object->position.y < 100.001 && game_object->position.y > 99.999 &&
    game_object->velocity.x < 50.001 && game_object->velocity.x > 49.999 &&
    game_object->velocity.y <= 50.001 && game_object->velocity.y >= 49.999 ;

}

static int test_game_object_update(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_update(game_object,1);
    return game_object->position.x == 0 && game_object->position.y == 0;
}

static int test_game_object_update_moving(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_velocity_x(game_object,5);
    game_object_update(game_object,1);
    return game_object->position.x == 5 && game_object->position.y == 0;
}

static int test_game_object_set_velocity_x(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_velocity_x(game_object,1);
    return game_object->velocity.x == 1 && game_object->velocity.y == 0;
}

static int test_game_object_set_velocity_y(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_velocity_y(game_object,1);
    return game_object->velocity.x == 0 && game_object->velocity.y == 1;
}

static int test_game_object_set_velocity(game_object_t *game_object)
{
    vector2_t new_velocity;
    vector2_init_safe(&new_velocity,50,40);
    game_object_init(game_object);
    game_object_set_velocity(game_object,new_velocity);
    return game_object->velocity.x == 50 && game_object->velocity.y == 40;
}

static int test_game_object_set_position_x(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_position_x(game_object,1);
    return game_object->position.x == 1 && game_object->position.y == 0;
}

static int test_game_object_set_position_y(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_position_y(game_object,1);
    return game_object->position.x == 0 && game_object->position.y == 1;
}

static int test_game_object_set_position(game_object_t *game_object)
{
    vector2_t new_position;
    vector2_init_safe(&new_position,50,40);
    game_object_init(game_object);
    game_object_set_position(game_object,new_position);
    return game_object->position.x == 50 && game_object->position.y == 40;
}

void test_game_object()
{
    RUN_TEST_GAME_OBJECT(test_game_object_init);
    RUN_TEST_GAME_OBJECT(test_game_object_init_with_vectors);
    RUN_TEST_GAME_OBJECT(test_game_object_set_velocity);
    RUN_TEST_GAME_OBJECT(test_game_object_set_velocity_x);
    RUN_TEST_GAME_OBJECT(test_game_object_set_velocity_y);
    RUN_TEST_GAME_OBJECT(test_game_object_update);
    RUN_TEST_GAME_OBJECT(test_game_object_update_moving);
    RUN_TEST_GAME_OBJECT(test_game_object_set_position);
    RUN_TEST_GAME_OBJECT(test_game_object_set_position_x);
    RUN_TEST_GAME_OBJECT(test_game_object_set_position_y);
}
#endif
void player_init(player_t *player, draw_manager_t *draw_manager)
{
    game_object_init(&player->game_object);
    sprite_t *sprite=malloc(sizeof(sprite_t));
    image_info_t img_inf;
    load_image(&img_inf,"assets/test.png");
    init_sprite(sprite, img_inf, draw_manager->renderer,1);
    draw_manager_add_sprite(draw_manager, sprite);
    vector2_t position,velocity;
    vector2_init_safe(&position,100,100);
    vector2_init_safe(&velocity,0,0);
    
    game_object_init_with_vectors(&player->game_object, &position, &velocity);
    game_object_set_sprite(&player->game_object,sprite);
    player->game_object.is_active = 1;
}
    

void player_read_input(player_t *player)
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    vector2_init(&player->game_object.velocity);

    if(keystates[SDL_SCANCODE_LEFT])
        player->game_object.velocity.x--;
    if(keystates[SDL_SCANCODE_RIGHT])
        player->game_object.velocity.x++;
    if(keystates[SDL_SCANCODE_UP])
        player->game_object.velocity.y--;
    if(keystates[SDL_SCANCODE_DOWN])
        player->game_object.velocity.y++;            

    player->game_object.velocity = vector2_mul(&player->game_object.velocity,(double)100);
    game_object_set_velocity(&player->game_object, player->game_object.velocity);
}