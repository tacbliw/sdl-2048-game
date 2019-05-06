#ifndef HIGHSCOREBOARD_H
#define HIGHSCOREBOARD_H

#include <Texture.h>


class HighScoreBoard
{
    public:
        HighScoreBoard(const char *_title, int _x , int _y , int _w = 100, int _h = 50);

//        virtual ~HighScoreBoard();

        int getHighScore();
        void setHighScore(int score);

        void render();

        void loadHighScore();

    private:
        int mHighScore;

        SDL_Point mPosition;
        const char *mTitle;
        int mWidth;
        int mHeight;

        Texture *mTexture;
        Texture *mTextTexture;
        Texture *mHighScoreTexture;
};

extern void loadHighScoreBoardMetadata();

#endif // HIGHSCOREBOARD_H
