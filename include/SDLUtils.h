#ifndef SDLUTILS_H_INCLUDED
#define SDLUTILS_H_INCLUDED

#include <SDL.h>

extern const int  SCREEN_WIDTH;
extern const int  SCREEN_HEIGHT;
extern const SDL_Color BACKGROUND_COLOR;

extern bool InitSDL();
extern void CloseSDL();

#endif // SDLUTILS_H_INCLUDED
