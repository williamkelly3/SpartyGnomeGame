/**
 * @file SpartyGnome.cpp
 * @author LeeAnn Alsaeed
 */

#include "pch.h"
#include "SpartyGnome.h"
#include "Game.h"
//#include "ItemDoor.h"
#include "VerticalVisit.h"
#include "HorizontalVisit.h"

/// Gravity in virtual pixels per second per second
const double Gravity = 1000.0;

/// Horizontal character speed in pixels per second
const double HorizontalSpeed = 500.00*20;

/// Jump speed constant
const double JumpSpeed = -800;

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

/// Sparty Gnome image
const std::wstring Gnome = L"images/gnome.png";

/// Map of images
std::map<std::string, const std::wstring> image_map { {"Gnome", L"images/gnome.png"}, {"LeftGnomeOne", L"images/gnome-walk-left-1.png"},
        {"LeftGnomeTwo", L"images/gnome-walk-left-2.png"}, {"RightGnomeOne",L"images/gnome-walk-right-1.png"}, {"RightGnomeTwo",L"images/gnome-walk-right-2.png"}, };

/**
 * Constructor for SpartyGnome
 * @param game Game this level is apart of
 */
SpartyGnome::SpartyGnome(Game *game, double x, double y) : Item(game)
{
    mItemImage = std::make_shared<wxImage>(Gnome, wxBITMAP_TYPE_ANY);
    SetImage(mItemImage);
    SetLocation(x, y);

}

/**
 * Draw front SpartyGnome image
 * @param graphics The wxWidgets graphics context on which to draw
 */
void SpartyGnome::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mLeft && !mRight)
    {
       DrawLeft(graphics);
    }
    else if (mRight && !mLeft)
    {
        DrawRight(graphics);
    }
    else
    {
        mItemImage = std::make_shared<wxImage>(image_map["Gnome"], wxBITMAP_TYPE_ANY);
    }

    mGnome = graphics->CreateBitmapFromImage(*mItemImage);

    int width = mItemImage->GetWidth();
    int height = mItemImage->GetHeight();
    graphics->DrawBitmap(mGnome, int(GetX() - width / 2),
                         int(GetY() - height / 2), width + 1, height);

}

/**
 * Left SpartyGnome images
 * @param graphics The wxWidgets graphics context on which to draw
 */
void SpartyGnome::DrawLeft(std::shared_ptr<wxGraphicsContext> graphics)
{
    mItemImage = std::make_shared<wxImage>(image_map["LeftGnomeOne"], wxBITMAP_TYPE_ANY);
    if((int(GetX()) % 2) == 0){
        mItemImage = std::make_shared<wxImage>(image_map["LeftGnomeTwo"], wxBITMAP_TYPE_ANY);
    }
}

/**
 * Right SpartyGnome images.
 * @param graphics The wxWidgets graphics context on which to drawt
 */
void SpartyGnome::DrawRight(std::shared_ptr<wxGraphicsContext> graphics)
{
    mItemImage = std::make_shared<wxImage>(image_map["RightGnomeOne"], wxBITMAP_TYPE_ANY);
    if((int(GetX()) % 2) == 0){
        mItemImage = std::make_shared<wxImage>(image_map["RightGnomeTwo"], wxBITMAP_TYPE_ANY);
    }
}

/**
 * update the gnome in time
 * @param elapsed Elapsed time in seconds
 */
void SpartyGnome::Update(double elapsed)
{

    Vector p = GetP();
    Vector newV = GetV();
    Vector newP = p;

    if (mJump)
    {
        //Gravity
        // Compute a new velocity with gravity added in.
        Vector thisV(GetV().X() , GetV().Y() + Gravity * elapsed);
        newV = thisV;

        // Update position
        newP = p + newV * elapsed;
        //mJumpTwice = true;
    }
    //mJumpTwice = false;

    //Try updating the X location
    SetLocation(newP.X(), p.Y() );

    auto collided = GetGame()->CollisionTest(this);

    for (auto item  : collided)
    {
        HorizontalVisit visitor;
        visitor.SetGnome(this);
        item->Accept(&visitor);
    }
    // Update new P
    newP.SetX(GetP().X());

    // Try updating the Y direction
    SetLocation(newP.X(), newP.Y() + Epsilon);
    collided = GetGame()->CollisionTest(this);

    for (auto item  : collided)
    {
        //ItemVisitor visitor;
        VerticalVisit visitor;
        visitor.SetGnome(this);
        item->Accept(&visitor);
    }
    // Update new P
    newP.SetY(GetP().Y());

    // Update the velocity and position
    SetV(newV);
    SetLocation(newP.X(), newP.Y());
    if(GetY() > GetHeight() + 1024)
    {
        GetGame()->SetFall(true);

        //ResetVelocity();

    }

}

void SpartyGnome::ResetVelocity()
{
    // Reset Gnome position
    SetLocation(500, 550); // Position
    SetV(Vector(0, -800)); // velocity
    //GetGame()->SetFall(false);

    mJump = false;
}

void SpartyGnome::OnLeft(double elapsed)
{
    // The current position
    Vector p = GetP();

    // Compute a new velocity with HorizontalSpeed added in.
    Vector newV(GetV().X() - HorizontalSpeed * elapsed , GetV().Y());

    // Update position
    p = p + newV * elapsed;

    //
    // Update position
    //
    SetLocation(p.X(), GetP().Y());


}

void SpartyGnome::OnRight(double elapsed)
{
    // The current position
    Vector p = GetP();

    // Compute a new velocity with HorizontalSpeed added in.
    Vector newV(GetV().X() + HorizontalSpeed * elapsed, GetV().Y());

    // Update position
    p = p + newV * elapsed;

    //
    // Update position
    //
    SetLocation(p.X(), GetP().Y());

}
