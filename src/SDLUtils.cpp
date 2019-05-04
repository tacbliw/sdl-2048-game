#include "SDLUtils.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Render.h"
#include <stdio.h>

extern const int  SCREEN_WIDTH = 700;
extern const int SCREEN_HEIGHT = 640;

static SDL_Window *gWindow = NULL;
static SDL_Renderer *gRenderer = NULL;

/** @brief Standard SDL initialization.
 *
 * @return bool
 *
 */
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

        gWindow = SDL_CreateWindow(
                                    "2048",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN
                                    );
        if (gWindow == NULL)
        {
            printf("could not create window with error%s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("could not create renderer with error: %s\n", SDL_GetError());
            }
            gRender.setRenderer(gRenderer);
            int iFlags = IMG_INIT_PNG;
            if (!IMG_Init(iFlags) & iFlags)
            {
                printf("sdl_image could not initialize, you did this, damn. error: %s\n", SDL_GetError());
                success = false;
            }

            if (TTF_Init() == -1)
            {
                printf("sdl_tff could not initialize, download and put it in the right place... error: %s\n",
                       SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}

/** @brief Standard SDL destruction.
 *
 * @return bool
 *
 */
void CloseSDL()
{
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
