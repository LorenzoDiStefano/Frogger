#include <engine/gfx/interface_gpu_api.h>
#include <stdlib.h>
#include <SDL.h>

interface_window_t* interface_gpu_api_create_window(const char* title, int x, int y, int window_width, int window_height, uint32_t flags)
{
	//create window interface object and initilize to safe state
	interface_window_t* new_window = (interface_window_t*)malloc(sizeof(interface_window_t));
	init_interface_window(new_window);

	//temporary for shutting up the compiler
	if (new_window == NULL)
	{
		exit(1);
	}

	//create window with sdl
	void* dummy = SDL_CreateWindow("Game", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
	new_window->raw_data = dummy;

	return new_window;
}

interface_texture_t* interface_gpu_api_create_texture()
{
	return NULL;
}

//assigns dafulat functions to struct pointers to hide whats behind the api
void init_interface_gpu_api(interface_gpu_api_t *api)
{
	api->create_texture = interface_gpu_api_create_texture;
	api->create_window = interface_gpu_api_create_window;
}

