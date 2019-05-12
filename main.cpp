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
#include "Button.h"
#include "ScoreBoard.h"
#include "HighScoreBoard.h"

const int SIZE = 4;

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
        loadButtonMetadata();
        loadScoreBoardMetadata();
        loadBlockBoardMetadata();
        loadHighScoreBoardMetadata();

        gRender.setDrawColor(BACKGROUND_COLOR);
        gRender.clear();
        Game *g = new Game;
        g->init(SIZE);
        g->render();
        gRender.present();

        Button *newGameBtn = new Button("New game");
        newGameBtn->setCallBackFunc( [=] { g->newGame(); } );
        newGameBtn->setPosition((SCREEN_WIDTH - g->getBlockBoard()->getWidth()) / 2, 25);


        bool quit = false;
        SDL_Event e;
        Uint32 ticks = SDL_GetTicks();
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT)
                    quit = true;
                else if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_UP:
                        g->move(UP);
                        break;
                    case SDLK_RIGHT:
                        g->move(RIGHT);
                        break;
                    case SDLK_DOWN:
                        g->move(DOWN);
                        break;
                    case SDLK_LEFT:
                        g->move(LEFT);
                        break;
                    }
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    newGameBtn->handleEvent(&e);
                }
            }
            Uint32 new_ticks = SDL_GetTicks();
            int delta_ms = new_ticks - ticks;
            ticks = new_ticks;
            gRender.setDrawColor(BACKGROUND_COLOR);
            gRender.clear();
            g->render();
            newGameBtn->render();
            gRender.present();
            g->update(delta_ms);
        }
        CloseSDL();
    }
    return 0;
}
