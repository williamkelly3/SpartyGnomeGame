/**
 * @file Level.cpp
 * @author Will K, Maria Pacifico
 */

#include "pch.h"
#include "Level.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "GameView.h"

using namespace std;

/**
 * Level Constructor
 * @param game The game object
 * @param filename Background of this level
 */
Level::Level(Game *game, const std::wstring &filename)
{
    mBackground = std::make_unique<wxBitmap>(
            filename, wxBITMAP_TYPE_ANY);
    mGame = game;
}

/**
 * Draw the level's background
 * @param dc The device context to draw on
 */
void Level::OnDrawBackground(wxDC *dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);
    dc->DrawBitmap(*mBackground, mBackground->GetWidth(), 0);
}

/**
 * Draw the items in the level
 * @param graphics The device context to draw on
 */
/*void Level::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    int size = mItems.size();
    for (int i = 0; i < size; i++)
    {
        mItems[i]->Draw(graphics);
    }
}*/

/*void Level::Clear()
{
    mItems.clear();
}*/

/*void Level::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}*/