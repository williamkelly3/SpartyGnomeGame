/**
 * @file ItemDoor.h
 * @author William Alff
 *
 * Class that describes a door in our game.
 */

#ifndef PROJECT1_ITEMDOOR_H
#define PROJECT1_ITEMDOOR_H

#include "Item.h"

/**
 * Class that describes a door in our game.
 */
class ItemDoor : public Item {
private:
    /// Collision distance for the door in pixels
    const double CollisionDistance = 20;
public:
    /**
     * Constructor
     * @param game The game this item is a member of
     * @param dec The declaration of this item
     * @param x The x position of our item
     * @param y The y position of our item
     */
    ItemDoor(Game* game, ItemDec* dec, double x, double y) : Item(game, dec, x, y) {};

    /**
     * Constructor with just game
     * @param game The game this item is a member of
     */
    ItemDoor(Game* game) : Item(game) {}

    bool CollisionTest(Item* item) override;

};

#endif //PROJECT1_ITEMDOOR_H
