/**
 * @file ItemWall.cpp
 * @author William Alff
 */

#include "pch.h"
#include "ItemWall.h"

/**
 * Loads in a specific wall from the XML file.
 * @param node Wall we are loading in
 */
void ItemWall::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    long width, height;
    node->GetAttribute(L"width").ToLong(&width);
    node->GetAttribute(L"height").ToLong(&height);
    SetDimensions(width, height);
}

/**
 * Draws wall in our game
 * @param graphics The graphics context to draw on
 */
void ItemWall::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (GetBitmap().IsNull())
    {
        SetBitmap(graphics->CreateBitmapFromImage(*GetImage()));
    }
    int width = GetImage()->GetWidth();
    int height = GetImage()->GetHeight();

    int dist = 0;
    for (int i = height; i <= GetH(); dist += height, i += height)
    {
        graphics->DrawBitmap(GetBitmap(), int(GetX() - width / 2),
                int((GetY() - height) + (height - GetH() / 2 + dist)), width, height + 1);
    }
}
