#include "Render.h"
#include "Texture.h"
#include "Font.h"
#include <stdio.h>
#include "SDLUtils.h"
/** @brief Load texture from file
  *
  *
  */
SDL_Texture* Texture::loadTexture(std::string path)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadSurface = IMG_Load(path.c_str());
    if (loadSurface == NULL)
    {
        printf("cant load image....\n SDL_image error: %s\n", IMG_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRender.getRenderer(), loadSurface);
        if (newTexture == NULL)
        {
            printf("gimme some paper to draw, i dont have texture. SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            mWidth = loadSurface->w;
            mHeight = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }

    return newTexture;
}

/** @brief Load texture from text
  *
  *
  */
SDL_Texture* Texture::loadTextureFromText(Font *f, const char *text, SDL_Color fgColor)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *textSurface = f->renderText(text, fgColor);
    if (textSurface == NULL)
    {
        printf("cant load text surface....\n SDL_error: %s\n", SDL_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRender.getRenderer(), textSurface);
        if (newTexture == NULL)
        {
            printf("gimme some paper to draw, i dont have texture. SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    return newTexture;
}


/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Texture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(gRender.getRenderer(), mTexture, clip, &renderQuad);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Texture::setAsRenderTarget(SDL_Texture *texture)
{
    SDL_SetRenderTarget(gRender.getRenderer(), texture);
}


