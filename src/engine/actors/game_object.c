#include <engine/physics/rigid_body.h>
#include <engine/gfx/sprite.h>
#include <engine/actors/game_object.h>
#include <math.h>
#include <stdlib.h>

void game_object_update_sprite(game_object_t *game_object)
{
    double integral;
    double fractional = modf(game_object->rigid_body->position.x, &integral);
    int dir = (int)copysign(1.0, fractional);

    if(fabs(fractional)>.5f)
        game_object->sprite->sprite_rect.x = (int)integral + (1 * dir);
    else
        game_object->sprite->sprite_rect.x = (int)integral;

    game_object->sprite->sprite_rect.y = (int)game_object->rigid_body->position.y;
}

void game_object_on_collision(game_object_t *game_object, collision_info_t *delta)
{

}

//if the gameobject is active updates it position to rigid body if present and moves sprite 
void game_object_update(game_object_t *game_object, const double delta_time)
{
    if(!game_object->is_active)
        return;

    if (game_object->rigid_body != NULL)
    {
        vector2_set(&game_object->position, game_object->rigid_body->position.x, game_object->rigid_body->position.y);
    }

    if(game_object->sprite != NULL)
    {
        game_object_update_sprite(game_object);
    }
}

void game_object_init(game_object_t *game_object)
{
    vector2_init(&(game_object->position));

    game_object->is_active = 0;
    game_object->collider_type = 0;
    game_object->sprite = NULL;
    game_object->rigid_body = NULL;
    game_object->update = game_object_update;
}

void game_object_init_with_vectors(game_object_t *game_object, const vector2_t *position, const vector2_t *velocity)
{
    game_object_init(game_object);
    game_object_set_position_with_vector(game_object, *position);

    if (game_object->rigid_body == NULL)
        return;

    game_object->rigid_body->velocity.x = velocity->x;
    game_object->rigid_body->velocity.y = velocity->y;
}

void game_object_set_position(game_object_t *game_object, const float x, const float y)
{
    vector2_t vector2;
    vector2_set(&vector2, x, y);
    game_object_set_position_with_vector(game_object, vector2);

    if(game_object->sprite != NULL)
        game_object_update_sprite(game_object);
}

void game_object_set_position_with_vector(game_object_t *game_object, const vector2_t new_position)
{
    if(game_object->rigid_body != NULL)
    {
        rigid_body_set_position_with_vector2(game_object->rigid_body, new_position);
    }
    else
    {
        game_object_set_position_x(game_object, new_position.x);
        game_object_set_position_y(game_object, new_position.y);
    }
}

void game_object_set_position_x(game_object_t *game_object, const float new_position_x)
{
    game_object->position.x = new_position_x;
}

void game_object_set_position_y(game_object_t *game_object, const float new_position_y)
{
    game_object->position.y = new_position_y;
}

void game_object_set_velocity(game_object_t *game_object, const vector2_t new_velocity)
{
    if (game_object->rigid_body == NULL)
        return;
    game_object_set_velocity_x(game_object, new_velocity.x);
    game_object_set_velocity_y(game_object, new_velocity.y);
}

void game_object_set_velocity_x(game_object_t *game_object, const float new_velocity_x)
{
    game_object->rigid_body->velocity.x = fabs(new_velocity_x);
    rigid_body_set_direction(game_object->rigid_body, new_velocity_x ,0);
}

void game_object_set_velocity_y(game_object_t *game_object, const float new_velocity_y)
{
    game_object->rigid_body->velocity.y = new_velocity_y;
}

void game_object_set_sprite(game_object_t *game_object, sprite_t *sprite)
{
    game_object->sprite = sprite;
}