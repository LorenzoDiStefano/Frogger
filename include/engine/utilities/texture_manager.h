#ifndef FROGGER_TEXTUREMANAGER
#define FROGGER_TEXTUREMANAGER
#pragma once

#include <engine/utilities/image_info.h>
#include <engine/gfx/interface_renderer.h>

//temporary, should use dynamic array
#define TM_MAX_TEXTURES 100

typedef struct texture_manager
{
	interface_renderer_t* renderer;
	int stored_texture;
	image_info_t textures[TM_MAX_TEXTURES];
}texture_manager_t;

void texture_manager_init(texture_manager_t *tm);
void texture_manager_set_renderer(texture_manager_t* tm, interface_renderer_t* renderer);

//return index of loaded texture
int texture_manager_load_texture(texture_manager_t *tm, const char* path);

#endif // !FROGGER_TEXTUREMANAGER