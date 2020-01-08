#include "physics_manager.h"

int physics_manager_init(physics_manager_t *physics_manager)
{
    if (physics_manager == NULL)
        return 1;

    physics_manager->max_rb = 100;
    physics_manager->player_rb = NULL;
    physics_manager->rb_count = 0;
    return 0;
}

void physics_manager_update_rb(physics_manager_t *physics_manager, const double delta_time)
{
    rigid_body_t *play_rb = physics_manager->player_rb;
    play_rb->update(play_rb, delta_time);

    for (int i = 0; i < physics_manager->rb_count; i++)
    {
        rigid_body_t *rb = physics_manager->rigid_bodies[i];
        rb->update(rb, delta_time);
    } 
}

void physics_manager_add_rigid_body(physics_manager_t *physics_manager, rigid_body_t *rect)
{
    physics_manager->rigid_bodies[physics_manager->rb_count] = rect;
    physics_manager->rb_count++;
}

void physics_manager_add_player(physics_manager_t *physics_manager, rigid_body_t *player)
{
    physics_manager->player_rb = player;
}

void physics_manager_check_collisions(physics_manager_t *physics_manager)
{
    for (int i = 0; i < physics_manager->rb_count; i++)
    {
        collision_info_t collision;
        collision_info_init(&collision);
        if(rect_check_collision(&physics_manager->player_rb->bounding_box, 
            &physics_manager->rigid_bodies[i]->bounding_box, &collision) == 1)
        {
            game_object_t *player_game_object = physics_manager->player_rb->owner;
            player_game_object->on_collision(player_game_object, &collision);
        }     
    } 
}
