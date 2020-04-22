#include "update_manager.h"

int update_manager_init(update_manager_t* update_manager)
{
	if (update_manager == NULL)
		return 1;

	update_manager->go_count = 0;
	update_manager->max_go = 100;

	return 0;
}

void update_manager_update(const update_manager_t *update_manager, const double delta_time)
{
	for (int i = 0; i < update_manager->go_count; i++)
	{
		game_object_t *game_object_address = update_manager->go[i];

		if (game_object_address->update == NULL)
			printf("null update");
		else
			game_object_address->update(game_object_address, delta_time);
	}
}

int update_manager_add_game_object(update_manager_t* update_manager, game_object_t* go)
{
	if (update_manager == NULL)
		return 1;

	update_manager->go[update_manager->go_count] = go;
	update_manager->go_count++;
	return 0;
}