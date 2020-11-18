#include <engine/gfx/interface_renderer.h>
#include <engine/gfx/interface_texture.h>
#include <engine/gfx/interface_window.h>
#include <stdlib.h>
#include <SDL.h>

void interface_renderer_set_draw_blend_mode(interface_renderer_t* renderer, uint32_t flags)
{
	SDL_SetRenderDrawBlendMode(renderer->raw_data, flags);
}

void interface_renderer_set_draw_color(interface_renderer_t* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(renderer->raw_data, r, g, b, a);
}

void interface_renderer_clear(interface_renderer_t* renderer)
{
	SDL_RenderClear(renderer->raw_data);
}

void interface_renderer_present(interface_renderer_t* renderer)
{
	SDL_RenderPresent(renderer->raw_data);
}

void interface_renderer_copy(interface_renderer_t* renderer, interface_texture_t* texture, SDL_Rect* sprite_rect)
{
	SDL_RenderCopy(renderer->raw_data, texture->raw_data, NULL, sprite_rect);
}

void init_interface_renderer(interface_renderer_t* renderer)
{
	renderer->raw_data = NULL;
	renderer->set_draw_blend_mode = interface_renderer_set_draw_blend_mode;
	renderer->clear = interface_renderer_clear;
	renderer->copy = interface_renderer_copy;
	renderer->set_draw_color = interface_renderer_set_draw_color;
	renderer->present = interface_renderer_present;
}

interface_renderer_t* create_interface_renderer(interface_window_t* window, int index, uint32_t flags)
{
	//create renderer interface object and initilize to safe state
	interface_renderer_t* new_renderer = (interface_renderer_t*)malloc(sizeof(interface_renderer_t));
	init_interface_renderer(new_renderer);

	//create renderer with sdl
	void* dummy = SDL_CreateRenderer(window->raw_data, index, flags);
	new_renderer->raw_data = dummy;

	return new_renderer;
}