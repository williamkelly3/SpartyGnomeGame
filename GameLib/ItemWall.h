/**
 * @file ItemWall.h
 * @author William Alff
 *
 * Class that describes a wall in our game.
 */

#ifndef PROJECT1_ITEMWALL_H
#define PROJECT1_ITEMWALL_H

#include "Item.h"

/**
 * Class that describes a wall in our game.
 */
class ItemWall : public Item{
private:
    /// Left image of wall
    std::shared_ptr<wxImage> mLeftImage;

    /// Right image of wall
    std::shared_ptr<wxImage> mRightImage;

    /// Left bitmap of wall
    wxGraphicsBitmap mLeftBitmap;

    /// Right bitmap of wall
    wxGraphicsBitmap mRightBitmap;

    /// Width of the wall
    int mWidth;

    /// Height of the wall
    int mHeight;
public:
    /**
     * Constructor
     * @param game The game this item is a member of
     * @param dec The declaration of this item
     * @param x The x position of our item
     * @param y The y position of our item
     * @param w The width of the item
     * @param h The height of the item
     */
    ItemWall(Game* game, ItemDec* dec, double x, double y, double w, double h) : Item(game, dec, x, y),
    mWidth(w), mHeight(h) {}

    /**
     * Constructor with just game
     * @param game The game this item is a member of
     */
    ItemWall(Game* game) : Item(game) {}

    void XmlLoad(wxXmlNode* node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Sets dimensions of wall
     * @param width Width of the wall
     * @param height Height of the wall
     */
    void SetDimensions(int width, int height) { mWidth = width; mHeight = height; }

    /**
     * Gets width of the wall
     * @return Width of the wall
     */
    double GetW() { return mWidth; }

    /**
     * Gets height of the wall
     * @return Height of the wall
     */
    double GetH() { return mHeight; }

    //bool CollisionTest(Item * item) override;

    void Accept(ItemVisitor* visitor) override { visitor->VisitWall(this); }
};

#endif //PROJECT1_ITEMWALL_H
