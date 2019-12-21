#include "player.h"

void player_update(game_object_t *game_object,const double delta_time)
{
    game_object_update(game_object, delta_time);

    if(game_object->position.x > WINDOW_WIDTH - game_object->rigid_body->bounding_box.width)
    {
        game_object->position.x = WINDOW_WIDTH - game_object->rigid_body->bounding_box.width;
    }
    else if(game_object->position.x < 0)
    {
        game_object->position.x = 0;
    }

    if(game_object->position.y < 0)
    {
        game_object->position.y = 0;
    }
    else if (game_object->position.y > WINDOW_HEIGHT - game_object->rigid_body->bounding_box.height)
    {
        game_object->position.y = WINDOW_HEIGHT - game_object->rigid_body->bounding_box.height;
    }

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
            exit(1);
        }
    }
    else if(collider->collider_type == COLLIDER_TYPE_LOG)
    {
        ((player_t *)game_object)->is_on_log = 1;
        int fps = 60;
        double frame_time = (double)1000 / fps;
        vector2_t movement = vector2_mul(&collider->rigid_body->velocity, frame_time * 0.001);
        game_object_set_position_with_vector(game_object,  vector2_add(&game_object->position, &movement));
    }
}

void player_die(player_t *player)
{
    printf("Player died\n");
    game_object_set_position_with_vector(&player->game_object, player->spawn_point);
    game_object_update_sprite(&player->game_object);

}

void player_init(player_t *player, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info)
{
    game_object_init(&player->game_object);

    player->last_frame_input = 0;
    player->is_on_log = 0;
    vector2_init_safe(&player->spawn_point, (WINDOW_WIDTH-TILE_SIZE)/2, (WINDOW_HEIGHT-TILE_SIZE));

    player->game_object.on_collision = player_on_collision;
    player->game_object.update = player_update;
    player->game_object.collider_type = COLLIDER_TYPE_PLAYER;
    player->game_object.is_active = 1;

    player->last_frame_input = 0;
    vector2_init(&player->input_direction);

    sprite_t *sprite = malloc(sizeof(sprite_t));
    init_sprite(sprite, img_info, draw_manager->renderer, 1);
    game_object_set_sprite(&player->game_object, sprite);

    rigid_body_t *rigid_body = malloc(sizeof(rigid_body_t));
    rigid_body_init(rigid_body);
    player->game_object.rigid_body = rigid_body;

    rect_set_size(&player->game_object.rigid_body->bounding_box, player->game_object.sprite->sprite_rect.w, player->game_object.sprite->sprite_rect.h);
    player->game_object.rigid_body->bounding_box.owner = &player->game_object;

    player_die(player);

    draw_manager_add_sprite(draw_manager, sprite);
    physics_manager_add_player(physics_manager, &player->game_object.rigid_body->bounding_box);
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

    int frame_input;

    if(direction.x == 0 && direction.y == 0)
    {
        frame_input = 0;
    }
    else
    {
        frame_input = 1;
        player->input_direction = direction;
    }

    if(player->last_frame_input == 1 && frame_input == 0)
    {
        direction = vector2_mul(&player->input_direction, TILE_SIZE);
        direction = vector2_add(&direction, &player->game_object.position);
        game_object_set_position_with_vector(&player->game_object, direction);
    }

    player->last_frame_input = frame_input;
}