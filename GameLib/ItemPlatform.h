/**
 * @file ItemPlatform.h
 * @author William Alff
 *
 * Class that describes a platform in our game.
 */

#ifndef PROJECT1_ITEMPLATFORM_H
#define PROJECT1_ITEMPLATFORM_H

#include "PlatformDec.h"
#include "Item.h"
#include "Game.h"

/**
 * Class that describes a platform in our game.
 */
class ItemPlatform : public Item {
private:
    /// Left image of platform
    std::shared_ptr<wxImage> mLeftImage;

    /// Middle image of platform
    std::shared_ptr<wxImage> mMidImage;

    /// Right image of platform
    std::shared_ptr<wxImage> mRightImage;

    /// Left bitmap of platform
    wxGraphicsBitmap mLeftBitmap;

    /// Right bitmap of platform
    wxGraphicsBitmap mRightBitmap;

    /// The game our platform is in
    Game *mGame;

    /// Width of our platform
    int mWidth;

    /// Height of our platform
    int mHeight;
public:
    /**
     * Constructor
     * @param game The game this platform is a member of
     * @param dec The declaration of this platform
     * @param x The x position of our platform
     * @param y The y position of our platform
     * @param w The width of our platform
     * @param h The height of our platform
     */
    ItemPlatform(Game* game, PlatformDec* dec, double x, double y, double w, double h) : Item(game, dec, x, y), mGame(game),
        mLeftImage(std::make_unique<wxImage>(dec->GetLeftImageFilename(), wxBITMAP_TYPE_ANY)),
        mRightImage(std::make_unique<wxImage>(dec->GetRightImageFilename(), wxBITMAP_TYPE_ANY)),
        mMidImage(std::make_unique<wxImage>(dec->GetFilename(), wxBITMAP_TYPE_ANY)),
        mWidth(w), mHeight(h) {};

    /**
     * Constructor with just game
     * @param game The game this platform is a member of
     */
    ItemPlatform(Game* game) :Item(game) ,mGame(game) {}

    void XmlLoad(wxXmlNode* node) override;

    /**
     * Sets images for left, right, and middle platforms
     * @param left Left platform image
     * @param right Right platform image
     * @param middle Middle platform image
     */
    void SetImages(std::shared_ptr<wxImage> left, std::shared_ptr<wxImage> right, std::shared_ptr<wxImage> middle)
    {
        mLeftImage = left;
        mRightImage = right;
        mMidImage = middle;
    }

    /**
     * Sets dimensions of the platform
     * @param width Width of the platform
     * @param height Height of the platform
     */
    void SetDimensions(int width, int height) { mWidth = width; mHeight = height; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Gets width of the platform
     * @return Width of the platform
     */
    //double GetW() { return mWidth; }
    double GetWidth() override { return mWidth; }

    /**
     * Gets height of the platform
     * @return Height of the platform
     */
    //double GetH() { return mHeight; }
    double GetHeight() override { return mHeight; }

    //bool CollisionTest(Item * item) override;

    void Accept(ItemVisitor* visitor) override { visitor->VisitPlatform(this); }

};

#endif //PROJECT1_ITEMPLATFORM_H
