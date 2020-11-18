#ifndef FROGGER_INTERFACEWINDOW
#define FROGGER_INTERFACEWINDOW
#pragma once

typedef struct interface_window
{
	void* raw_data;
} interface_window_t;

void init_interface_window(interface_window_t* window);

#endif // !FROGGER_INTERFACEWINDOW