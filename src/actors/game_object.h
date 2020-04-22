#ifndef FROGGER_GAME_OBJECT_HEADER
#define FROGGER_GAME_OBJECT_HEADER

#include "../engine/physics_manager.h"
#include "../engine/gfx/sprite.h"

typedef struct game_object
{
    vector2_t position;
    uint8_t collider_type;
    int is_active;

    sprite_t *sprite;
    rigid_body_t *rigid_body;   

    void (*on_collision)(struct game_object *game_object, collision_info_t *collision);
    void (*update)(struct game_object *game_object, const double delta_time);

}game_object_t;

void game_object_init(game_object_t *game_object);
void game_object_init_with_vectors(game_object_t *game_object, const vector2_t *position, const vector2_t *velocity);

void game_object_set_position_with_vector(game_object_t *game_object, const vector2_t new_position);
void game_object_set_position(game_object_t *game_object, const float x, const float y);
void game_object_set_position_x(game_object_t *game_object, const float new_position_x);
void game_object_set_position_y(game_object_t *game_object, const float new_position_y);

void game_object_set_velocity(game_object_t *game_object, const vector2_t new_velocity);
void game_object_set_velocity_x(game_object_t *game_object, const float new_velocity_x);
void game_object_set_velocity_y(game_object_t *game_object, const float new_velocity_y);

void game_object_set_sprite(game_object_t *game_object, sprite_t *sprite);
void game_object_update(game_object_t *game_object, const double delta_time);
void game_object_update_sprite(game_object_t *game_object);

#endif 