#include "obstacle.h"

void obstacle_update(game_object_t *game_object, const double delta_time)
{
    game_object_update(game_object, delta_time);
    if(game_object->rigid_body->position.x > WINDOW_WIDTH)
    {
        game_object->rigid_body->position.x=-game_object->rigid_body->bounding_box.width;
    }
    else if(game_object->rigid_body->position.x < -(game_object->rigid_body->bounding_box.width))
    {
        game_object->rigid_body->position.x = WINDOW_WIDTH;
    }
}

void obstacle_init(obstacle_t *obstacle, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info)
{
    game_object_init(&obstacle->game_object);

    obstacle->game_object.is_active = 1;
    obstacle->game_object.update = obstacle_update;
    obstacle->game_object.collider_type = COLLIDER_TYPE_CAR;

    sprite_t *sprite = (sprite_t*)malloc(sizeof(sprite_t));
    init_sprite(sprite, img_info, draw_manager->renderer, 1); 
    game_object_set_sprite(&obstacle->game_object, sprite);

    rigid_body_t *rigid_body = (rigid_body_t*)malloc(sizeof(rigid_body_t));
    
    if (rigid_body == NULL)
    {
        printf("failed malloc rigid_body\n func: background_init\n");
        exit(-1);
    }

    rigid_body_init(rigid_body);
    obstacle->game_object.rigid_body = rigid_body;

    obstacle->game_object.rigid_body->is_active = 1;
    obstacle->game_object.rigid_body->bounding_box.owner = &obstacle->game_object;
    rect_set_size(&obstacle->game_object.rigid_body->bounding_box, obstacle->game_object.sprite->sprite_rect.w, obstacle->game_object.sprite->sprite_rect.h);

    game_object_set_position(&obstacle->game_object, 0, WINDOW_HEIGHT);

    draw_manager_add_sprite(draw_manager, obstacle->game_object.sprite);
    physics_manager_add_rigid_body(physics_manager, obstacle->game_object.rigid_body);
}