#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>

#include "Texture.h"
#include "Font.h"
#include "Animation.h"

extern void loadBlockMetadata();
extern void unloadBlockMetadata();

/**
 * @brief A class represent a Block in the game
 *
 * @param row X coordinate of the Block.
 * @param col Y coordinate of the Block.
 *
 */
class AnimationExecutor;
class Animation;
class Block
{
    public:
        Block(int row, int col, int value);

        int get_row() { return row; }
        int get_col() { return col; }
        int get_value() { return value; }

        void set_row(int row) { this->row = row; }
        void set_col(int col) { this->col = col; }
        void set_value(int value) { this->value = value; }

        void render(int x, int y);

        void update(int delta_ms);

        void setProperty(int ID, double value);
        void attachAnimation(std::shared_ptr<Animation> animation);
        std::shared_ptr<AnimationExecutor> mAnimationExecutor;
        void planMove(int row, int col);

        Block *mergeFrom1, *mergeFrom2;

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

        friend void updateBlock(Block *block, int delta_ms);
        //std::shared_ptr<AnimationExecutor> mAnimationExecutor;


};

#endif // BLOCK_H
