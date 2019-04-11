#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>

class Render
{
    public:
        void setRenderer(SDL_Renderer *renderer);
        SDL_Renderer* getRenderer();

        void setDrawColor(const SDL_Color &color);
        void clear();
        void drawRect(int x, int y, int width, int height);
        void fillRect(int x, int y, int width, int height);
        void present();

    private:
        SDL_Renderer *mRenderer;
};

/**< We will define gRender in Render.cpp */
extern Render gRender;

#endif // RENDER_H
