#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "Texture.h"

class ScoreBoard
{
    public:
        ScoreBoard(const char *_title, int _x = 0, int _y = 0, int _w = 100, int _h = 50);

        int getPoint();
        void addPoint(int point);
        void resetPoint();

        void render();

    private:
        int mPoint;
        SDL_Point mPosition;
        const char *mTitle;
        int mWidth;
        int mHeight;

        Texture *mTexture;
        Texture *mTextTexture;
        Texture *mPointTexture;
};

extern void loadScoreBoardMetadata();

#endif // SCOREBOARD_H
