/**
 * @file ItemPlatform.cpp
 * @author William Alff
 */

#include "pch.h"
#include "ItemPlatform.h"

/**
 * Loads in a specific platform from the XML file.
 * @param node Platform we are loading in
 */
void ItemPlatform::XmlLoad(wxXmlNode* node)
{
    auto id = node->GetAttribute(L"id");
    auto dec = mGame->GetPlatformDec(id.ToStdWstring());

    // SET IMAGE IN ITEM
    std::wstring filename = mGame->GetImageDirectory() + L"/" + dec.GetFilename();
    SetImage(std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY));

    std::wstring left = mGame->GetImageDirectory() + L"/" + dec.GetLeftImageFilename();
    std::wstring right = mGame->GetImageDirectory() + L"/" + dec.GetRightImageFilename();
    std::wstring middle = mGame->GetImageDirectory() + L"/" + dec.GetFilename();
    SetImages(std::make_unique<wxImage>(left, wxBITMAP_TYPE_ANY),
            std::make_unique<wxImage>(right, wxBITMAP_TYPE_ANY),
                    std::make_unique<wxImage>(middle, wxBITMAP_TYPE_ANY));

    long x, y;
    node->GetAttribute(L"x", L"0").ToLong(&x);
    node->GetAttribute(L"y", L"0").ToLong(&y);
    SetLocation(int(x), int(y));

    long width, height;
    node->GetAttribute(L"width").ToLong(&width);
    node->GetAttribute(L"height").ToLong(&height);
    SetDimensions(width, height);
}

/**
 * Draws platform in our game
 * @param graphics The graphics context to draw on
 */
void ItemPlatform::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double leftImageX = GetX() - GetWidth() / 2;
    double midImageX = GetX() - GetWidth() / 2 + mMidImage->GetWidth();
    double rightImageX = GetX() + GetWidth() / 2 - mRightImage->GetWidth();

    if (mLeftBitmap.IsNull())
    {
        mLeftBitmap = graphics->CreateBitmapFromImage(*mLeftImage);
    }
    int width = mLeftImage->GetWidth();
    int height = mLeftImage->GetHeight();
    graphics->DrawBitmap(mLeftBitmap, int(leftImageX + 1), int(GetY() - height / 2), width, height);

    if (GetBitmap().IsNull())
    {
        SetBitmap(graphics->CreateBitmapFromImage(*mMidImage));
    }

    width = mMidImage->GetWidth();
    height = mMidImage->GetHeight();

    int dist = 0;
    for (int i = 0; i < GetWidth() - width; i += width, dist += width)
    {
        graphics->DrawBitmap(GetBitmap(), int(midImageX + dist), int(GetY() - height / 2), width + 1, height);
    }

    if (mRightBitmap.IsNull())
    {
        mRightBitmap = graphics->CreateBitmapFromImage(*mRightImage);
        width = mRightImage->GetWidth();
        height = mRightImage->GetHeight();
        graphics->DrawBitmap(mRightBitmap, int(rightImageX + 2), int(GetY() - height / 2), width, height);
    }
}
