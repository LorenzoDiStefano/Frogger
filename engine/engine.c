#include "engine.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"


int vector2_init(vector2_t *vector2)
{
    if(vector2==NULL)
        return 0;
    
    vector2->x = 0;
    vector2->y = 0;
    return 1;
}

int vector2_init_safe(vector2_t *vector2, float x,float y)
{
    if(vector2==NULL)
        return 0;
    
    vector2->x = x;
    vector2->y = y;
    return 1;
}

vector2_t vector2_add(vector2_t *first_value,vector2_t *second_value)
{
    vector2_t result;
    result.x = (first_value->x) + (second_value->x);
    result.y = (first_value->y) + (second_value->y);
    return result;
}

vector2_t vector2_sub(vector2_t *first_value,vector2_t *second_value)
{
    vector2_t result;
    result.x = (first_value->x) - (second_value->x);
    result.y = (first_value->y) - (second_value->y);
    return result;
}

vector2_t vector2_mul(vector2_t *first_value, double value)
{
    vector2_t result;

    result.x = first_value->x*value;
    result.y = first_value->y*value;

    return result;
}
vector2_t vector2_get_deep_copy(vector2_t *vector2)
{
    vector2_t result;

    result.x = vector2->x;
    result.y = vector2->y;

    return result;
}

#ifdef _TEST

static int test_vector2_init()
{
    vector2_t vector2;
    int ret_val = vector2_init(&vector2);
    return vector2.x == 0 && vector2.y == 0 && ret_val == 1;
}

static int test_vector2_init_safe()
{
    vector2_t vector2;
    int ret_val = vector2_init_safe(&vector2, 50, 70);
    return vector2.x == 50 && vector2.y == 70 && ret_val == 1;
}

static int test_vector2_add()
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_init_safe(&second_vector2, 50, 70);
    second_vector2 = vector2_add(&vector2, &second_vector2);
    return second_vector2.x == 100 && second_vector2.y == 140;
}

static int test_vector2_sub()
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_init_safe(&second_vector2, 50, 70);
    second_vector2 = vector2_sub(&vector2, &second_vector2);
    return second_vector2.x == 0 && second_vector2.y == 0;
}

static int test_vector2_deep_copy()
{
    vector2_t vector2;
    vector2_init_safe(&vector2, 50, 70);
    vector2_t second_vector2 = vector2_get_deep_copy(&vector2);
    return second_vector2.x == 50 && second_vector2.y == 70 &&
    &(second_vector2.y) != &(vector2.y) && &(second_vector2.x) != &(vector2.x);
}

static int test_vector2_mul()
{
    vector2_t second_vector2, vector2;
    vector2_init_safe(&vector2, 10, 2);
    second_vector2 = vector2_mul(&vector2, 4);
    return second_vector2.x == 40 && second_vector2.y == 8;
}

void test_vector2()
{
    RUN_TEST_VECTOR2(test_vector2_init);
    RUN_TEST_VECTOR2(test_vector2_init_safe);
    RUN_TEST_VECTOR2(test_vector2_add);
    RUN_TEST_VECTOR2(test_vector2_sub);
    RUN_TEST_VECTOR2(test_vector2_mul);
    RUN_TEST_VECTOR2(test_vector2_deep_copy);
}
#endif

void collision_info_init(collision_info_t *collision_info)
{
    collision_info->collider = NULL;
    vector2_init(&collision_info->delta);
}


#ifdef _TEST

static int test_collision_info_init()
{
    collision_info_t collision_info;
    collision_info_init(&collision_info);
    return collision_info.collider == NULL &&
    collision_info.delta.x == 0 &&
    collision_info.delta.y == 0;
}

void test_collision_info()
{
    RUN_TEST_COLLISION_INFO(test_collision_info_init);
}

#endif

void rect_init(rect_t* rect)
{
    rect->owner = malloc(300);;
    rect->height = 0;
    rect->width = 0;
    rect->half_height = 0;
    rect->half_width = 0;
    vector2_init(&rect->position);
}

void rect_init_safe(rect_t* rect, int width, int height, vector2_t position, void *owner)
{
    rect->owner = owner;
    rect->height = height;
    rect->width = width;
    rect->half_height = (float)height/2;
    rect->half_width = (float)width/2;
    rect->position = vector2_get_deep_copy(&position);
}

void rect_set_size(rect_t* rect, int width, int height)
{
    rect->height = height;
    rect->width = width;
    rect->half_height = (float)height/2;
    rect->half_width = (float)width/2;
}

void rect_set_position(rect_t* rect, vector2_t new_position)
{
    rect_set_position_x(rect, new_position.x);
    rect_set_position_y(rect, new_position.y);
}

void rect_set_position_x(rect_t *rect, float new_position_x)
{
    rect->position.x=new_position_x;
}

void rect_set_position_y(rect_t *rect, float new_position_y)
{
    rect->position.y=new_position_y;
}

//TODO:, return collision info instead of int, for now, return -1 on non collision, 1 on collision
int rect_check_collision(rect_t *first_rect, rect_t *second_rect, collision_info_t *collision)
{
    if(first_rect->position.x < second_rect->position.x + second_rect->width &&
        first_rect->position.x + first_rect->width > second_rect->position.x &&
        first_rect->position.y < second_rect->position.y + second_rect->height &&
        first_rect->position.y + first_rect->height > second_rect ->position.y)
    {
        float x=0,y=0;
        if(first_rect->position.x < second_rect->position.x)
            x = (first_rect->position.x + first_rect->width) - second_rect->position.x;
        else
            x = ((first_rect->position.x) - (second_rect->position.x+ second_rect->width));

        if(first_rect->position.y < second_rect->position.y)
            y = (first_rect->position.y + first_rect->height) - second_rect->position.y;
        else
            y = ((first_rect->position.y) - (second_rect->position.y+ second_rect->height));

        vector2_init_safe(&collision->delta,x,y);
        collision->collider= (void*)second_rect->owner;
        return 1;
    }

    return -1;
}


#ifdef _TEST

static int test_rect_init()
{
    rect_t rect;
    rect_init(&rect);
    return rect.owner == NULL &&
    rect.height == 0 &&
    rect.width == 0 &&
    rect.half_height == 0 &&
    rect.half_width == 0 &&
    rect.position.x == 0 &&
    rect.position.y == 0;
}

static int test_rect_init_safe()
{
    rect_t rect;
    game_object_t owner;
    vector2_t position;
    vector2_init_safe(&position,20,30);
    rect_init_safe(&rect, 100, 50, position, &owner);

    return rect.owner == &owner &&
    rect.width == 100 &&
    rect.height == 50 &&
    rect.half_width == 50 &&
    rect.half_height == 25 &&
    rect.position.x == 20 &&
    rect.position.y == 30;
}

static int test_rect_set_position()
{
    rect_t rect;
    vector2_t new_position;
    vector2_init_safe(&new_position, 100, 50);
    rect_set_position(&rect,new_position);
    return rect.position.x == 100 && rect.position.y == 50;
}

static int test_rect_set_position_x()
{
    rect_t rect;
    rect_init(&rect);
    rect_set_position_x(&rect, 100);
    return rect.position.x == 100 && rect.position.y == 0;
}

static int test_rect_set_position_y()
{
    rect_t rect;
    rect_init(&rect);
    rect_set_position_y(&rect, 100);
    return rect.position.x == 0 && rect.position.y == 100;
}

static int test_rect_collision_successful()
{
    rect_t first_rect, second_rect;
    collision_info_t collisio_info;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&second_rect, 50, 50, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect, &collisio_info);
    return collision == 1;
}

static int test_rect_collision_failed()
{
    rect_t first_rect, second_rect;
    collision_info_t collisio_info;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 51, 30);
    rect_init_safe(&second_rect, 5, 5, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect, &collisio_info);
    return collision == -1;
}

void test_rect()
{
    RUN_TEST_RECT(test_rect_init);
    RUN_TEST_RECT(test_rect_init_safe);
    RUN_TEST_RECT(test_rect_set_position);
    RUN_TEST_RECT(test_rect_set_position_x);
    RUN_TEST_RECT(test_rect_set_position_y);
    RUN_TEST_RECT(test_rect_collision_successful);
    RUN_TEST_RECT(test_rect_collision_failed);
}

#endif

void load_texture(image_info_t *img_info, SDL_Renderer *renderer)
{
    SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, img_info->width, img_info->height);
    if(!texture)
        printf("error");

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    Uint8 *pixels = NULL;
    int pitch = 0;
    if (SDL_LockTexture(texture, NULL, (void **)&pixels, &pitch))
    {
        printf("Unable to map texture into address space");
    }
    memcpy(pixels, (void *)img_info->image, img_info->height *4* img_info->width);

    SDL_UnlockTexture(texture);
    //free(img_info->image); //img info is not in the heap but image is
    img_info->texture = texture;
    return;
}

void init_sprite(sprite_t *sprite, image_info_t *img_info, SDL_Renderer *renderer, float scale)
{
    sprite->texture = img_info->texture;
    sprite->scale = scale;
    sprite->sprite_rect.w = img_info->width * scale;
    sprite->sprite_rect.h = img_info->height * scale;
    sprite->sprite_rect.x = 0;
    sprite->sprite_rect.y = 0;
    sprite->renderer = renderer;
}

void draw_scene(draw_manager_t *draw_manager)
{
    SDL_SetRenderDrawColor(draw_manager->renderer, 67, 33, 33, 255);
    SDL_RenderClear(draw_manager->renderer);

    for (int i = 0; i < draw_manager->bg_sprites_to_draw; i++)
    {
        sprite_t *sprite_address = draw_manager->bg_sprites[i];
        SDL_RenderCopy(draw_manager->renderer, sprite_address->texture, NULL, &sprite_address->sprite_rect);
    }

    for (int i = 0; i < draw_manager->sprites_to_draw; i++)
    {
        sprite_t *sprite_address = draw_manager->sprites[i];
        SDL_RenderCopy(draw_manager->renderer, sprite_address->texture, NULL, &sprite_address->sprite_rect);
    }
    
    SDL_RenderPresent(draw_manager->renderer);
}

void draw_manager_add_sprite(draw_manager_t *draw_manager, sprite_t *sprite)
{
    draw_manager->sprites[draw_manager->sprites_to_draw] = sprite;
    draw_manager->sprites_to_draw++;
}

void draw_manager_add_sprite_bg(draw_manager_t *draw_manager, sprite_t *sprite)
{
    draw_manager->bg_sprites[draw_manager->bg_sprites_to_draw] = sprite;
    draw_manager->bg_sprites_to_draw++;
}

int draw_manager_init(draw_manager_t* draw_manager)
{
    draw_manager->window = SDL_CreateWindow("Game", 100, 100 ,WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if(!draw_manager->window)
    {
        return -1;
    }

    draw_manager->renderer = SDL_CreateRenderer(draw_manager->window, -1,SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);

    if(!draw_manager->renderer)
    {
        return -1;
    }

    draw_manager->draw_scene = draw_scene;
    SDL_SetRenderDrawBlendMode(draw_manager->renderer, SDL_BLENDMODE_BLEND);

    draw_manager->max_sprites = 100;
    draw_manager->sprites_to_draw = 0;
    draw_manager->sprites = malloc(100*sizeof(sprite_t));

    draw_manager->bg_max_sprites = 100;
    draw_manager->bg_sprites_to_draw = 0;
    draw_manager->bg_sprites = malloc(100*sizeof(sprite_t));

    return 0;
}

int load_image(image_info_t *img, const char* path)
{
    int width, height, comp;
    unsigned char* image;
    image = stbi_load(path, &width, &height, &comp, STBI_rgb_alpha);

    //checking if loading was successfull
    SDL_Log("Loading img: %s",path);
    if (!image)
    {
        SDL_Log("Error loading img: %s",path);
        return 1;
    }

    img->image = image;
    img->width = width;
    img->height = height; 
    img->comp = comp;
    img->length = width*height;

    return 0;
}

#ifdef _TEST

static int test_draw_manager_init()
{
    draw_manager_t draw_manager;
    
    int return_value = draw_manager_init(&draw_manager);
    return !return_value &&
    draw_manager.max_sprites == 100 &&
    draw_manager.sprites_to_draw == 0;
}

void test_draw_manager()
{
    RUN_TEST_DRAW_MANAGER(test_draw_manager_init);
}

#endif

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
        game_object->sprite->sprite_rect.x = (int)game_object->position.x;
        game_object->sprite->sprite_rect.y = (int)game_object->position.y;
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

void player_on_collision(struct game_object *game_object, collision_info_t *collision)
{
    game_object_t *collider = (game_object_t *)collision->collider;
    //printf("player collided with %d \n", collider->collider_type);
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
        double frame_time = (double)1000/fps;
        vector2_t movement = vector2_mul(&collider->velocity, frame_time*0.001);
        game_object->position = vector2_add(&game_object->position, &movement);
    }
}

void player_die(player_t *player)
{
    printf("Player died\n");
    player->game_object.position.x = player->spawn_point.x;
    player->game_object.position.y = player->spawn_point.y;
}

void game_object_player_update(game_object_t *game_object,const double delta_time)
{
    game_object_update(game_object,delta_time);

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
        game_object->sprite->sprite_rect.x = (int)game_object->position.x;
        game_object->sprite->sprite_rect.y = (int)game_object->position.y;
    }

    ((player_t *)game_object)->is_on_log = 0;

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

void physics_manager_init(physics_manager_t *physics_manager)
{
    physics_manager->max_rects = 100;
    physics_manager->player = NULL;
    physics_manager->rects_to_draw = 0;
}

void physics_manager_update(physics_manager_t *physics_manager, const double delta_time)
{
    if(physics_manager->player==NULL)
    {
        printf("missing player\n");
        return;
    }

    //update player
    game_object_t *player_game_object = ((game_object_t *)physics_manager->player->owner);
    player_game_object->update(player_game_object, delta_time);

    for (int i = 0; i < physics_manager->rects_to_draw; i++)
    {
        game_object_t *game_object_address = physics_manager->rects[i]->owner;

        if(game_object_address->update == NULL)
            printf("null update");
        game_object_address->update(game_object_address, delta_time);
    } 
}

void physics_manager_add_rect(physics_manager_t *physics_manager, rect_t *rect)
{
    physics_manager->rects[physics_manager->rects_to_draw] = rect;
    physics_manager->rects_to_draw++;
}

void physics_manager_add_player(physics_manager_t *physics_manager, rect_t *rect)
{
    physics_manager->player = rect;
}

void physics_manager_check_collisions(physics_manager_t *physics_manager)
{
    if(physics_manager->player == NULL)
        return;

    for (int i = 0; i < physics_manager->rects_to_draw; i++)
    {
        collision_info_t collision;
        collision_info_init(&collision);
        if(rect_check_collision(physics_manager->player, physics_manager->rects[i] ,&collision) == 1)
        {
            game_object_t *player_game_object = physics_manager->player->owner;
            player_game_object->on_collision(player_game_object, &collision);
        }     
    } 
}

void game_object_car_update(game_object_t *game_object, const double delta_time)
{
    game_object_update(game_object, delta_time);
    //printf("override");
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

    //temporary, waiting for art
    car->game_object.sprite->sprite_rect.h = TILE_SIZE;
    car->game_object.sprite->sprite_rect.w = TILE_SIZE;
    rect_set_size(&car->game_object.bounding_box, TILE_SIZE, TILE_SIZE);

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
