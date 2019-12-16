#ifndef FROGGER_BACKGROUND_HEADER
#define FROGGER_BACKGROUND_HEADER

typedef struct background
{
    game_object_t game_object;
}background_t;

void background_init(background_t *backgound, draw_manager_t *draw_manager, physics_manager_t *physics_manager, image_info_t *img_info);

#include "background.c"
#endif