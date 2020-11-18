#ifndef FROGGER_INTERFACEAPI
#define FROGGER_INTERFACEAPI
#pragma once

#include <engine/gfx/interface_window.h>
#include <engine/gfx/interface_texture.h>
#include <engine/gfx/interface_renderer.h>

struct interface_gpu_api
{
    interface_texture_t* (*create_texture)(interface_renderer_t* renderer, uint32_t format_flags, uint32_t access_flags, int width, int height);
    interface_renderer_t* (*create_renderer)(interface_window_t*, int, uint32_t);
    interface_window_t* (*create_window)(const char* title, int x, int y, int window_width, int window_height, uint32_t flags);
}typedef interface_gpu_api_t;

void init_interface_gpu_api(interface_gpu_api_t *api);

interface_texture_t* interface_gpu_api_create_texture(interface_renderer_t* renderer, uint32_t format_flags, uint32_t access_flags, int width, int height);
interface_renderer_t* inteface_gpu_api_create_renderer(interface_window_t* window, int index, uint32_t flags);
interface_window_t* interface_gpu_api_create_window(const char* title, int x, int y, int window_width, int window_height, uint32_t flags);

#endif // !FROGGER_INTERFACEAPI