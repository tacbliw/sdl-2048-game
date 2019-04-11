#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>

// Game Libraries
#include "Font.h"
#include "SDLUtils.h"

int main( int argc, char * argv[] )
{
<<<<<<< HEAD
    /**
        Your code go here
    */
=======
    bool quit = false;
    SDL_Event event;

    Window window("Testing", 800, 600);
    while (!quit)
    {
        SDL_WaitEvent(&event);
>>>>>>> cd9e1df9e943b785789e5d8a884edd4d4743043b

    /**
        Test area
    */
    if (!InitSDL())
        return 1;
    return 0;
}
