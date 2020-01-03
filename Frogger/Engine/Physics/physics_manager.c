#include "physics_manager.h"

void physics_manager_init(physics_manager_t *physics_manager)
{
    physics_manager->max_rects = 100;
    physics_manager->player = NULL;
    physics_manager->rects_to_draw = 0;
}

void physics_manager_update_rb(physics_manager_t *physics_manager, const double delta_time)
{
    if(physics_manager->player == NULL)
    {
        printf("missing player\n");
        return;
    }

    //update player
    game_object_t *player_game_object = physics_manager->player->owner;
    player_game_object->update(player_game_object, delta_time);

    for (int i = 0; i < physics_manager->rects_to_draw; i++)
    {
        game_object_t *game_object_address = physics_manager->rects[i]->owner;

        if (game_object_address->rigid_body->update == NULL)
        {
            printf("null update");
        }
        else
        {
            game_object_address->rigid_body->update(game_object_address->rigid_body, delta_time);
        }
    } 
}

void physics_manager_add_rect(physics_manager_t *physics_manager, rect_t *rect)
{
    physics_manager->rects[physics_manager->rects_to_draw] = rect;
    physics_manager->rects_to_draw++;
}

void physics_manager_add_player(physics_manager_t *physics_manager, rect_t *rect)
{
    physics_manager->player = rect;
}

void physics_manager_check_collisions(physics_manager_t *physics_manager)
{
    if(physics_manager->player == NULL)
    {
        return;
    }

    for (int i = 0; i < physics_manager->rects_to_draw; i++)
    {
        collision_info_t collision;
        collision_info_init(&collision);
        if(rect_check_collision(physics_manager->player, physics_manager->rects[i], &collision) == 1)
        {
            game_object_t *player_game_object = physics_manager->player->owner;
            player_game_object->on_collision(player_game_object, &collision);
        }     
    } 
}
