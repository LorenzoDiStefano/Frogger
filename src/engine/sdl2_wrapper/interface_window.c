#include <engine/gfx/interface_window.h>
#include <stdlib.h>

void init_interface_window(interface_window_t* window)
{
	window->raw_data = NULL;
}

interface_window_t* create_interface_window(const char* title, int x, int y, int window_width, int window_height, uint32_t flags)
{
	//create window interface object and initilize to safe state
	interface_window_t* new_window = (interface_window_t*)malloc(sizeof(interface_window_t));
	init_interface_window(new_window);

	//create window with sdl
	void* dummy = SDL_CreateWindow(title, x, y, window_width, window_height, flags);
	new_window->raw_data = dummy;

	return new_window;
}
