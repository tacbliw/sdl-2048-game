#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>

// Game Libraries
#include "Font.h"

using namespace std;

int main( int argc, char * argv[] )
{
    bool quit = false;
    SDL_Event event;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window * window= SDL_CreateWindow("Test text", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    if (!window)
    {
        cout << "Error creating window: " << SDL_GetError() << endl;
        return 1;
    }


    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);
    if (!ren)
    {
        cout << "Error creating Renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        return 1;
    }

    // Tesing font


    // End testing font

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }

    font->free();
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
