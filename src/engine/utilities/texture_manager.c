#include <engine/utilities/texture_manager.h>

void texture_manager_init(texture_manager_t *tm)
{
	tm->stored_texture = 0;
    tm->renderer = NULL;
}

void texture_manager_set_renderer(texture_manager_t *tm, SDL_Renderer *renderer)
{
    tm->renderer = renderer;
}

//return index of texture
int texture_manager_load_texture(texture_manager_t* tm, const char* path)
{
    image_info_t *texture_inf = (image_info_t*)malloc(sizeof(image_info_t));
    load_image(texture_inf, path);
    load_texture(texture_inf, tm->renderer);
    tm->textures[tm->stored_texture] = *texture_inf;

	return tm->stored_texture++;
}