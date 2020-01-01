#include "background.h"

void background_init(background_t *background, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info)
{
    //initializing game_object
    game_object_init(&background->game_object);

    background->game_object.is_active = 1;
    background->game_object.collider_type = COLLIDER_TYPE_OBASTACLE;
    
    sprite_t *sprite = (sprite_t*)malloc(sizeof(sprite_t));
    init_sprite(sprite, img_info, draw_manager->renderer, 1);  
    game_object_set_sprite(&background->game_object, sprite);

    //temporary, waiting for art
    sprite->sprite_rect.h = TILE_SIZE;
    sprite->sprite_rect.w = WINDOW_WIDTH;

    rigid_body_t *rigid_body = (rigid_body_t*)malloc(sizeof(rigid_body_t));
    rigid_body_init(rigid_body);
    background->game_object.rigid_body = rigid_body;

    background->game_object.rigid_body->bounding_box.owner = &background->game_object;
    rect_set_size(&background->game_object.rigid_body->bounding_box, sprite->sprite_rect.w, sprite->sprite_rect.h);

    draw_manager_add_sprite_bg(draw_manager, background->game_object.sprite);
    physics_manager_add_rect(physics_manager, &background->game_object.rigid_body->bounding_box);
}