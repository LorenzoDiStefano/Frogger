// Frogger.cpp: definisce il punto di ingresso dell'applicazione.
//

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#include <SDL.h>
#endif

#include "engine/physics/vector2.h"

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("error %s", SDL_GetError());
		return 1;
	}
	vector2_t ab;
	vector2_mul(&ab,5.0);
	SDL_Rect a;
	a.h = 0;
	getchar();
}
