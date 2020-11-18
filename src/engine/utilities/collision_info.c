#include <engine/utilities/collision_info.h>
#include <stdlib.h>

void collision_info_init(collision_info_t *collision_info)
{
    collision_info->collider = NULL;
    vector2_init(&collision_info->delta);
}