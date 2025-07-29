/**
 * @file ItemDoor.cpp
 * @author William Alff, LeeAnn Alsaeed
 */

#include "pch.h"
#include "ItemDoor.h"
#include "Game.h"

bool ItemDoor::CollisionTest(Item* item)
{
    // Collision for door is different
    double dx = item->GetX() - GetX();
    double dy = item->GetY() - GetY();
    double distance = sqrt(dx * dx + dy * dy);
    if (distance < CollisionDistance)
    {
        GetGame()->SetDoorCol(true);
    }

    return false;
}

