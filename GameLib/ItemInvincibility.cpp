/**
 * @file ItemInvincibility.cpp
 * @author William Alff
 */

#include "pch.h"
#include "ItemInvincibility.h"

/**
 * Draws invincibility power-up
 * @param graphics The graphics context to draw on
 */
void ItemInvincibility::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);

    if (mTemp)
    {
        mInitX = GetX();
        mInitY = GetY();
        mTemp = false;
    }
    if (mPickedUp)
    {
        wxFont font(wxSize(50, 50), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, wxColour(0, 102, 0));
        //SetLocation(GetX(), GetY() + 50);
        graphics->DrawText(L"Invincibility!", mInitX, mInitY);
        SetLocation(GetX(), GetY() + 50);
        mInitX += 2;
        mInitY -= 25;
    }
}

bool ItemInvincibility::CollisionTest(Item* item)
{
    bool collided = Item::CollisionTest(item);
    if (collided)
    {
        SetPickedUp();
        GetGame()->SetInvincible(true);
    }
    return false;
}
