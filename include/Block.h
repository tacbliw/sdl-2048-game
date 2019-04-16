#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>

#include "Texture.h"
#include "Font.h"

extern void loadBlockMetadata();
extern void unloadBlockMetadata();

/**
 * @brief A class represent a Block in the game
 *
 * @param row X coordinate of the Block.
 * @param col Y coordinate of the Block.
 *
 */

class Block
{
    public:
        Block(int row, int col, int value);

        int get_row() { return row; }
        int get_col() { return col; }
        int get_value() { return value; }


        void render(int x, int y);

    private:
        SDL_Color blockTextColor;
        SDL_Color blockBgColor;
        Font font;

        int mX;
        int mY;
        int value;
        int row;
        int col;

        Texture *mBlockTexture;
        Texture *mTextInBlockTexture;


};

#endif // BLOCK_H
