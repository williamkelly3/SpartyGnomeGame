/**
 * @file Game.cpp
 * @author LeeAnn Alsaeed, Lydia Wibbelman
 * @author William Alff
 */

#include "pch.h"
#include "Game.h"
#include <algorithm>
#include "Level.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "ItemPlatform.h"
#include "ItemDoor.h"
#include "ItemTuitionUp.h"
#include "ItemInvincibility.h"
#include "ItemWall.h"
#include "ItemBackground.h"
#include "ItemVillain.h"
#include "ItemMoney.h"

using namespace std;

/// Game area height in virtual pixels
const static int Height = 1024;

/// Initial item X location
const int InitialX = 200;

/// Initial item Y location
const int InitialY = 200;

/**
* Game Constructor
*/
Game::Game()
{
    mBackground = make_unique<wxBitmap>(
            L"images/backgroundForest.png", wxBITMAP_TYPE_ANY);

    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());
    mImageDirectory = L"images";
}

/**
 * Draw the game's background
 * @param dc The device context to draw on
 */
void Game::OnDrawBackground(wxDC *dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);
    dc->DrawBitmap(*mBackground, mBackground->GetWidth(), 0);
}

///**
// * Draw the level's background
// * @param dc The device context to draw on
// * @param level the level object we're drawing
// */
//void Game::OnDrawLevelBackground(std::shared_ptr<Level> level, wxDC *dc)
//{
//    level->OnDrawBackground(dc);
//    level->DrawPlats(this,dc);
//}

/**
 * Draw the game area
 * @param graphics The wxWidgets graphics context on which to draw
 * @param width Width of the client window
 * @param height Height of the client window
 * @param gnome gnome we are drawing
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height, std::shared_ptr<SpartyGnome> gnome)
{
    //
    // Automatic Scaling
    //
    mScale = double(height) / double(Height);
    graphics->Scale(mScale, mScale);

    auto virtualWidth = (double)width/mScale;
    graphics->PushState();

    //
    // Draw in virtual pixels on the graphics context
    //
    auto xOffset = (double)-gnome->GetX() + virtualWidth / 2.0f;
    //float xOffset = ((width - virtualWidth * mScale) / 2);
    //float yOffset = ((height - Height * mScale) / 2);
    graphics->PushState();
    graphics->Translate(xOffset, 0);

    //mLevel->OnDraw(graphics);  //breaks game - dont uncomment yet
    int size = mItems.size();
    for (int i = 0; i < size; i++)
    {
        mItems[i]->Draw(graphics);
    }
    if(this->GetLose())
    {
        gnome->Draw(graphics);
    }
    else
    {
        gnome->Draw(graphics);
    }
    graphics->PopState();
}

/**
 * Draw's the scoreboard in the game
 * @param graphics The wxWidgets graphics context on which to draw
 * @param scoreboard The scoreboard we are drawing
 */
void Game::OnDrawScoreboard(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Scoreboard> scoreboard)
{
    scoreboard->Draw(graphics);
    mScoreboard = scoreboard;
}

/**
 * Loads the XML files that make up the game's levels.
 * @param filename The path to the XML file we are loading in
 */
void Game::LoadXml(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"error");
        return;
    }

    Clear();

    auto root = xmlDoc.GetRoot();

    long x, y;
    root->GetAttribute(L"start-x").ToLong(&x);
    root->GetAttribute(L"start-y").ToLong(&y);
    //mGnome = std::make_shared<SpartyGnome>(this, x, y);

    auto child = root->GetChildren();
    for ( ; child; child=child->GetNext())
    {
        if (child->GetName() == L"declarations")
        {
            LoadXmlDeclarations(child);
        }
        else if (child->GetName() == L"items")
        {
            LoadXmlItems(child);
        }
    }
}

/**
 * Loads in the item part of the XML file
 * @param node The section of the XML file we are loading in
 */
void Game::LoadXmlItems(wxXmlNode* node)
{
    auto child = node->GetChildren();
    for ( ; child; child=child->GetNext())
    {
        shared_ptr<Item> item;
        if (child->GetName() == L"money")
        {
            item = make_shared<ItemMoney>(this);


        }
        else if (child->GetName() == L"platform")
        {
            item = make_shared<ItemPlatform>(this);

        }
        else if (child->GetName() == L"background")
        {
            item = make_shared<ItemBackground>(this);


        }
        else if (child->GetName() == L"wall")
        {
            item = make_shared<ItemWall>(this);

            item->XmlLoad(child);

        }
        else if (child->GetName() == L"tuition-up")
        {
            item = make_shared<ItemTuitionUp>(this);


        }
        else if (child->GetName() == L"invincibility")
        {
            item = make_shared<ItemInvincibility>(this);


        }
        else if (child->GetName() == L"door")
        {
            item = make_shared<ItemDoor>(this);

        }
        else if (child->GetName() == L"villain")
        {
            item = make_shared<ItemVillain>(this);

        }

        if (item != nullptr)
        {
            item->XmlLoad(child);
            mItems.push_back(item);
        }
    }
}

/**
 * Loads in the declaration part of the XML file.
 * @param node The section of the XML file we are loading in
 */
void Game::LoadXmlDeclarations(wxXmlNode* node)
{
    auto child = node->GetChildren();

    for ( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        auto id = child->GetAttribute(L"id");

        if (mItemDecs.find(id.ToStdWstring()) != mItemDecs.end())
        {
            continue;
        }
        if (name == L"background" ||  name == L"wall" || name == L"tuition-up" ||
        name == L"door" || name == L"villain" || name == L"invincibility")
        {
            auto image = child->GetAttribute(L"image");
            ItemDec declare(id.ToStdWstring(), image.ToStdWstring());
            mItemDecs[id.ToStdWstring()] = declare;
        }
        else if (name == L"money")
        {
            auto image = child->GetAttribute(L"image");
            auto value_str = child->GetAttribute(L"value");
            double value;
            value_str.ToDouble(&value);
            MoneyDec declare(id.ToStdWstring(), image.ToStdWstring(), value);
            mMoneyDecs[id.ToStdWstring()] = declare;
        }
        else if (name == L"platform")
        {
            auto left = child->GetAttribute(L"left-image");
            auto mid = child->GetAttribute(L"mid-image");
            auto right = child->GetAttribute(L"right-image");
            PlatformDec declare(id.ToStdWstring(), left.ToStdWstring(), mid.ToStdWstring(),
                    right.ToStdWstring());
            mPlatformDecs[id.ToStdWstring()] = declare;
        }
    }
}

/**
 * Clears all items in list of items.
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}

/**
 * Draw Sparty Gnome
 * @param gnome The gnome we're drawing
 * @param graphics The device context to draw on
 */
void Game::OnDrawSpartyGnome(std::shared_ptr<SpartyGnome> gnome, std::shared_ptr<wxGraphicsContext> graphics)
{
    gnome->Draw(graphics);
    wxFont font(60, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour textColor(*wxBLUE);
    graphics->SetFont(font, textColor);
    //graphics->DrawText(to_string(gnome->GetX()), 400, 400); ///To track Gnome's location
    //graphics->DrawText(to_string(gnome->GetY()), 400, 350);

}

/**
 * Draws the message begin
 * @param graphics draws message
 * @param level level to draw message for
 */
void Game::PrintStartMessage(std::shared_ptr<wxGraphicsContext> graphics, std::wstring level)
{
    wxFont font(60, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour textColor(*wxBLUE);
    graphics->SetFont(font, textColor);
    graphics->DrawText("Level " + level + " Begin!", 500, 500);
}

/**
 * Print "Level Complete" message
 * @param gnome The gnome we're drawing
 * @param graphics The device context to draw on
 */
void Game::PrintMessage(std::shared_ptr<SpartyGnome> gnome, std::shared_ptr<wxGraphicsContext> graphics, double elapsed)
{
    wxFont font(60, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxColour textColor(*wxBLUE);
    graphics->SetFont(font, textColor);
    graphics->DrawText("Level Begin!", 500, 500);

    if (mDoor) {
        wxFont font(60, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        wxColour textColor(*wxBLUE);
        graphics->SetFont(font, textColor);
        graphics->DrawText("Level Complete!", 400, 400);

        //ResetLevel(gnome);

        //door = false;
    }

    if (mFall) {
        wxFont font(60, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        wxColour textColor(*wxBLUE);
        graphics->SetFont(font, textColor);
        graphics->DrawText("You Lose!", 400, 400);

        ResetLevel(gnome);
        //double pause = elapsed;
        //while (pause + 2 != elapsed){

        //}
        mFall = false;
    }

    if (mLose)
    {
        wxFont font(60, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        wxColour textColor(*wxBLUE);
        graphics->SetFont(font, textColor);
        graphics->DrawText("You Lose!", 400, 400);
        gnome->SetLocation(gnome->GetX(), gnome->GetY()+50);
        ResetLevel(gnome);
        mLose = false;
    }
}


std::vector<std::shared_ptr<Item>> Game::CollisionTest(SpartyGnome * gnome)
{
    shared_ptr<Item> collided;
    bool collision;
    std::vector<std::shared_ptr<Item>> collided_items;

    for (auto item  : mItems)
    {
        collision = item->CollisionTest(gnome);

        if (collision)
        {

            collided_items.push_back(item);

        }
        //else
        //{
            //collision = WallCollided->CollisionTest(gnome);
            //if(collision)
            //{
               // return WallCollided;
            //}
        //}

    }
    //return collision;
//    if (collided_items.size() != 0)
//    {
//        return collided_items;
//    }
//    else
//    {
//        return nullptr;
//    }
    return collided_items;

}

void Game::RemoveItem(Item* item)
{

}

void Game::ResetLevel(std::shared_ptr<SpartyGnome> gnome)
{
    // Reset Gnome position
    gnome->ResetVelocity();
    gnome->SetJump(false);
    SetLose(false);
    //this->SetFall(false);
//    mStopWatch.Start(0);
//    mScoreboard->SetStopwatch(mStopWatch);

    this->GetScoreboard()->ResetScore();
    this->SetScoreMultiplier(1.0);
    this->SetInvincible(false);
}


