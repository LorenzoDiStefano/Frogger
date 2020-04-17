#ifndef PHYSICS_MANAGER_HEADER
#define PHYSICS_MANAGER_HEADER

#include "physics/rigid_body.h"
#include "../actors/game_object.h"

typedef struct physics_manager
{
    rigid_body_t *rigid_bodies[100];
    int rb_count;
    int max_rb;
    rigid_body_t *player_rb;

} physics_manager_t;

int physics_manager_init(physics_manager_t *physics_manager);
void physics_manager_update_rb(physics_manager_t *physics_manager, const double delta_time);
void physics_manager_add_rigid_body(physics_manager_t *physics_manager, rigid_body_t *rigid_body);
void physics_manager_check_collisions(physics_manager_t *physics_manager);
void physics_manager_add_player(physics_manager_t *physics_manager, rigid_body_t *rigid_body);

#endif