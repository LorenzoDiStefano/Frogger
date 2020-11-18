#ifndef FROGGER_INTERFACETEXTURE
#define FROGGER_INTERFACETEXTURE
#pragma once

#include <stdint.h>

struct interface_renderer typedef interface_renderer_t;

typedef struct interface_texture
{
	void* raw_data;

    void (*unlock)(struct interface_texture* texture);
    void (*set_blend_mode)(struct interface_texture* texture, uint32_t flags);
    int (*lock)(struct interface_texture* texture, void** pixels, int* pitch);

} interface_texture_t;

void init_interface_texture(interface_texture_t* texture);
interface_texture_t* create_interface_texture(interface_renderer_t* renderer, uint32_t format_flags, 
                                                uint32_t access_flags, int width, int height);

#endif // !FROGGER_INTERFACETEXTURE
