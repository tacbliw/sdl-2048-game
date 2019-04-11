#include "Render.h"

Render gRender;
/** @brief Update screen with any last rendering perform
  *
  *
  */
void Render::present()
{
    SDL_RenderPresent(mRenderer);
}

/** @brief Draw a rect with position and width, height given
  *
  *
  */
void Render::fillRect(int x, int y, int width, int height)
{
    SDL_Rect _rect = {x, y, width, height};
    SDL_RenderFillRect(mRenderer, &_rect);
}

/** @brief Draw a rect with position and width, height given
  *
  *
  */
void Render::drawRect(int x, int y, int width, int height)
{
    SDL_Rect _rect = {x, y, width, height};
    SDL_RenderDrawRect(mRenderer, &_rect);
}

/** @brief Clear out entire rendering target with render draw color
  *
  *
  */
void Render::clear()
{
     SDL_RenderClear(mRenderer);
}

/** @brief Set draw color for renderer
  *
  *
  */
void Render::setDrawColor(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
}

/** @brief getter for renderer
  *
  *
  */
SDL_Renderer* Render::getRenderer()
{
    return mRenderer;
}

/** @brief setter for renderer
  *
  *
  */
void Render::setRenderer(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}
