#ifndef FROGGER_UPDATEMANAGER
#define FROGGER_UPDATEMANAGER
#pragma once

struct game_object typedef game_object_t;

typedef struct update_manager
{
    game_object_t* go[100];
    int go_count;
    int max_go;

}update_manager_t;

void update_manager_update(const update_manager_t *physics_manager, const double delta_time);

int update_manager_init(update_manager_t *update_manager);
int update_manager_add_game_object(update_manager_t *physics_manager, game_object_t *go);

#endif // !FROGGER_UPDATEMANAGER