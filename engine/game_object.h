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

#ifdef _TEST

#include "engine/vector2.c"
#include "tests/tests.c"
#include "tests/test_clock.c"
#include "tests/test_draw_manager.c"
#include "tests/test_vector2.c"
#include "engine/draw_manager.h"

#endif
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

typedef struct game_object
{
    vector2_t velocity,position;
    sprite_t *sprite;
    int is_active;

}game_object_t;

void game_object_init(game_object_t *game_object);
void game_object_init_with_vectors(game_object_t *game_object, vector2_t *position, vector2_t *velocity);

void game_object_update(game_object_t *game_object, double delta_time);

void game_object_set_position(game_object_t *game_object, vector2_t new_position);
void game_object_set_position_x(game_object_t *game_object, float new_position_x);
void game_object_set_position_y(game_object_t *game_object, float new_position_y);

void game_object_set_velocity(game_object_t *game_object, vector2_t new_velocity);
void game_object_set_velocity_x(game_object_t *game_object, float new_velocity_x);
void game_object_set_velocity_y(game_object_t *game_object, float new_velocity_y);

void game_object_set_sprite(game_object_t *game_object, sprite_t *sprite);

#ifdef _TEST
void game_object_test_wrapper(const char *name, int (*func)(game_object_t *game_object));
#define RUN_TEST_GAME_OBJECT(func) game_object_test_wrapper(#func, func);

void test_game_object();

#endif