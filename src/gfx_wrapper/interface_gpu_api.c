#include <engine/gfx/interface_gpu_api.h>
#include <stdlib.h>
#include <SDL.h>

interface_window_t* interface_gpu_api_create_window(const char* title, int x, int y, int window_width, int window_height, uint32_t flags)
{
	//create window interface object and initilize to safe state
	interface_window_t* new_window = (interface_window_t*)malloc(sizeof(interface_window_t));
	init_interface_window(new_window);

	//create window with sdl
	void* dummy = SDL_CreateWindow("Game", 100, 100, window_width, window_height, flags);
	new_window->raw_data = dummy;

	return new_window;
}

interface_texture_t* interface_gpu_api_create_texture()
{
	return NULL;
}

interface_renderer_t* inteface_gpu_api_create_renderer(interface_window_t* window, int index, uint32_t flags)
{
	//create renderer interface object and initilize to safe state
	interface_renderer_t* new_renderer = (interface_renderer_t*)malloc(sizeof(interface_renderer_t));
	init_interface_renderer(new_renderer);

	//create renderer with sdl
	void* dummy = SDL_CreateRenderer(window->raw_data, index, flags);
	new_renderer->raw_data = dummy;

	return new_renderer;
}

//assigns dafulat functions to struct pointers to hide whats behind the api
void init_interface_gpu_api(interface_gpu_api_t *api)
{
	api->create_texture = interface_gpu_api_create_texture;
	api->create_window = interface_gpu_api_create_window;
	api->create_renderer = inteface_gpu_api_create_renderer;
}

