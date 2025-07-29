/**
 * @file ItemVillain.cpp
 * @author William Alff
 */

#include "pch.h"
#include "ItemVillain.h"

/**
 * Loads in a villain from the XML file.
 * @param node Villain we are loading in
 */
void ItemVillain::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    mStart.Set(GetX(), GetY());
    mVel.Set(0, 0);
}

/**
 * Updates position of the villain
 * @param elapsed Elapsed time since game began
 */
void ItemVillain::Update(double elapsed)
{
    Vector pos;
    pos.Set(GetX(), GetY());
    Vector newPos = pos + (mVel * elapsed);
    if (newPos.Y() <= mStart.Y() - 300)
    {
        mVel.SetY(150);
    }
    if (newPos.Y() > mStart.Y() - 20)
    {
        mVel.SetY(-150);
    }
    SetLocation(newPos.X(), newPos.Y());
}
/*
bool ItemVillain::CollisionTest(Item* item)
{
    Game* game = GetGame();
    bool collided = Item::CollisionTest(item);
    if (collided)
    {
        game->SetLose(collided);
    }
    return false;
}
 */