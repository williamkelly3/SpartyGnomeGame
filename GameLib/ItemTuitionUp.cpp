/**
 * @file ItemTuitionUp.cpp
 * @author William Alff
 */

#include "pch.h"
#include "ItemTuitionUp.h"

/**
 * Draws tuition-up power-up.
 * @param graphics The graphics context to draw on
 */
void ItemTuitionUp::Draw(std::shared_ptr<wxGraphicsContext> graphics)
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
        SetLocation(GetX(), GetY() + 50);
        graphics->DrawText(L"Tuition Increase!", mInitX, mInitY);
        mInitX += 2;
        mInitY -= 25;
    }
}

bool ItemTuitionUp::CollisionTest(Item* item)
{
    Game* game = GetGame();
    bool collided = Item::CollisionTest(item);
    if (collided)
    {
        SetPickedUp();
        game->AddScoreMultiplier(.1 / 8);
    }
    return false;
}