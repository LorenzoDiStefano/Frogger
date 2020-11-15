#ifndef FROGGER_PLAYER
#define FROGGER_PLAYER
#pragma once

#include <engine/actors/game_object.h>

struct image_info typedef image_info_t;
struct draw_manager typedef draw_manager_t;
struct physics_manager typedef physics_manager_t;

typedef struct player
{
    game_object_t game_object;
    vector2_t spawn_point;
    int is_on_log;
    int score;
    int last_frame_input;
    vector2_t input_direction;
}player_t;

void player_init(player_t *player, draw_manager_t *draw_manager, image_info_t *img_info);
void player_read_input(player_t *player);
void player_die(player_t *player);
void player_set_position(player_t *player, float x, float y);

#endif // !FROGGER_PLAYER