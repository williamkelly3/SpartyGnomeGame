/**
 * @file Level.h
 * @author Will K, Maria Pacifico
 */

#ifndef PROJECT1_LEVEL_H
#define PROJECT1_LEVEL_H

//#include "Game.h"
#include "Item.h"

class Game;

/**
 *  Base Class for implementing different Levels
 */
class Level
{
private:
    /// Game level is contained in
    Game *mGame;

    /// Vector of items in the level
    std::vector<std::shared_ptr<Item>> mItems;

    /// Starting position X
    int mStartX = 0;

    /// Starting position Y
    int mStartY = 0;

    /// Height of game
    int mHeight = 1024;

    /// Width of game
    int mWidth = 1500;

    ///  Level Background image to use
    std::unique_ptr<wxBitmap> mBackground;

protected:
    Level(Game *game, const std::wstring &filename);

public:

    /// Default constructor (disabled)
    Level() = delete;

    /// Copy constructor (disabled)
    Level(const Level &) = delete;

    /// Assignment operator
    void operator=(const Level &) = delete;

    /**
     * Get the start X
     * @return Start of level x coordinate
     */
    int GetStartX() const {return mStartX;}

    /**
     * Get the start Y
     * @return Start of level y coordinate
     */
    int GetStartY() const {return mStartY;}

    /**
     * Get the Height of game
     * @return Height of the game
     */
    int GetHeight() const {return mHeight;}

    /**
     * Get the Width of game
     * @return Width of the game
     */
    int GetWidth() const {return mWidth;}

    void OnDrawBackground(wxDC *dc);

    //void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

    //virtual void DrawPlats(Game *game, wxDC *dc) = 0;

};

#endif //PROJECT1_LEVEL_H
