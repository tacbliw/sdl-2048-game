#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>

//#include "Texture.h"
#include "Font.h"

/**
 * \brief A class represent a Block in the game
 *
 * \param posX X coordinate of the Block.
 * \param posY Y coordinate of the Block.
 *
 */

class Block
{
    public:
        Block(int posX, int posY, int value);

        int get_posX() { return posX; }
        int get_posY() { return posY; }
        int get_value() { return value; }



    private:
        SDL_Color blockTextColor;
        SDL_Color blockBgColor;
        Font font;

        int x;
        int y;
        int value;
        int posX;
        int posY;
};

#endif // BLOCK_H
