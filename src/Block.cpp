#include <map>
#include <stdio.h>
#include <sstream>

#include "Block.h"
#include "Texture.h"
#include "Render.h"
#include "Font.h"


/** Small change to help the game run smoother.
 *
 *  Instead of generating block style (background color, text color, font size) in
 * every frame, we can just generate all of that at the beginning and store in a map:
 *          map<int, blockStyle>
 *
 *  Each frame, we just have to read the attributes directly from the map, which is O(1).
 */

#define MAX_BLOCK_VALUE 65536

struct blockStyle
{
    SDL_Color backgroundColor;
    SDL_Color textColor;
    Font font;
};
std::map<int, blockStyle> blockStyleMap;

// ============== FONTS =================
static Font numberSmall;
static Font numberMedium;
static Font numberLarge;

void fontInit(const char *fontFile)
{
    numberSmall.init(fontFile, 35);
    numberMedium.init(fontFile, 45);
    numberLarge.init(fontFile, 55);
}

void fontFree()
{
    numberSmall.free();
    numberMedium.free();
    numberLarge.free();
}

// ============== COLOR =================
SDL_Color backgroundColors[] = {
    {240, 230, 215}, // 2
    {240, 225, 200}, // 4
    {240, 177, 120}, // 8
    {245, 150, 100}, // 16
    {240, 203, 100}, // 32
    {250,  93,  60}, // 64
    {240, 205, 115}, // 128
    {240, 205,  97}, // 256
    {240, 200,  80}, // 512
    {240, 200,  65}, // 1024
    {240, 190,  50}, // 2048
    {240, 105, 110}, // 4096
    { 90, 160, 220}, // 8192
    {245,  65,  65}, // 16384
    {115, 180, 215}, // 32768
    { 90, 160, 222}  // 65536
};

SDL_Color BLACK = {0, 0, 0};

/** @brief Get background color for a block.
 *
 * @param blockValue current value of the block.
 * @return  SDL_Color for the block background,
 *  if blockValue > 65536, return BLACK {0, 0, 0}.
 */
SDL_Color getBlockBackgroundColor(int blockValue)
{
    int valueNumber = 2;
    int level = 0;


    while (valueNumber != blockValue)
    {
        level++;
        valueNumber *= 2;
    }

    if (level > 15)
    {
        return BLACK;
    }
    return backgroundColors[level];
}


SDL_Color textColors[] = {
    {120, 110, 100}, // 2, 4
    {255, 255, 255}  // others
};


/** @brief Get text color for a block.
 *
 * @param blockValue current value of the block.
 * @return SDL_Color for the block text.
 *
 * All blocks that have value greater than 4 will have WHITE text.
 */
SDL_Color getBlockTextColor(int blockValue)
{
    if (blockValue == 2 || blockValue == 4)
    {
        return textColors[0];
    }
    else
    {
        return textColors[1];
    }
}

//============== BLOCK STYLE ================
void initBlockStyle()
{
    int blockValue = 2;
    while (blockValue <= MAX_BLOCK_VALUE)
    {
        blockStyle style;

        style.backgroundColor = getBlockBackgroundColor(blockValue);
        style.textColor = getBlockTextColor(blockValue);

        if (blockValue < 1024)
        {
            style.font = numberLarge;
        }
        else if (blockValue < 16384)
        {
            style.font = numberMedium;
        }
        else
        {
            style.font = numberSmall;
        }

        blockStyleMap[blockValue] = style;

        blockValue *= 2;
    }
}

//=============== COORDINATE ================
/** @brief Calculate SDL position x and y from coordinate of
 *  the block in 4x4 block board.
 *
 * @param row, col coordinates of block in 4x4 block board.
 * @param *x, *y SDL coordinate
 * @return nothing, but change *x and *y to the right number.
 *
 */
int blockSize = 100;
int gridSpacing = 15;

void calPosFromXY(int row, int col, int *x, int *y)
{
    *x = col * (blockSize + gridSpacing);
    *y = row * (blockSize + gridSpacing);
}

std::shared_ptr<Animation> makeMoveAnimation(int row1, int col1, int row2, int col2)
{
    int x1, y1, x2, y2;
    calPosFromXY(row1, col1, &x1, &y1);
    calPosFromXY(row2, col2, &x2, &y2);
    printf("%d:%d to %d:%d \n", row1, col1, row2, col2);

    auto animation = std::make_shared<Animation>(100, TMFUNC_EASE_IN_OUT);
    auto t = animation->createTransition(1);
    t->add(0, x1);
    t->add(100, x2);
    //printf("make move!!\n");
    return animation;
}

//================ METADATA =================
/** @brief Two function to help load and unload metadata.
 *
 *  Load and unload includes fonts, animations.
 */

extern void loadBlockMetadata()
{
    const char *fontFile = "Fonts/OpenSans-Bold.ttf";
    fontInit(fontFile);
    initBlockStyle();

    /**
     *  Add animation here
     */

}

extern void unloadBlockMetadata()
{
    fontFree();

    /**
     *  Add animation here
     */
}

//============ CLASS ATTRIBUTES =============
Block::Block(int row, int col, int value)
{
    this->row = row;
    this->col = col;
    this->value = value;
    loadBlockMetadata();
    calPosFromXY(row, col, &mX, &mY);
    mTextInBlockTexture = new Texture();
    mBlockTexture = new Texture();
}

/** @brief Render block
 *
 * @param x: x position
 * @param y: y position
 *
 */
void Block::render(int x, int y)
{
    std::stringstream ss;
    ss << get_value();
    mTextInBlockTexture->loadTextureFromText(&numberLarge, ss.str().c_str(), getBlockTextColor(get_value()));
    mBlockTexture->createBlankTexture(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, blockSize, blockSize);

    mBlockTexture->setAsRenderTarget();
    gRender.setDrawColor(getBlockBackgroundColor(get_value()));
    gRender.clear();
    mTextInBlockTexture->render((blockSize - mTextInBlockTexture->getWidth())/2, (blockSize - mTextInBlockTexture->getHeight())/2, NULL);

    gRender.setRenderTarget(NULL);
    mBlockTexture->render(x + mX, y + mY, NULL);
    //gRender.present();
}

void updateBlock(Block *block, int delta_ms)
{
    if(block->mAnimationExecutor)
    {
        block->mAnimationExecutor->progress(delta_ms);
    }
}
void Block::update(int delta_ms)
{
    updateBlock(this, delta_ms);
}

void Block::setProperty(int ID, double value)
{
    switch (ID)
    {
    case 1:
        mX = static_cast<int>(value);
        break;
    case 2:
        mY = static_cast<int>(value);
        break;
    }
}

void Block::attachAnimation(std::shared_ptr<Animation> animation)
{
    mAnimationExecutor = std::make_shared<AnimationExecutor>(animation, this);
    mAnimationExecutor->init();
}

void Block::planMove(int toRow, int toCol)
{
    attachAnimation(makeMoveAnimation(row, col, toRow, toCol));
    row = toRow;
    col = toCol;
    printf("row: %d, col: %d\n", row, col);
}
