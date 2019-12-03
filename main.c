#define SDL_MAIN_HANDLED
#include <SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int crash()
{
    SDL_Log("window error %s",SDL_GetError());
    SDL_Quit();
    getchar();
    return 1;
}

int end()
{
    SDL_Quit();
    return 0;
}

int main (int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO))
    {
        SDL_Log("error %s",SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Game",100,100,640,480,SDL_WINDOW_SHOWN);

    if(!window)
    {
        return crash();
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);

    if(!renderer)
    {
        return crash();
    }

    for(;;)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                return end();
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    return 0;
}


