#ifndef FROGGER_INTERFACERENDERER
#define FROGGER_INTERFACERENDERER
#pragma once

#include <stdint.h>
#include <SDL.h>

typedef struct interface_renderer
{
	void* raw_data;

	void (*set_draw_blend_mode)(struct interface_renderer* renderer ,uint32_t flags);
	void (*set_draw_color)(struct interface_renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void (*clear)(struct interface_renderer* renderer);
	void (*present)(struct interface_renderer* renderer);
	void (*copy)(struct interface_renderer* renderer, SDL_Texture* texture, SDL_Rect* sprite_rect);

} interface_renderer_t;

void init_interface_renderer(interface_renderer_t* renderer);
void interface_renderer_set_draw_blend_mode(interface_renderer_t* renderer, uint32_t flags);
void interface_renderer_set_draw_color(interface_renderer_t* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void interface_renderer_clear(interface_renderer_t* renderer);
void interface_renderer_present(interface_renderer_t* renderer);
void interface_renderer_copy(interface_renderer_t* renderer, SDL_Texture* texture, SDL_Rect* sprite_rect);

#endif // !FROGGER_INTERFACERENDERER
