#include "Render.h"

Render gRender;
/** @brief Update screen with any last rendering perform
  *
  * We use SDL_RenderPresent to show what change in texture to screen
  */
void Render::present()
{
    SDL_RenderPresent(mRenderer);
}

/** @brief Draw a rect with position and width, height given
 *
 * @param x int
 * @param y int
 * @param width int
 * @param height int
 * @return void
 *
 * Draw a rectangle with position and width, height given
 */
void Render::fillRect(int x, int y, int width, int height)
{
    SDL_Rect _rect = {x, y, width, height};
    SDL_RenderFillRect(mRenderer, &_rect);
}

/** @brief
 *
 * @param x int
 * @param y int
 * @param width int
 * @param height int
 * @return void
 *
 * Draw a rect with position and width, height given
 */
void Render::drawRect(int x, int y, int width, int height)
{
    SDL_Rect _rect = {x, y, width, height};
    SDL_RenderDrawRect(mRenderer, &_rect);
}

/** @brief Clear out entire rendering target with render draw color
  *
  * Clear out entire rendering target with render draw color, remember to pick a number before clear.
  */
void Render::clear()
{
     SDL_RenderClear(mRenderer);
}

/** @brief Set draw color to render
 *
 * @param color const SDL_Color&
 * @return void
 *
 * Set draw color to render
 */
void Render::setDrawColor(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
}

/** @brief Getter for renderer
  *
  * Getter for renderer
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

void Render::setRenderTarget(SDL_Texture *texture)
{
    SDL_SetRenderTarget(mRenderer, texture);
}
