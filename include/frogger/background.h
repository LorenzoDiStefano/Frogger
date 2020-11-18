#ifndef FROGGER_BACKGROUND
#define FROGGER_BACKGROUND
#pragma once

#include <engine/actors/game_object.h>

struct draw_manager typedef draw_manager_t;
struct physics_manager typedef physics_manager_t;
struct image_info typedef image_info_t;

typedef struct background
{
    game_object_t game_object;

}background_t;

void background_init(background_t *backgound, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info);

#endif // !FROGGER_BACKGROUND