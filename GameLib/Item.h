/**
 * @file Item.h
 * @author Maria Pacifico
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

class Game;

#include <wx/xml/xml.h>
#include <wx/graphics.h>
#include "ItemDec.h"
#include "Vector.h"
#include "ItemVisitor.h"

/**
 * Base class for items in the game.
 */
class Item {
private:
    /// The game which the item is contained in
    Game *mGame;

    /// Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    ///Velocity vector
    Vector  mV = Vector(0, -800);     ///< V velocity for the item

    /// The underlying image for the item
    std::shared_ptr<wxImage> mItemImage;

    /// The bitmap we can display the item
    wxGraphicsBitmap mItemBitmap;

    Vector mPos;

protected:
    Item(Game *game, ItemDec* dec, double x, double y);

    Item(Game* game) : mGame(game) {}
public:
    virtual ~Item();
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;


    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mPos.X(); }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mPos.Y(); }

    /**
     * The P location of the item
     * @return P location in pixels
     */
    Vector GetP() const { return Vector(mPos.X(),mPos.Y()); }

    /**
     * The V velocity of the item
     * @return V Vector
     */
    Vector GetV() const { return mV; }

    /**
     * Set V velocity of the item
     * @return V Vector
     */
    void SetV(Vector v) { mV = v; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y){ mPos.Set(x,y); }

    /**
     * Draw this item
     * @param graphics Device context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    virtual void XmlLoad(wxXmlNode* node);

    void SetImage(std::shared_ptr<wxImage> image) { mItemImage = image; }

    virtual double GetWidth() { return mItemImage->GetWidth(); }

    virtual double GetHeight() { return mItemImage->GetHeight(); }

    std::shared_ptr<wxImage> GetImage() { return mItemImage; }

    wxGraphicsBitmap GetBitmap() { return mItemBitmap; }

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    void SetBitmap(wxGraphicsBitmap bitmap)
    {
        mItemBitmap = bitmap;
    }

    virtual bool CollisionTest(Item *item);

    Game* GetGame() { return mGame; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(ItemVisitor* visitor) { visitor->VisitOther(); }

};


#endif //PROJECT1_ITEM_H
