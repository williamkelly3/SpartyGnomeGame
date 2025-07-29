/**
 * @file ItemMoney.h
 * @author William Alff
 *
 * Class that describes money in our game.
 */

#ifndef PROJECT1_ITEMMONEY_H
#define PROJECT1_ITEMMONEY_H

#include "Item.h"
#include "Game.h"

/**
 * Class that describes money in our game.
 */
class ItemMoney : public Item {
private:
    /// Game that money is part of
    Game *mGame;

    /// Dollar Value of the money
    double mValue;

    /// Determines if money has been picked up
    bool mPickedUp = false;

    bool mTemp = true;
    double mInitX;
    double mInitY;
public:
    /**
     * Constructor
     * @param game The game this money is a member of
     * @param dec The declaration of this money
     * @param x The x position of our money
     * @param y The y position of our money
     */
    ItemMoney(Game* game, MoneyDec* dec, double x, double y) : Item(game, dec, x, y),
        mGame(game), mValue(dec->GetVal()) {};

    void XmlLoad(wxXmlNode* node) override;

    /**
     * Constructor with just game
     * @param game The game this money is a member of
     */
    ItemMoney(Game* game) : Item(game), mGame(game) {}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Sets pickup status on item
     */
    void SetPickedUp() { mPickedUp = true; }

    bool CollisionTest(Item *item) override;

};

#endif //PROJECT1_ITEMMONEY_H
