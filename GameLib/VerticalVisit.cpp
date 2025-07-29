/**
 * @file VerticalVisit.cpp
 * @author Maria Pacifico
 */

#include "VerticalVisit.h"
#include "SpartyGnome.h"
#include "ItemPlatform.h"
#include "ItemWall.h"

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

void VerticalVisit::VisitPlatform(ItemPlatform* platform)
{
    //mGnome->SetLocation();
    Vector newV = mGnome->GetV();
    Vector newP = mGnome->GetP();
    if (!platform->GetGame()->GetLose())
    {
        if (newV.Y() > 0)
        {
            mGnome->SetJump(false);
            // We are falling, stop at the collision point
            newP.SetY(platform->GetY() - platform->GetHeight() / 2 - mGnome->GetHeight() / 2 - Epsilon);
        }
        else
        {
            // We are rising, stop at the collision point
            newP.SetY(platform->GetY() + platform->GetHeight() / 2 + mGnome->GetHeight() / 2 + Epsilon);
            mGnome->SetJump(true); // continue to fall
        }
    }
    newV.SetY(0);
    mGnome->SetLocation(newP.X(), newP.Y());
    mGnome->SetV(newV);
}

void VerticalVisit::VisitOther()
{
    mGnome->SetJump(true);
}

void VerticalVisit::VisitWall(ItemWall* wall)
{
    //mGnome->SetLocation();
    Vector newV = mGnome->GetV();
    Vector newP = mGnome->GetP();
    if (newV.Y() > 0)
    {
        mGnome->SetJump(false);
        // We are falling, stop at the collision point
        newP.SetY(wall->GetY() - wall->GetHeight() / 2 - mGnome->GetHeight() / 2 - Epsilon);
    }
    else
    {
        // We are rising, stop at the collision point
        newP.SetY(wall->GetY() + wall->GetHeight() / 2 + mGnome->GetHeight() / 2 + Epsilon);
        mGnome->SetJump(true); // continue to fall
    }
    newV.SetY(0);
    mGnome->SetLocation(newP.X(), newP.Y());
    mGnome->SetV(newV);
}