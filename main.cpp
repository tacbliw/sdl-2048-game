#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>

// Game Libraries
#include "Font.h"
#include "SDLUtils.h"
#include "Render.h"

int main( int argc, char * argv[] )
{
    /**
        Your code go here
    */

    /**
        Test area
    */
    if (InitSDL())
    {
        SDL_Color _t = {0xFF, 0x00, 0x00, 0xFF};
        gRender.setDrawColor(_t);
        gRender.drawRect(10, 10, 10, 10);
        SDL_RenderPresent(gRender.getRenderer());
    }

    SDL_Delay( 2000 );


    return 0;
}
