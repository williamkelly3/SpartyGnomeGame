/**
 * @file ItemBackground.h
 * @author Will K
 * @author William Alff
 *
 */

#ifndef PROJECT1_ITEMBACKGROUND_H
#define PROJECT1_ITEMBACKGROUND_H

#include "Item.h"

/**
 * Class to implement item Background and Virtual Pixels
 */
class ItemBackground : public Item {
private:
    std::unique_ptr<wxBitmap> mPicture;  ///< Picture image to use
public:
    /**
    * Draw the virtual background
    * @param graphics
    * @param scrollX Keep track of how the object has moved
    */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int scrollX);

    /**
     * Constructor
     * @param game The game this item is a member of
     * @param dec The declaration of this item
     * @param x The x position of our item
     * @param y The y position of our item
     */
    ItemBackground(Game* game, ItemDec* dec, double x, double y) : Item(game, dec, x, y) {}

    /**
     * Constructor with just game
     * @param game The game this item is a member of
     */
    ItemBackground(Game* game) : Item(game) {}
};

#endif //PROJECT1_ITEMBACKGROUND_H
