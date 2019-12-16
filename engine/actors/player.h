#ifndef FROGGER_PLAYER_HEADER
#define FROGGER_PLAYER_HEADER

#include "../physics/vector2.h"
#include "../physics/physics_manager.h"
#include "../actors/game_object.h"
#include "../gfx/draw_manager.h"

typedef struct player
{
    game_object_t game_object;
    vector2_t spawn_point;
    int is_on_log;
    int score;
    int last_frame_input;
    vector2_t input_direction;
}player_t;

void player_init(player_t *player, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info);
void player_read_input(player_t *player);
void player_die(player_t *player);
void player_set_position(player_t *player, float x, float y);

typedef struct car
{
    game_object_t game_object;
}car_t;

void car_init(car_t *car, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info);

typedef struct backgound
{
    game_object_t game_object;
}backgound_t;

void backgound_init(backgound_t *backgound, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info);


#endif