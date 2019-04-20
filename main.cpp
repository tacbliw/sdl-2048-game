#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>
#include <windows.h>

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
    if (!InitSDL()) return 0;
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
    while (!quit && SDL_WaitEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_UP:
                g->movementExecute(SDL_SCANCODE_UP);
                break;
            case SDL_SCANCODE_DOWN:
                g->movementExecute(SDL_SCANCODE_DOWN);
                break;
            case SDL_SCANCODE_LEFT:
                g->movementExecute(SDL_SCANCODE_LEFT);
                break;
            case SDL_SCANCODE_RIGHT:
                g->movementExecute(SDL_SCANCODE_RIGHT);
                break;
            default:
                printf("Unhandled key\n");
                break;
            }
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
        g->render();
        gRender.present();
    }
    CloseSDL();


    return 0;
}
