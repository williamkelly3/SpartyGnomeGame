/**
 * @file HorizontalVisit.cpp
 * @author Maria Pacifico
 */

#include "HorizontalVisit.h"
#include "Vector.h"
#include "SpartyGnome.h"
#include "ItemPlatform.h"
#include "ItemWall.h"

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

void HorizontalVisit::VisitPlatform(ItemPlatform *platform)
{
    Vector newV = mGnome->GetV();
    Vector newP = mGnome->GetP();

    //if (newV.X() > 0)
    if (!platform->GetGame()->GetLose())
    {
        if (mGnome->GetWidth()/2 + mGnome->GetX() <= platform->GetX() + platform->GetWidth() / 2)
        {
            // We are moving to the right, stop at the collision point
            newP.SetX(platform->GetX() - platform->GetWidth() / 2 - mGnome->GetWidth() / 2 - Epsilon);
            newV.SetX(0);
        }
        else
        {
            // We are moving to the left, stop at the collision point
            newP.SetX(platform->GetX() + platform->GetWidth() / 2 + mGnome->GetWidth() / 2 + Epsilon);
            newV.SetX(0);
        }
    }

    mGnome->SetLocation(newP.X(), newP.Y());
    mGnome->SetV(newV);
}

void HorizontalVisit::VisitWall(ItemWall *wall)
{
    Vector newV = mGnome->GetV();
    Vector newP = mGnome->GetP();

    //if (newV.X() > 0) {
        if (newV.X() > 0)
        {
            // We are moving to the right, stop at the collision point
            newP.SetX(wall->GetX() - wall->GetWidth() / 2 - mGnome->GetWidth() / 2 - Epsilon);
            newV.SetX(0);
        }
        else
        {
            // We are moving to the left, stop at the collision point
            newP.SetX(wall->GetX() + wall->GetWidth() / 2 + mGnome->GetWidth() / 2 + Epsilon);
            newV.SetX(0);
        }
    //}

    mGnome->SetLocation(newP.X(), newP.Y());
    mGnome->SetV(newV);
}

