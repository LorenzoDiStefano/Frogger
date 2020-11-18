#include <engine/gfx/sprite.h>
#include <engine/utilities/image_info.h>

void sprite_init(sprite_t *sprite, image_info_t *img_info, interface_renderer_t *renderer, const float scale)
{
    sprite->texture = img_info->texture;
    sprite->scale = scale;
    sprite->sprite_rect.w = img_info->width;
    sprite->sprite_rect.h = img_info->height;
    sprite->sprite_rect.x = 0;
    sprite->sprite_rect.y = 0;
    sprite->renderer = renderer;
}
