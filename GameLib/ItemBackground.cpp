/**
 * @file ItemBackground.cpp
 * @author Will K
 */

#include "pch.h"
#include "ItemBackground.h"
#include "Game.h"

void ItemBackground::Draw(std::shared_ptr<wxGraphicsContext> graphics, int scrollX)
{
    int wid = mPicture->GetWidth();
    int hit = mPicture->GetHeight();
    graphics->DrawBitmap(*mPicture,
            (int)GetX() - wid / 2 + scrollX, (int)GetY() - hit / 2,
            wid + 1, hit);
}




