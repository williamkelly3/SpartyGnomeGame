/**
 * @file Item.cpp
 * @author Maria Pacifico
 * @author William Alff
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"
#include "ItemDec.h"

/**
 * Destructor
 */
Item::~Item()
{

}


/**
 * Constructor
 * @param game The game this item is a member of
 * @param dec The declaration of this item
 * @param x The x position of our item
 * @param y The y position of our item
 */
Item::Item(Game *game, ItemDec* dec, double x, double y) : mGame(game)
{
    mPos.SetX(x);
    mPos.SetY(y);
    std::wstring filename = mGame->GetImageDirectory() + L"/" + dec->GetFilename();
    mItemImage = std::make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
    //mItemBitmap = std::make_unique<wxGraphicsBitmap>(*mItemImage);
}

/**
 * Loads in a specific item from the XML file.
 * @param node Item we are loading in
 */
void Item::XmlLoad(wxXmlNode *node)
{
    auto id = node->GetAttribute(L"id");
    auto declaration = mGame->GetItemDec(id.ToStdWstring());
    std::wstring filename = mGame->GetImageDirectory() + L"/" + declaration.GetFilename();
    mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);

    long x, y;
    node->GetAttribute(L"x", L"0").ToLong(&x);
    node->GetAttribute(L"y", L"0").ToLong(&y);
    mPos.SetX(int(x));
    mPos.SetY(int(y));
}

void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mItemBitmap.IsNull())
    {
        mItemBitmap = graphics->CreateBitmapFromImage(*mItemImage);
    }

    int width = mItemImage->GetWidth();
    int height = mItemImage->GetHeight();
    graphics->DrawBitmap(mItemBitmap, int(GetX() - width / 2),
            int(GetY() - height / 2), width + 1, height);
}


bool Item::CollisionTest(Item * item)
{
    // Border for the item
    auto itemLeft = item->GetX() - item->GetWidth() / 2;
    auto itemRight = item->GetX() + item->GetWidth() / 2;
    auto itemTop = item->GetY() - item->GetHeight() / 2;
    auto itemBottom = item->GetY() + item->GetHeight() / 2;

    // For us
    auto ourLeft = GetX() - GetWidth() / 2;
    auto ourRight = GetX() + GetWidth() / 2;
    auto ourTop = GetY() - GetHeight() / 2;
    auto ourBottom = GetY() + GetHeight() / 2;

    // Test for all of the non-collision cases,
    // cases where there is a gap between the two items
    if (ourRight < itemLeft ||  // Completely to the left
        ourLeft > itemRight ||  // Completely to the right
        ourTop > itemBottom ||  // Completely below
        ourBottom < itemTop)    // Completely above
    {
        return false;
    }

    return true;
}



