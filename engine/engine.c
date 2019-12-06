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

static int test_init(vector2_t *vector2)
{
    int ret_val = vector2_init(vector2);
    return vector2->x == 0 && vector2->y == 0 && ret_val == 1;
}

static int test_init_safe(vector2_t *vector2)
{
    int ret_val = vector2_init_safe(vector2, 50, 70);
    return vector2->x == 50 && vector2->y == 70 && ret_val == 1;
}

static int test_add(vector2_t *vector2)
{
    vector2_t second_vector2;
    vector2_init_safe(vector2, 50, 70);
    vector2_init_safe(&second_vector2, 50, 70);
    second_vector2 = vector2_add(vector2, &second_vector2);
    return second_vector2.x == 100 && second_vector2.y == 140;
}

static int test_sub(vector2_t *vector2)
{
    vector2_t second_vector2;
    vector2_init_safe(vector2, 50, 70);
    vector2_init_safe(&second_vector2, 50, 70);
    second_vector2= vector2_sub(vector2, &second_vector2);
    return second_vector2.x == 0 && second_vector2.y == 0;
}

static int test_deep_copy(vector2_t *vector2)
{
    vector2_init_safe(vector2, 50, 70);
    vector2_t second_vector2 = vector2_get_deep_copy(vector2);
    return second_vector2.x == 50 && second_vector2.y==70 &&
    &(second_vector2.y) != &(vector2->y) && &(second_vector2.x) != &(vector2->x);
}

static int test_mul(vector2_t *vector2)
{
    vector2_t second_vector2;
    vector2_init_safe(vector2, 10, 2);
    second_vector2= vector2_mul(vector2, 4);
    return second_vector2.x == 40 && second_vector2.y == 8;
}

void test_vector2()
{
    RUN_TEST_VECTOR2(test_init);
    RUN_TEST_VECTOR2(test_init_safe);
    RUN_TEST_VECTOR2(test_add);
    RUN_TEST_VECTOR2(test_sub);
    RUN_TEST_VECTOR2(test_mul);
    RUN_TEST_VECTOR2(test_deep_copy);
}
#endif

void collision_info_init(collision_info_t *collision_info)
{
    collision_info->collider = NULL;
    vector2_init(&collision_info->delta);
}


#ifdef _TEST

static int test_collision_info_init(collision_info_t *collision_info)
{
    collision_info_init(collision_info);
    return collision_info->collider == NULL &&
    collision_info->delta.x == 0 &&
    collision_info->delta.y == 0;
}

void test_collision_info()
{
    RUN_TEST_COLLISION_INFO(test_collision_info_init);
}

#endif

void rect_init(rect_t* rect)
{
    rect->owner = NULL;
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

        if(x>y)
            y=0;
        else
            x=0;
        vector2_init_safe(&collision->delta,x,y);
        return 1;
    }

    //printf("first rect x:%f y:%f w:%d h:%d\n",first_rect->position.x,first_rect->position.y,first_rect->width,first_rect->height);
    //printf("first rect x:%f y:%f w:%d h:%d\n",second_rect->position.x,second_rect->position.y,second_rect->width,second_rect->height);
    return -1;
}


#ifdef _TEST

static int test_rect_init(rect_t *rect)
{
    rect_init(rect);
    return rect->owner == NULL &&
    rect->height == 0 &&
    rect->width == 0 &&
    rect->half_height == 0 &&
    rect->half_width == 0 &&
    rect->position.x == 0 &&
    rect->position.y == 0;
}

static int test_rect_init_safe(rect_t *rect)
{
    game_object_t owner;
    vector2_t position;
    vector2_init_safe(&position,20,30);
    rect_init_safe(rect, 100, 50, position, &owner);

    return rect->owner == &owner &&
    rect->width == 100 &&
    rect->height == 50 &&
    rect->half_width == 50 &&
    rect->half_height == 25 &&
    rect->position.x == 20 &&
    rect->position.y == 30;
}

static int test_rect_set_position(rect_t *rect)
{
    vector2_t new_position;
    vector2_init_safe(&new_position, 100, 50);
    rect_set_position(rect,new_position);
    return rect->position.x == 100 && rect->position.y == 50;
}

static int test_rect_set_position_x(rect_t *rect)
{
    rect_set_position_x(rect, 100);
    return rect->position.x == 100 && rect->position.y == 0;
}

static int test_rect_set_position_y(rect_t *rect)
{
    rect_set_position_y(rect, 100);
    return rect->position.x == 0 && rect->position.y == 100;
}

static int test_rect_collision_successful(rect_t *rect)
{
    rect_t first_rect, second_rect;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&second_rect, 50, 50, position, NULL);

    rect_init_safe(rect, 100, 50, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect);
    return collision == 1;
}

static int test_rect_collision_failed(rect_t *rect)
{
    rect_t first_rect, second_rect;
    vector2_t position;

    vector2_init(&position);
    rect_init_safe(&first_rect, 50, 50, position, NULL);

    vector2_init_safe(&position, 20, 30);
    rect_init_safe(&second_rect, 5, 5, position, NULL);

    rect_init_safe(rect, 100, 50, position, NULL);

    int collision = rect_check_collision(&first_rect, &second_rect);
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

void init_sprite(sprite_t *sprite, image_info_t img_info, SDL_Renderer *renderer, float scale)
{
    sprite->texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, img_info.width, img_info.height);
    sprite->scale = scale;
    sprite->sprite_rect.w = img_info.width*scale;
    sprite->sprite_rect.h = img_info.height*scale;
    sprite->sprite_rect.x = 0;
    sprite->sprite_rect.y = 0;

    SDL_SetTextureBlendMode(sprite->texture, SDL_BLENDMODE_BLEND);

    Uint8 *pixels = NULL;
    int pitch = 0;
    SDL_LockTexture(sprite->texture, NULL, (void **)&pixels, &pitch);

    memcpy(pixels, img_info.image, pitch * img_info.width);

    //free(img_info.image); //img info is not in the heap

    SDL_UnlockTexture(sprite->texture);
    sprite->renderer = renderer;
}

void draw_scene(draw_manager_t *draw_manager)
{
    SDL_SetRenderDrawColor(draw_manager->renderer, 67, 33, 33, 255);
    SDL_RenderClear(draw_manager->renderer);

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

int draw_manager_init(draw_manager_t* draw_manager)
{
    draw_manager->window = SDL_CreateWindow("Game",100,100,640,480,SDL_WINDOW_SHOWN);

    if(!draw_manager->window)
    {
        return -1;
    }

    draw_manager->renderer = SDL_CreateRenderer(draw_manager->window,-1,SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);

    if(!draw_manager->renderer)
    {
        return -1;
    }

    draw_manager->draw_scene = draw_scene;
    SDL_SetRenderDrawBlendMode(draw_manager->renderer, SDL_BLENDMODE_BLEND);

    draw_manager->max_sprites = 100;
    draw_manager->sprites_to_draw = 0;
    draw_manager->sprites = malloc(100*sizeof(sprite_t));

    return 0;
}

int load_image(image_info_t *img,const char* path)
{
    int width, height, comp;
    unsigned char* image;
    image = stbi_load(path, &width, &height, &comp, STBI_rgb_alpha);

    //checking if loading was successfull
    SDL_Log("Loading img: %s",path);
    if (!image)
    {
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

static int test_draw_manager_init(draw_manager_t *draw_manager)
{
    int return_value = draw_manager_init(draw_manager);
    return !return_value &&
    draw_manager->max_sprites == 100 &&
    draw_manager->sprites_to_draw == 0;
}

void test_draw_manager()
{
    RUN_TEST_DRAW_MANAGER(test_draw_manager_init);
}

#endif

void game_object_init(game_object_t *game_object)
{
    //rect_init(&game_object->bounding_box);
    vector2_init(&(game_object->position));
    vector2_init(&(game_object->velocity));
    game_object->is_active = 0;
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
    game_object->sprite = NULL;
}

void game_object_update(game_object_t *game_object, double delta_time)
{
    if(!game_object->is_active)
        return;

    game_object->position.x+=game_object->velocity.x*delta_time;
    game_object->position.y+=game_object->velocity.y*delta_time;

    game_object->bounding_box.position.x = (int)game_object->position.x;
    game_object->bounding_box.position.y = (int)game_object->position.y;      

    if(game_object->sprite != NULL)
    {
        game_object->sprite->sprite_rect.x = (int)game_object->position.x;
        game_object->sprite->sprite_rect.y = (int)game_object->position.y;
    }

}

void game_object_set_position(game_object_t *game_object, vector2_t new_position)
{
    game_object_set_position_x(game_object,new_position.x);
    game_object_set_position_y(game_object,new_position.y);
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
    game_object_set_velocity_x(game_object,new_velocity.x);
    game_object_set_velocity_y(game_object,new_velocity.y);
}

void game_object_set_velocity_x(game_object_t *game_object, float new_velocity_x)
{
    game_object->velocity.x=new_velocity_x;
}

void game_object_set_velocity_y(game_object_t *game_object, float new_velocity_y)
{
    game_object->velocity.y=new_velocity_y;
}

void game_object_set_sprite(game_object_t *game_object, sprite_t *sprite)
{
    game_object->sprite = sprite;
}

#ifdef _TEST

static int test_game_object_init(game_object_t *game_object)
{
    game_object_init(game_object);
    return game_object->position.x == 0 && game_object->velocity.y == 0;
}

static int test_game_object_init_with_vectors(game_object_t *game_object)
{
    vector2_t position,velocity;
    vector2_init_safe(&position,100,100);
    vector2_init_safe(&velocity,50,50);

    game_object_init_with_vectors(game_object,&position,&velocity);
    
    return game_object->position.x < 100.001 && game_object->position.x > 99.999 &&
    game_object->position.y < 100.001 && game_object->position.y > 99.999 &&
    game_object->velocity.x < 50.001 && game_object->velocity.x > 49.999 &&
    game_object->velocity.y <= 50.001 && game_object->velocity.y >= 49.999 ;

}

static int test_game_object_update(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_update(game_object,1);
    return game_object->position.x == 0 && game_object->position.y == 0;
}

static int test_game_object_update_moving(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_velocity_x(game_object,5);
    game_object_update(game_object,1);
    return game_object->position.x == 5 && game_object->position.y == 0;
}

static int test_game_object_set_velocity_x(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_velocity_x(game_object,1);
    return game_object->velocity.x == 1 && game_object->velocity.y == 0;
}

static int test_game_object_set_velocity_y(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_velocity_y(game_object,1);
    return game_object->velocity.x == 0 && game_object->velocity.y == 1;
}

static int test_game_object_set_velocity(game_object_t *game_object)
{
    vector2_t new_velocity;
    vector2_init_safe(&new_velocity,50,40);
    game_object_init(game_object);
    game_object_set_velocity(game_object,new_velocity);
    return game_object->velocity.x == 50 && game_object->velocity.y == 40;
}

static int test_game_object_set_position_x(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_position_x(game_object,1);
    return game_object->position.x == 1 && game_object->position.y == 0;
}

static int test_game_object_set_position_y(game_object_t *game_object)
{
    game_object_init(game_object);
    game_object_set_position_y(game_object,1);
    return game_object->position.x == 0 && game_object->position.y == 1;
}

static int test_game_object_set_position(game_object_t *game_object)
{
    vector2_t new_position;
    vector2_init_safe(&new_position,50,40);
    game_object_init(game_object);
    game_object_set_position(game_object,new_position);
    return game_object->position.x == 50 && game_object->position.y == 40;
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
void player_init(player_t *player, draw_manager_t *draw_manager)
{
    game_object_init(&player->game_object);
    sprite_t *sprite=malloc(sizeof(sprite_t));
    image_info_t img_inf;
    load_image(&img_inf,"assets/frog.png");
    init_sprite(sprite, img_inf, draw_manager->renderer,1);
    draw_manager_add_sprite(draw_manager, sprite);
    vector2_t position,velocity;
    vector2_init_safe(&position,100,100);
    vector2_init_safe(&velocity,0,0);
    
    game_object_init_with_vectors(&player->game_object, &position, &velocity);
    game_object_set_sprite(&player->game_object,sprite);

    rect_set_size(&player->game_object.bounding_box,player->game_object.sprite->sprite_rect.w,player->game_object.sprite->sprite_rect.h);
    /*printf("created bounding box w:%d h:%d hw:%f",player->game_object.bounding_box.width,player->game_object.bounding_box.height,
    player->game_object.bounding_box.half_width);*/

    player->game_object.is_active = 1;
}
    

void player_read_input(player_t *player)
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    vector2_init(&player->game_object.velocity);

    if(keystates[SDL_SCANCODE_LEFT])
        player->game_object.velocity.x--;
    if(keystates[SDL_SCANCODE_RIGHT])
        player->game_object.velocity.x++;
    if(keystates[SDL_SCANCODE_UP])
        player->game_object.velocity.y--;
    if(keystates[SDL_SCANCODE_DOWN])
        player->game_object.velocity.y++;            

    player->game_object.velocity = vector2_mul(&player->game_object.velocity,(double)100);
    game_object_set_velocity(&player->game_object, player->game_object.velocity);
}

void wall_init(wall_t *wall, draw_manager_t *draw_manager)
{
    game_object_init(&wall->game_object);
    sprite_t *sprite=malloc(sizeof(sprite_t));
    image_info_t img_inf;
    load_image(&img_inf,"assets/ph_wall.png");
    init_sprite(sprite, img_inf, draw_manager->renderer,1);
    draw_manager_add_sprite(draw_manager, sprite);
    vector2_t position,velocity;
    vector2_init_safe(&position,0,0);
    vector2_init_safe(&velocity,0,0);
    
    game_object_init_with_vectors(&wall->game_object, &position, &velocity);
    game_object_set_sprite(&wall->game_object,sprite);

    sprite->sprite_rect.h=500;
    sprite->sprite_rect.w=50;
    //rect_set_size(&wall->game_object.bounding_box,wall->game_object.sprite->sprite_rect.w,wall->game_object.sprite->sprite_rect.h);
    rect_set_size(&wall->game_object.bounding_box,50,500);
    //printf("created bounding box w:%d h:%d ",wall->game_object.bounding_box.width,wall->game_object.bounding_box.height);
    wall->game_object.is_active = 1;
}