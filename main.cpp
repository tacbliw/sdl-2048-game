#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>

// Game Libraries
#include "Font.h"
#include "Window.h"

using namespace std;

int main( int argc, char * argv[] )
{
    bool quit = false;
    SDL_Event event;

    Window window("Testing", 800, 600);

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
    SDL_Quit();
    return 0;
}
