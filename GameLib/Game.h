/**
 * @file Game.h
 * @author LeeAnn Alsaeed
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include "Level.h"
#include "SpartyGnome.h"
#include "Item.h"
#include "ItemDec.h"
#include "MoneyDec.h"
#include "PlatformDec.h"
#include "Scoreboard.h"
#include "Game.h"
#include <map>
#include <memory>
#include <random>
#include <wx/graphics.h>

/**
 * The main game class.
 */
class Game {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

    /// Random number generator
    std::mt19937 mRandom;

    /// Handles window scaling
    double mScale = 0;

    /// Level we are currently on
    std::shared_ptr<Level> mLevel;

    /// Map for regular declarations, takes id and gives declaration
    std::map<std::wstring, ItemDec> mItemDecs;

    /// Map for money declarations, takes id and gives declare money
    std::map<std::wstring, MoneyDec> mMoneyDecs;

    /// Map for platform declarations, takes id and gives declare platform
    std::map<std::wstring, PlatformDec> mPlatformDecs;

    /// String containing path to image directory
    std::wstring mImageDirectory;

    /// Gnome in our game
    std::shared_ptr<SpartyGnome> mGnome;

    /// Vector of items in the level
    std::vector<std::shared_ptr<Item>> mItems;

    bool mLose = false;

    bool mFall = false;

    std::shared_ptr<Scoreboard> mScoreboard;

    double mScoreMultiplier = 1.0;

    bool mDoor = false;

    bool mInvincible = false;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

public:
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height, std::shared_ptr<SpartyGnome> gnome);

    void OnDrawBackground(wxDC *dc);

//    void OnDrawLevelBackground(std::shared_ptr<Level> level, wxDC *dc);

    /**
     * Get the width of the game
     * @return Game width in pixels
     */
    int GetWidth() const { return mBackground->GetWidth(); }

    /**
     * Get the height of the game
     * @return Game height in pixels
     */
    int GetHeight() const { return mBackground->GetHeight(); }

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}

    void OnDrawSpartyGnome(std::shared_ptr<SpartyGnome> gnome, std::shared_ptr<wxGraphicsContext> graphics);

    void OnDrawScoreboard(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Scoreboard> scoreboard);

    ItemDec GetItemDec(const std::wstring& id) { return mItemDecs[id]; }

    const std::wstring& GetImageDirectory() { return mImageDirectory; }

    void LoadXml(const wxString& filename);

    void Clear();

    /**
    * Updates the animation
    * @param elapsed time since last update
    */
    void Update(double elapsed);

    void LoadXmlItems(wxXmlNode* node);

    void LoadXmlDeclarations(wxXmlNode* node);

    MoneyDec GetMoneyDec(const std::wstring& id) { return mMoneyDecs[id]; }

    PlatformDec GetPlatformDec(const std::wstring& id) { return mPlatformDecs[id]; }

    void PrintMessage(std::shared_ptr<SpartyGnome> gnome, std::shared_ptr<wxGraphicsContext> graphics, double elapsed);

    std::vector<std::shared_ptr<Item>> CollisionTest(SpartyGnome * gnome);

    void SetLose(bool lose) { mLose = lose; }

    void SetFall(bool fl) { mFall = fl; }

    void SetDoorCol(bool dr) { mDoor = dr; }

    bool GetDoorCol() { return mDoor; }

    bool GetLose() { return mLose; }

    void RemoveItem(Item* item);

    std::shared_ptr<Scoreboard> GetScoreboard() { return mScoreboard; }

    void SetScoreMultiplier(double value) { mScoreMultiplier = value; }

    void AddScoreMultiplier(double value) { mScoreMultiplier += value; }

    double GetScoreMultiplier() { return mScoreMultiplier; }

    void ResetLevel(std::shared_ptr<SpartyGnome> gnome);

    void SetInvincible(bool invincible) { mInvincible = invincible; };

    bool GetInvincibilityStatus() { return mInvincible; }

    void SetScoreboard(std::shared_ptr<Scoreboard> scoreboard) { mScoreboard = scoreboard; }

    void PrintStartMessage(std::shared_ptr<wxGraphicsContext> graphics, std::wstring level);
};

#endif //PROJECT1_GAME_H
