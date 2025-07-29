/**
 * @file ItemMoney.cpp
 * @author William Alff
 */

#include "pch.h"
#include "ItemMoney.h"

/**
 * Loads in a specific money from the XML file.
 * @param node Money we are loading in
 */
void ItemMoney::XmlLoad(wxXmlNode* node)
{
    auto id = node->GetAttribute(L"id");
    auto dec = mGame->GetMoneyDec(id.ToStdWstring());

    std::wstring filename = mGame->GetImageDirectory() + L"/" + dec.GetFilename();
    SetImage(std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY));

    mValue = dec.GetVal();

    long x, y;
    node->GetAttribute(L"x", L"0").ToLong(&x);
    node->GetAttribute(L"y", L"0").ToLong(&y);
    SetLocation(int(x), int(y));
}

/**
 * Draws money in our game
 * @param graphics The graphics context to draw on
 */
void ItemMoney::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);

    if (mTemp)
    {
        mInitX = GetX();
        mInitY = GetY();
    }
    if (mPickedUp)
    {
        wxFont font(wxSize(50, 50), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, wxColour(0, 102, 0));
        SetLocation(GetX(), GetY() - 25);
        if (GetGame()->GetScoreMultiplier() == 1) {
            graphics->DrawText(L"$" + std::to_string(int(mValue * GetGame()->GetScoreMultiplier())), GetX(), GetY());
        }
        else {
            graphics->DrawText(L"$" + std::to_string(int(mValue * GetGame()->GetScoreMultiplier()) + 1), GetX(), GetY());
            //mGame->RemoveItem(this);
        }
//        graphics->DrawText(L"$" + std::to_string(int(mValue * GetGame()->GetScoreMultiplier()) + 1), GetX(), GetY());
//        //mGame->RemoveItem(this);
        if (mTemp)
        {
            if (GetGame()->GetScoreMultiplier() == 1) {
                mGame->GetScoreboard()->IncreaseScore(mValue * GetGame()->GetScoreMultiplier());
                mTemp = false;
            }else {
                mGame->GetScoreboard()->IncreaseScore(mValue * GetGame()->GetScoreMultiplier() + 1);
                mTemp = false;
            }
//            mGame->GetScoreboard()->IncreaseScore(mValue * GetGame()->GetScoreMultiplier() + 1);
//            mTemp = false;
        }
    }
}

bool ItemMoney::CollisionTest(Item* item)
{
    bool collided = Item::CollisionTest(item);
    if (collided)
    {
        SetPickedUp();
    }
    return false;
}