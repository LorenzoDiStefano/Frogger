#ifndef FROGGER_GAME_OBJECT
#define FROGGER_GAME_OBJECT

#include "game_object.h"
#include "../physics/physics_manager.c"
#include "../physics/vector2.c"
#include "../physics/rect.c"
//#include "../gfx/sprite.h"

void game_object_update_sprite(game_object_t *game_object)
{
    game_object->sprite->sprite_rect.x = (int)game_object->position.x;
    game_object->sprite->sprite_rect.y = (int)game_object->position.y;
}

void game_object_on_collision(game_object_t *game_object, collision_info_t *delta)
{

}

void game_object_update(game_object_t *game_object, const double delta_time)
{
    if(!game_object->is_active)
        return;

    game_object->position.x+=game_object->velocity.x*delta_time;
    game_object->position.y+=game_object->velocity.y*delta_time;

    game_object->bounding_box.position.x = game_object->position.x;
    game_object->bounding_box.position.y = game_object->position.y;      

    if(game_object->sprite != NULL)
    {
        game_object_update_sprite(game_object);
    }
}

void game_object_init(game_object_t *game_object)
{
    rect_init(&game_object->bounding_box);
    vector2_init(&(game_object->position));
    vector2_init(&(game_object->velocity));
    game_object->is_active = 0;
    game_object->collider_type = 0;
    game_object->sprite = NULL;
    game_object->update = game_object_update;
}

void game_object_init_with_vectors(game_object_t *game_object, vector2_t *position, vector2_t *velocity)
{
    vector2_init(&(game_object->position));
    game_object->position.x = position->x;
    game_object->position.y = position->y;

    vector2_init(&(game_object->velocity));
    game_object->velocity.x = velocity->x;
    game_object->velocity.y = velocity->y;

    game_object->is_active = 0;
    game_object->update = game_object_update;
    game_object->sprite = NULL;
}

void game_object_set_position(game_object_t *game_object, float x, float y)
{
    vector2_t vector2;
    vector2_init_safe(&vector2,x,y);
    game_object_set_position_with_vector(game_object, vector2);
}

void game_object_set_position_with_vector(game_object_t *game_object, vector2_t new_position)
{
    game_object_set_position_x(game_object, new_position.x);
    game_object_set_position_y(game_object, new_position.y);
}

void game_object_set_position_x(game_object_t *game_object, float new_position_x)
{
    game_object->position.x = new_position_x;
}

void game_object_set_position_y(game_object_t *game_object, float new_position_y)
{
    game_object->position.y = new_position_y;
}

void game_object_set_velocity(game_object_t *game_object, vector2_t new_velocity)
{
    game_object_set_velocity_x(game_object, new_velocity.x);
    game_object_set_velocity_y(game_object, new_velocity.y);
}

void game_object_set_velocity_x(game_object_t *game_object, float new_velocity_x)
{
    game_object->velocity.x = new_velocity_x;
}

void game_object_set_velocity_y(game_object_t *game_object, float new_velocity_y)
{
    game_object->velocity.y = new_velocity_y;
}

void game_object_set_sprite(game_object_t *game_object, sprite_t *sprite)
{
    game_object->sprite = sprite;
}

#ifdef _TEST

static int test_game_object_init()
{
    game_object_t game_object;
    game_object_init(&game_object);
    return game_object.position.x == 0 && game_object.velocity.y == 0;
}

static int test_game_object_init_with_vectors()
{
    game_object_t game_object;
    vector2_t position,velocity;
    vector2_init_safe(&position,100,100);
    vector2_init_safe(&velocity,50,50);

    game_object_init_with_vectors(&game_object, &position, &velocity);
    
    return game_object.position.x < 100.001 && game_object.position.x > 99.999 &&
    game_object.position.y < 100.001 && game_object.position.y > 99.999 &&
    game_object.velocity.x < 50.001 && game_object.velocity.x > 49.999 &&
    game_object.velocity.y <= 50.001 && game_object.velocity.y >= 49.999 ;

}

static int test_game_object_update()
{
    game_object_t game_object;
    game_object_init(&game_object);
    game_object.is_active = 1;
    game_object_update(&game_object, 1);
    return game_object.position.x == 0 && game_object.position.y == 0;
}

static int test_game_object_update_moving()
{
    game_object_t game_object;
    game_object_init(&game_object);
    game_object.is_active = 1;
    game_object_set_velocity_x(&game_object, 5);
    game_object_update(&game_object, 1);
    return game_object.position.x == 5 && game_object.position.y == 0;
}

static int test_game_object_set_velocity_x()
{
    game_object_t game_object;
    game_object_init(&game_object);
    game_object_set_velocity_x(&game_object, 1);
    return game_object.velocity.x == 1 && game_object.velocity.y == 0;
}

static int test_game_object_set_velocity_y()
{
    game_object_t game_object;
    game_object_init(&game_object);
    game_object_set_velocity_y(&game_object, 1);
    return game_object.velocity.x == 0 && game_object.velocity.y == 1;
}

static int test_game_object_set_velocity()
{
    game_object_t game_object;
    vector2_t new_velocity;
    vector2_init_safe(&new_velocity, 50, 40);
    game_object_init(&game_object);
    game_object_set_velocity(&game_object, new_velocity);
    return game_object.velocity.x == 50 && game_object.velocity.y == 40;
}

static int test_game_object_set_position_x()
{
    game_object_t game_object;
    game_object_init(&game_object);
    game_object_set_position_x(&game_object, 1);
    return game_object.position.x == 1 && game_object.position.y == 0;
}

static int test_game_object_set_position_y()
{
    game_object_t game_object;
    game_object_init(&game_object);
    game_object_set_position_y(&game_object, 1);
    return game_object.position.x == 0 && game_object.position.y == 1;
}

static int test_game_object_set_position()
{
    game_object_t game_object;
    vector2_t new_position;
    vector2_init_safe(&new_position, 50, 40);
    game_object_init(&game_object);
    game_object_set_position(&game_object, 100, 40);
    return game_object.position.x == 100 && game_object.position.y == 40;
}

void test_game_object()
{
    RUN_TEST_GAME_OBJECT(test_game_object_init);
    RUN_TEST_GAME_OBJECT(test_game_object_init_with_vectors);
    RUN_TEST_GAME_OBJECT(test_game_object_set_velocity);
    RUN_TEST_GAME_OBJECT(test_game_object_set_velocity_x);
    RUN_TEST_GAME_OBJECT(test_game_object_set_velocity_y);
    RUN_TEST_GAME_OBJECT(test_game_object_update);
    RUN_TEST_GAME_OBJECT(test_game_object_update_moving);
    RUN_TEST_GAME_OBJECT(test_game_object_set_position);
    RUN_TEST_GAME_OBJECT(test_game_object_set_position_x);
    RUN_TEST_GAME_OBJECT(test_game_object_set_position_y);
}
#endif

#endif