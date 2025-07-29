/**
 * @file ItemInvincibility.h
 * @author William Alff
 *
 * Class that describes an invincibility power-up in our game.
 */

#ifndef PROJECT1_ITEMINVINCIBILITY_H
#define PROJECT1_ITEMINVINCIBILITY_H

#include "Item.h"
#include "Game.h"

/**
 * Class that describes an invincibility power-up in our game.
 */
class ItemInvincibility : public Item {
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
    ItemInvincibility(Game* game, ItemDec* dec, double x, double y) : Item(game, dec, x, y) {};

    /**
     * Constructor
     * @param game The game this item is a member of
     */
    ItemInvincibility(Game* game) : Item(game) {}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Sets pickup status on item
     */
    void SetPickedUp() { mPickedUp = true; }

    bool CollisionTest(Item *item) override;
};

#endif //PROJECT1_ITEMINVINCIBILITY_H
