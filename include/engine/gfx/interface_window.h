#ifndef FROGGER_INTERFACEWINDOW
#define FROGGER_INTERFACEWINDOW
#pragma once

#include <stdint.h>

typedef struct interface_window
{
	void* raw_data;

} interface_window_t;

void init_interface_window(interface_window_t* window);
interface_window_t* create_interface_window(const char* title, int x, int y, int window_width, int window_height, uint32_t flags);

#endif // !FROGGER_INTERFACEWINDOW