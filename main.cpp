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
    SDL_Event e;
    Uint32 ticks = SDL_GetTicks();
    while (!quit)
    {
        while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT)
            quit = true;
        else if(e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
            case SDLK_UP:
                g->movementExecute(UP);
                break;
            case SDLK_RIGHT:
                g->movementExecute(RIGHT);
                break;
            case SDLK_DOWN:
                g->movementExecute(DOWN);
                break;
            case SDLK_LEFT:
                g->movementExecute(LEFT);
                break;
            }
        }
                g->render();
        gRender.present();
        Uint32 new_ticks = SDL_GetTicks();
        int delta_ms = new_ticks - ticks;
        ticks = new_ticks;
        g->update(delta_ms);
    }



    }
    CloseSDL();

    return 0;
}
