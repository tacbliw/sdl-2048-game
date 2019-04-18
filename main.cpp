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
    InitSDL();
        loadBlockMetadata();
        gRender.setDrawColor({255, 255, 255});
        gRender.clear();
        Game *g = new Game;
        g->init(4);
        g->getBlockBoard()->setPosition((SCREEN_WIDTH - g->getBlockBoard()->getWidth())/2,
                                        (SCREEN_HEIGHT - g->getBlockBoard()->getWidth())/2);
        g->render();
        gRender.present();
        g->printBoard();
        printf("\n");


    bool quit = false;
    SDL_Event event;
    int prevKey = SDL_SCANCODE_ESCAPE;
    while (!quit)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    g->rotateClockWise();
                    break;
                case SDL_SCANCODE_RETURN:
                    g->addRandomBlock();
                    break;
                }
                break;
            }
        }

            g->render();
        gRender.present();
    }
    CloseSDL();


    return 0;
}
