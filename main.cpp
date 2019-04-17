#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>

// Game Libraries
#include "Font.h"
#include "SDLUtils.h"
#include "Render.h"
#include "Block.h"
#include "BlockBoard.h"
#include "Game.h"

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
        loadBlockMetadata();
        gRender.setDrawColor({255, 255, 255});
        gRender.clear();
        Game *g = new Game;
        g->init(4);
        g->getBlockBoard()->setPosition((SCREEN_WIDTH - g->getBlockBoard()->getWidth())/2,
                                        (SCREEN_HEIGHT - g->getBlockBoard()->getWidth())/2);
        g->render();
        gRender.present();
    }

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                quit = true;
        }
    }
    CloseSDL();


    return 0;
}
