#include "SDLUtils.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>

extern const int  SCREEN_WIDTH = 700;
extern const int SCREEN_HEIGHT = 640;

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;

bool InitSDL()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL died with error: %s\n", SDL_GetError());
    }
    else
    {
        /*
            linear filltering
        */
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Linear texture filtering not enable, so what ?...\n");
        }

        g_window = SDL_CreateWindow(
                                    "2048",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN
                                    );
        if (g_window == NULL)
        {
            printf("could not create window with error%s\n", SDL_GetError());
            success = false;
        }
        else
        {
            g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (g_renderer == NULL)
            {
                printf("could not create renderer with error: %s\n", SDL_GetError());
            }
            //g_render.init(g_renderer);
            int iFlags = IMG_INIT_PNG;
            if (!IMG_Init(iFlags) & iFlags)
            {
                printf("sdl_image could not initialize, you did this, damn. error: %s\n", SDL_GetError());
                success = false;
            }

            if (TTF_Init() == -1)
            {
                printf("sdl_tff could not initialize, download and put it in the right place... error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}

void CloseSDL()
{
    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
