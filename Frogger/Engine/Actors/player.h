#ifndef FROGGER_PLAYER_HEADER
#define FROGGER_PLAYER_HEADER

#include "../physics/physics_manager.h"
#include "../gfx/draw_manager.h"
#include "game_object.h"

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

#endif