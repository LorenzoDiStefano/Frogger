#include <engine/gfx/interface_renderer.h>
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

void interface_renderer_copy(interface_renderer_t* renderer, SDL_Texture* texture, SDL_Rect* sprite_rect)
{
	SDL_RenderCopy(renderer->raw_data, texture, NULL, sprite_rect);
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
