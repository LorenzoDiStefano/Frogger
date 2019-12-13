#ifndef FROGGER_GAME_OBJECT_HEADER
#define FROGGER_GAME_OBJECT_HEADER

#include "../physics/vector2.h"
#include "../physics/rect.h"
#include "../gfx/sprite.h"

typedef struct game_object
{
    vector2_t velocity,position;
    sprite_t *sprite;
    rect_t bounding_box;
    int is_active;
    uint8_t collider_type;

    void (*on_collision)(struct game_object *game_object, collision_info_t *collision);
    void (*update)(struct game_object *game_object, const double delta_time);

}game_object_t;

void game_object_init(game_object_t *game_object);
void game_object_init_with_vectors(game_object_t *game_object, vector2_t *position, vector2_t *velocity);

void game_object_set_position_with_vector(game_object_t *game_object, vector2_t new_position);
void game_object_set_position(game_object_t *game_object, float x, float y);
void game_object_set_position_x(game_object_t *game_object, float new_position_x);
void game_object_set_position_y(game_object_t *game_object, float new_position_y);

void game_object_set_velocity(game_object_t *game_object, vector2_t new_velocity);
void game_object_set_velocity_x(game_object_t *game_object, float new_velocity_x);
void game_object_set_velocity_y(game_object_t *game_object, float new_velocity_y);

void game_object_set_sprite(game_object_t *game_object, sprite_t *sprite);

#ifdef _TEST
void test_wrapper(const char *name, int (*func)());
#define RUN_TEST_GAME_OBJECT(func) test_wrapper(#func, func);

void test_game_object();

#endif

#endif 