#define SDL_MAIN_HANDLED
#include <SDL.h>


typedef struct vector2
{
    float x,y;

}vector2_t;

vector2_t vector2_add(vector2_t *first_value, vector2_t *second_value);//return first_value+second_value
vector2_t vector2_sub(vector2_t *first_value, vector2_t *second_value);//return first_value-second_value
vector2_t vector2_mul(vector2_t *first_value, double value);
vector2_t vector2_get_deep_copy(vector2_t *vector2);
int vector2_init(vector2_t *vector2);
int vector2_init_safe(vector2_t *vector2, float x, float y);

#ifdef _TEST
void vector2_test_wrapper(const char *name, int (*func)(vector2_t *vector2));
#define RUN_TEST_VECTOR2(func) vector2_test_wrapper(#func, func);

void test_vector2();

#endif

typedef struct collision_info
{
    vector2_t delta;
    void *collider;

}collision_info_t;

#define COLLIDER_TYPE_PLAYER 1
#define COLLIDER_TYPE_CAR 2
#define COLLIDER_TYPE_OBASTACLE 4

void collision_info_init(collision_info_t *collision_info);

#ifdef _TEST
void collision_info_test_wrapper(const char *name, int (*func)(collision_info_t *collision_info));
#define RUN_TEST_COLLISION_INFO(func) collision_info_test_wrapper(#func, func);

void test_collision_info();

#endif

typedef struct rect
{
    vector2_t position;
    void *owner;//should be game_object
    int width, height;
    float half_width, half_height;
} rect_t;

void rect_init(rect_t* rect);
void rect_set_size(rect_t* rect, int width, int height);
void rect_init_safe(rect_t* rect, int width, int height, vector2_t position, void *owner);
void rect_set_position(rect_t* rect, vector2_t new_position);
void rect_set_position_x(rect_t *game_object, float new_position_x);
void rect_set_position_y(rect_t *game_object, float new_position_y);

//to do, return collision info instead of int
int rect_check_collision(rect_t *first_rect, rect_t *second_rect, collision_info_t *collision);

#ifdef _TEST
void rect_test_wrapper(const char *name, int (*func)(rect_t *rect));
#define RUN_TEST_RECT(func) rect_test_wrapper(#func, func);

void test_rect();

#endif

typedef struct image_info
{
    int width, height, comp, length;
    unsigned char *image;
}image_info_t;

typedef struct sprite
{
    SDL_Rect sprite_rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    float scale;
}sprite_t;

void init_sprite(sprite_t *sprite, image_info_t img_info, SDL_Renderer *renderer, float scale);

typedef struct draw_manager
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    sprite_t **sprites;
    int sprites_to_draw;
    int max_sprites;

    void (*draw_scene)(struct draw_manager *draw_manager);
} draw_manager_t;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int draw_manager_init(draw_manager_t* draw_manager);
int load_image(image_info_t *img, const char *path);

#ifdef _TEST
void draw_manager_test_wrapper(const char *name, int (*func)(draw_manager_t *draw_manager));
#define RUN_TEST_DRAW_MANAGER(func) draw_manager_test_wrapper(#func, func);

void test_draw_manager();

#endif

typedef struct game_object
{
    vector2_t velocity,position;
    sprite_t *sprite;
    rect_t bounding_box;
    int is_active;
    uint8_t collider_type;

    void (*on_collision)(struct game_object *game_object, collision_info_t *delta);
    void (*update)(struct game_object *game_object, double delta_time);

}game_object_t;

void game_object_init(game_object_t *game_object);
void game_object_init_with_vectors(game_object_t *game_object, vector2_t *position, vector2_t *velocity);


void game_object_set_position(game_object_t *game_object, vector2_t new_position);
void game_object_set_position_x(game_object_t *game_object, float new_position_x);
void game_object_set_position_y(game_object_t *game_object, float new_position_y);

void game_object_set_velocity(game_object_t *game_object, vector2_t new_velocity);
void game_object_set_velocity_x(game_object_t *game_object, float new_velocity_x);
void game_object_set_velocity_y(game_object_t *game_object, float new_velocity_y);

void game_object_set_sprite(game_object_t *game_object, sprite_t *sprite);

#ifdef _TEST
void game_object_test_wrapper(const char *name, int (*func)(game_object_t *game_object));
#define RUN_TEST_GAME_OBJECT(func) game_object_test_wrapper(#func, func);

void test_game_object();

#endif

typedef struct physics_manager
{
    rect_t **rects;
    int rects_to_draw;
    int max_rects;
    rect_t *player;

} physics_manager_t;

void physics_manager_init(physics_manager_t *physics_manager);
void physics_manager_update(physics_manager_t *physics_manager, double delta_time);
void physics_manager_add_rect(physics_manager_t *physics_manager, rect_t *rect);
void physics_manager_check_collisions(physics_manager_t *physics_manager);
void physics_manager_add_player(physics_manager_t *physics_manager, rect_t *rect);

typedef struct player
{
    game_object_t game_object;
    vector2_t spawn_point;
    int score;
}player_t;

void player_init(player_t *player, draw_manager_t *draw_manager, physics_manager_t *physics_manager);
void player_read_input(player_t *player);
void player_die(player_t *player);

typedef struct wall
{
    game_object_t game_object;
}wall_t;

void wall_init(wall_t *wall, draw_manager_t *draw_manager, physics_manager_t *physics_manager);

typedef struct car
{
    game_object_t game_object;
}car_t;

void car_init(car_t *car, draw_manager_t *draw_manager, physics_manager_t *physics_manager);