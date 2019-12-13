#ifndef FROGGER_PLAYER
#define FROGGER_PLAYER

#include "player.h"
#include "game_object.c"
#include "../gfx/draw_manager.c"
#include "../physics/physics_manager.c"

void game_object_player_update(game_object_t *game_object,const double delta_time)
{
    game_object_update(game_object, delta_time);

    if(game_object->position.x>WINDOW_WIDTH - game_object->bounding_box.width)
    {
        game_object->position.x = WINDOW_WIDTH - game_object->bounding_box.width;
    }
    else if(game_object->position.x<0)
    {
        game_object->position.x = 0;
    }

    if(game_object->position.y<0)
    {
        game_object->position.y = 0;
    }
    else if (game_object->position.y > WINDOW_HEIGHT - game_object->bounding_box.height)
    {
        game_object->position.y = WINDOW_HEIGHT - game_object->bounding_box.height;
    }

    game_object->bounding_box.position.x = (int)game_object->position.x;
    game_object->bounding_box.position.y = (int)game_object->position.y;      

    if(game_object->sprite != NULL)
    {
        game_object_update_sprite(game_object);
    }

    ((player_t *)game_object)->is_on_log = 0;

}

void player_on_collision(struct game_object *game_object, collision_info_t *collision)
{
    game_object_t *collider = (game_object_t *)collision->collider;

    if(collider->collider_type == COLLIDER_TYPE_WATER)
    {
        //check if player is drowning
        if(((player_t *)game_object)->is_on_log == 0)
            player_die((player_t *)game_object);    
    }
    else if(collider->collider_type == COLLIDER_TYPE_CAR)
    {
        //got hit by a car
        player_die((player_t *)game_object);
    }
    else if(collider->collider_type == COLLIDER_TYPE_END)
    {
        if(collision->delta.y<-77)
        {
            printf("Player win\n");
            game_state = 0;
        }
    }
    else if(collider->collider_type == COLLIDER_TYPE_LOG)
    {
        ((player_t *)game_object)->is_on_log = 1;
        int fps = 60;
        double frame_time = (double)1000 / fps;
        vector2_t movement = vector2_mul(&collider->velocity, frame_time * 0.001);
        game_object->position = vector2_add(&game_object->position, &movement);
    }
}

void player_die(player_t *player)
{
    printf("Player died\n");
    player->game_object.position.x = player->spawn_point.x;
    player->game_object.position.y = player->spawn_point.y;
    game_object_update_sprite(&player->game_object);

}

void player_init(player_t *player, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info)
{
    player->last_frame_input = 0;
    player->is_on_log = 0;
    vector2_init_safe(&player->spawn_point, (WINDOW_WIDTH-TILE_SIZE)/2, (WINDOW_HEIGHT-TILE_SIZE));

    game_object_init(&player->game_object);

    player->game_object.bounding_box.owner = &player->game_object;
    player->game_object.on_collision = player_on_collision;
    player->game_object.update = game_object_player_update;
    player->game_object.collider_type = COLLIDER_TYPE_PLAYER;
    player->game_object.is_active = 1;

    sprite_t *sprite = malloc(sizeof(sprite_t));
    init_sprite(sprite, img_info, draw_manager->renderer, 1);
    game_object_set_sprite(&player->game_object, sprite);

    rect_set_size(&player->game_object.bounding_box, player->game_object.sprite->sprite_rect.w, player->game_object.sprite->sprite_rect.h);

    player_die(player);

    draw_manager_add_sprite(draw_manager, sprite);
    physics_manager_add_player(physics_manager, &player->game_object.bounding_box);
}

void player_read_input(player_t *player)
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    
    vector2_t direction;
    vector2_init(&direction);

    if(keystates[SDL_SCANCODE_LEFT])
        direction.x--;
    else if(keystates[SDL_SCANCODE_RIGHT])
        direction.x++;
    else if(keystates[SDL_SCANCODE_UP])
        direction.y--;
    else if(keystates[SDL_SCANCODE_DOWN])
        direction.y++;    

    if(player->last_frame_input > 0)
    {
        player->last_frame_input--;
        return;
    }

    player->last_frame_input = 7;

    direction = vector2_mul(&direction, TILE_SIZE);
    direction = vector2_add(&direction, &player->game_object.position);
    game_object_set_position_with_vector(&player->game_object, direction);
}

void game_object_car_update(game_object_t *game_object, const double delta_time)
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

void car_init(car_t *car, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info)
{
    //initializing game_object
    game_object_init(&car->game_object);

    car->game_object.is_active = 1;
    car->game_object.update = game_object_car_update;
    car->game_object.collider_type = COLLIDER_TYPE_CAR;
    car->game_object.bounding_box.owner = &car->game_object;

    game_object_set_position(&car->game_object, 0, WINDOW_HEIGHT);

    sprite_t *sprite = malloc(sizeof(sprite_t));
    init_sprite(sprite, img_info, draw_manager->renderer, 1); 
    game_object_set_sprite(&car->game_object, sprite);

    rect_set_size(&car->game_object.bounding_box, car->game_object.sprite->sprite_rect.w, car->game_object.sprite->sprite_rect.h);

    draw_manager_add_sprite(draw_manager, car->game_object.sprite);
    physics_manager_add_rect(physics_manager, &car->game_object.bounding_box);
}

void backgound_init(backgound_t *background, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info)
{
    //initializing game_object
    game_object_init(&background->game_object);

    background->game_object.is_active = 1;
    background->game_object.collider_type = COLLIDER_TYPE_OBASTACLE;
    background->game_object.bounding_box.owner = &background->game_object;
    
    sprite_t *sprite = malloc(sizeof(sprite_t));
    init_sprite(sprite, img_info, draw_manager->renderer, 1);  
    game_object_set_sprite(&background->game_object, sprite);

    //temporary, waiting for art
    sprite->sprite_rect.h = TILE_SIZE;
    sprite->sprite_rect.w = WINDOW_WIDTH;
    rect_set_size(&background->game_object.bounding_box, sprite->sprite_rect.w, sprite->sprite_rect.h);

    draw_manager_add_sprite_bg(draw_manager, background->game_object.sprite);
    physics_manager_add_rect(physics_manager, &background->game_object.bounding_box);
}

#endif