/**
 * @file ItemTuitionUp.h
 * @author William Alff
 *
 * Class that describes a tuition-up power-up in our game.
 */

#ifndef PROJECT1_ITEMTUITIONUP_H
#define PROJECT1_ITEMTUITIONUP_H

#include "Item.h"
#include "Game.h"

/**
 * Class that describes a tuition-up power-up in our game.
 */
class ItemTuitionUp : public Item{
private:
    /// Determines if item has been picked up
    bool mPickedUp = false;

    bool mTemp = true;
    double mInitX;
    double mInitY;
public:
    /**
     * Constructor
     * @param game The game this item is a member of
     * @param dec The declaration of this item
     * @param x The x position of our item
     * @param y The y position of our item
     */
    ItemTuitionUp(Game* game, ItemDec* dec, double x, double y) : Item(game, dec, x, y) {};

    /**
     * Constructor
     * @param game The game this item is a member of
     */
    ItemTuitionUp(Game* game) : Item(game) {}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Sets pickup status on item
     */
    void SetPickedUp() { mPickedUp = true; }

    bool CollisionTest(Item *item) override;
};

#endif //PROJECT1_ITEMTUITIONUP_H
