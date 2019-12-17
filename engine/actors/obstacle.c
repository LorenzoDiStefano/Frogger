#ifndef FROGGER_OBSTACLE
#define FROGGER_OBSTACLE

#include "obstacle.h"

void obstacle_update(game_object_t *game_object, const double delta_time)
{
    game_object_update(game_object, delta_time);
    if(game_object->position.x > WINDOW_WIDTH)
    {
        game_object->position.x=-game_object->bounding_box.width;
    }
    else if(game_object->position.x<-(game_object->bounding_box.width))
    {
        game_object->position.x = WINDOW_WIDTH;
    }
}

void obstacle_init(obstacle_t *obstacle, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info)
{
    //initializing game_object
    game_object_init(&obstacle->game_object);

    obstacle->game_object.is_active = 1;
    obstacle->game_object.update = obstacle_update;
    obstacle->game_object.collider_type = COLLIDER_TYPE_CAR;
    obstacle->game_object.bounding_box.owner = &obstacle->game_object;

    game_object_set_position(&obstacle->game_object, 0, WINDOW_HEIGHT);

    sprite_t *sprite = malloc(sizeof(sprite_t));
    init_sprite(sprite, img_info, draw_manager->renderer, 1); 
    game_object_set_sprite(&obstacle->game_object, sprite);

    rect_set_size(&obstacle->game_object.bounding_box, obstacle->game_object.sprite->sprite_rect.w, obstacle->game_object.sprite->sprite_rect.h);

    draw_manager_add_sprite(draw_manager, obstacle->game_object.sprite);
    physics_manager_add_rect(physics_manager, &obstacle->game_object.bounding_box);
}

#endif