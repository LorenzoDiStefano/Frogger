#pragma once
#include "gfx/image_info.h"

//temporary, should use dynamic array/dictionary
#define TM_MAX_TEXTURES 100

typedef struct texture_manager
{
	SDL_Renderer* renderer;
	int stored_texture;
	image_info_t textures[TM_MAX_TEXTURES];
}texture_manager_t;

void texture_manager_init(texture_manager_t *tm);
void texture_manager_set_renderer(texture_manager_t* tm, SDL_Renderer* renderer);
//return index of texture
int texture_manager_load_texture(texture_manager_t *tm, const char* path);