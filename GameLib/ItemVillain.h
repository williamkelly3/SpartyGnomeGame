/**
 * @file ItemVillain.h
 * @author William Alff
 *
 * Class that describes a villain in our game.
 */

#ifndef PROJECT1_ITEMVILLAIN_H
#define PROJECT1_ITEMVILLAIN_H

#include "Item.h"
#include "Game.h"

/**
 * Class that describes a villain in our game.
 */
class ItemVillain : public Item {
private:
    /// Starting position of the villain
    Vector mStart;

    /// Velocity of the villain
    Vector mVel;
public:
    /**
     * Constructor
     * @param game The game this item is a member of
     * @param dec The declaration of this item
     * @param x The x position of our item
     * @param y The y position of our item
     */
    ItemVillain(Game* game, ItemDec* dec, double x, double y) : Item(game, dec, x, y) {};

    /**
     * Constructor
     * @param game The game this item is a member of
     */
    ItemVillain(Game* game) : Item(game) {};

    void Update(double elapsed) override;

    void XmlLoad(wxXmlNode* node) override;

    //bool CollisionTest(Item *item) override;

    void Accept(ItemVisitor* visitor) override { visitor->VisitVillian(this); }
};

#endif //PROJECT1_ITEMVILLAIN_H
