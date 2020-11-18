#include <engine/gfx/interface_texture.h>
#include <stdlib.h>
#include <SDL.h>

void init_interface_texture(interface_texture_t* texture)
{
	texture->raw_data = NULL;
	texture->set_blend_mode = interface_texture_set_blend_mode;
	texture->unlock = interface_texture_unlock;
	texture->lock = interface_texture_lock;
}

void interface_texture_unlock(interface_texture_t* texture)
{
	SDL_UnlockTexture(texture->raw_data);
}

void interface_texture_set_blend_mode(interface_texture_t* texture, uint32_t flags)
{
	SDL_SetTextureBlendMode(texture->raw_data, flags);
}

int interface_texture_lock(interface_texture_t* texture, void** pixels, int* pitch)
{
	return SDL_LockTexture(texture->raw_data, NULL, pixels, pitch);
}
