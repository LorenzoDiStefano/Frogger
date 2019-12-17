#ifndef PHYSICS_MANAGER_HEADER
#define PHYSICS_MANAGER_HEADER

#include "rect.h"
#include "../actors/game_object.h"

typedef struct physics_manager
{
    rect_t *rects[100];
    int rects_to_draw;
    int max_rects;
    rect_t *player;

} physics_manager_t;

void physics_manager_init(physics_manager_t *physics_manager);
void physics_manager_update(physics_manager_t *physics_manager, const double delta_time);
void physics_manager_add_rect(physics_manager_t *physics_manager, rect_t *rect);
void physics_manager_check_collisions(physics_manager_t *physics_manager);
void physics_manager_add_player(physics_manager_t *physics_manager, rect_t *rect);

#endif