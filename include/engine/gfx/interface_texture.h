#ifndef FROGGER_INTERFACETEXTURE
#define FROGGER_INTERFACETEXTURE
#pragma once

#include <stdint.h>

typedef struct interface_texture
{
	void* raw_data;

    void (*unlock)(struct interface_texture* texture);
    void (*set_blend_mode)(struct interface_texture* texture, uint32_t flags);
    int (*lock)(struct interface_texture* texture, void** pixels, int* pitch);
} interface_texture_t;

void init_interface_texture(interface_texture_t* texture);
void interface_texture_unlock(interface_texture_t* texture);
void interface_texture_set_blend_mode(interface_texture_t* texture, uint32_t flags);
int interface_texture_lock(interface_texture_t* texture, void** pixels, int* pitch);

#endif // !FROGGER_INTERFACETEXTURE
