#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL.h>

class Window
{
    public:
        Window(const char *title, int width, int height);
        ~Window();

        bool is_closed() const {return closed;}

    private:
        bool init();

    private:
        const char * m_title;
        int width = 800;
        int height = 600;

        bool closed = false;

        SDL_Window *window = NULL;
};

#endif // WINDOW_H
