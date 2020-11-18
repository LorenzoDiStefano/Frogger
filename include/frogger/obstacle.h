#ifndef FROGGER_OBSTACLE
#define FROGGER_OBSTACLE
#pragma once

#include <engine/actors/game_object.h>

struct draw_manager typedef draw_manager_t;
struct physics_manager typedef physics_manager_t;
struct image_info typedef image_info_t;

typedef struct obstacle
{
    game_object_t game_object;

}obstacle_t;

void obstacle_init(obstacle_t *car, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info);

#endif // !FROGGER_OBSTACLE