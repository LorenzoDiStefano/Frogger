#include <engine/gfx/interface_texture.h>
#include <engine/gfx/interface_renderer.h>
#include <stdlib.h>
#include <SDL.h>

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

void init_interface_texture(interface_texture_t* texture)
{
	texture->raw_data = NULL;
	texture->set_blend_mode = interface_texture_set_blend_mode;
	texture->unlock = interface_texture_unlock;
	texture->lock = interface_texture_lock;
}

interface_texture_t* create_interface_texture(interface_renderer_t* renderer, uint32_t format_flags, uint32_t access_flags, int width, int height)
{
	//create texrure interface object and initilize to safe state
	interface_texture_t* new_texture = (interface_texture_t*)malloc(sizeof(interface_texture_t));
	init_interface_texture(new_texture);

	//create texture with sdl
	void* dummy = SDL_CreateTexture(renderer->raw_data, format_flags, access_flags, width, height);
	new_texture->raw_data = dummy;

	return new_texture;
}
