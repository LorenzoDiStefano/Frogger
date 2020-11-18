#ifndef FROGGER_INTERFACERENDERER
#define FROGGER_INTERFACERENDERER
#pragma once

#include <stdint.h>

struct interface_texture typedef interface_texture_t;
struct interface_window typedef interface_window_t;
struct SDL_Rect typedef SDL_Rect;

typedef struct interface_renderer
{
	void* raw_data;

	void (*set_draw_blend_mode)(struct interface_renderer* renderer ,uint32_t flags);
	void (*set_draw_color)(struct interface_renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void (*clear)(struct interface_renderer* renderer);
	void (*present)(struct interface_renderer* renderer);
	void (*copy)(struct interface_renderer* renderer, interface_texture_t* texture, SDL_Rect* sprite_rect);

} interface_renderer_t;

void init_interface_renderer(interface_renderer_t* renderer);
interface_renderer_t* create_interface_renderer(interface_window_t* window, int index, uint32_t flags);

#endif // !FROGGER_INTERFACERENDERER
