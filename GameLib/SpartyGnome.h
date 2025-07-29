/**
* @file SpartyGnome.h
* @author LeeAnn Alsaeed
*/

#ifndef PROJECT1_SPARTYGNOME_H
#define PROJECT1_SPARTYGNOME_H

#include "Item.h"

class Item;

/**
 * Class that controls Sparty Gnome as an Item
 */
class SpartyGnome : public Item {
private:
    /// The bitmap we can display the item
    wxGraphicsBitmap mGnome;

    /// The underlying image for the item
    std::shared_ptr<wxImage> mItemImage;

    /// Determines whether the gnome jumps or not
    bool mJump = false;

    /// Left image bool
    bool mLeft = false;

    /// Right image bool
    bool mRight = false;

public:
    /// Default constructor (disabled)
    SpartyGnome() = delete;

    /// Copy constructor (disabled)
    SpartyGnome(const SpartyGnome &) = delete;

    /// Assignment operator
    void operator=(const SpartyGnome &) = delete;

    SpartyGnome(Game *game, double x, double y);

    void DrawRight(std::shared_ptr<wxGraphicsContext> graphics);

    void DrawLeft(std::shared_ptr<wxGraphicsContext> graphics);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Constructor
     * @param game The game our item is a member of
     */
    SpartyGnome(Game *game) : Item(game) {}

    void Update(double elapsed) override;

    void ResetVelocity();

    void OnLeft(double elapsed);

    void OnRight(double elapsed);

    std::shared_ptr<wxImage> GetSpartyImage() { return mItemImage; }

    void SetJump(bool jump) { mJump = jump; }

    bool GetJump() { return mJump; }

    bool GetLeft() { return mLeft; }

    bool GetRight() { return mRight; }

    void SetLeft(bool set) { mLeft = set; }

    void SetRight(bool set) { mRight = set; }
};

#endif //PROJECT1_SPARTYGNOME_H
