#ifndef FROGGER_OBSTACLE_HEADER
#define FROGGER_OBSTACLE_HEADER

#include "../physics/vector2.h"
#include "../physics/physics_manager.h"
#include "../actors/game_object.h"
#include "../gfx/draw_manager.h"

typedef struct obstacle
{
    game_object_t game_object;
}obstacle_t;

void obstacle_init(obstacle_t *car, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info);

#include "obstacle.c"
#endif