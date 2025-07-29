/**
 * @file GameView.cpp
 * @author LeeAnn Alsaeed
 * @author William Alff
 */

#include "pch.h"
#include "ids.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/stdpaths.h>
#include "GameView.h"
#include "Game.h"
#include "SpartyGnome.h"

using namespace std;

/// Maximum amount of time to allow for elapsed
const double MaxElapsed = 0.50;

int CurrentLevel = 0;

/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    mGnome = std::make_shared<SpartyGnome>(&mGame, 750, 570);
    mScoreboard = std::make_shared<Scoreboard>();
    mScoreboard->SetStopwatch(mStopWatch);
    mGame.SetScoreboard(mScoreboard);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddLevel0, this, IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddLevel1, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddLevel2, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddLevel3, this, IDM_LEVEL3);

    Load(L"1");
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mScoreboard->GetStopwatch().Time();
    elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mScoreboard->SetTime(mTime/1000);

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();
    auto size = GetClientSize();
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    if(mGame.GetDoorCol()){
        if(CurrentLevel == 1){
            Load(L"2");

        }
        else
        {
            Load(L"3");
        }
        mGame.SetDoorCol(false);
    }

    //
    // Prevent tunnelling
    //
    while (elapsed > MaxElapsed)
    {
        mGame.Update(MaxElapsed);
        mGnome->Update(MaxElapsed);

        elapsed -= MaxElapsed;
    }
    // Consume any remaining time
    if (elapsed > 0)
    {
        mGame.Update(elapsed);
        mGnome->Update(elapsed);
    }

    mGame.OnDrawBackground(&dc);
    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight(), mGnome);
    //mGame.OnDrawSpartyGnome(mGnome, graphics);
    mGame.OnDrawScoreboard(graphics, mScoreboard);
    mGame.PrintMessage(mGnome, graphics, elapsed);

    mGame.Update(elapsed);
}

/**
 * Resets each of the levels
 */
void GameView::ResetLevel()
{
    // Restart timer
//    mScoreboard->GetStopwatch().Start(0);
//    mStopWatch.Start(0);
    //mScoreboard->SetStopwatch(mStopWatch);

//    // Reset Gnome position
//    mGnome->ResetVelocity();
//    mGnome->SetJump(false);
//    mGame.SetLose(false);
//    mGame.GetScoreboard()->ResetScore();
//    mGame.SetScoreMultiplier(1.0);
    mGame.ResetLevel(mGnome);
}

/**
 * Handler for Level>Level 0
 * @param event Menu Event
 */
void GameView::OnAddLevel0(wxCommandEvent &event)
{
    // Load XML
    Load(L"0");
    ResetLevel();
}

/**
 * Handler for Level>Level 1
 * @param event Menu Event
 */
void GameView::OnAddLevel1(wxCommandEvent &event)
{
    Load(L"1");
    ResetLevel();
}

/**
 * Handler for Level>Level 2
 * @param event Menu Event
 */
void GameView::OnAddLevel2(wxCommandEvent &event)
{
    Load(L"2");
    ResetLevel();
}

/**
 * Handler for Level>Level 3
 * @param event Menu Event
 */
void GameView::OnAddLevel3(wxCommandEvent &event)
{
    Load(L"3");
    ResetLevel();
}

/**
 * Gets path to XML file and loads in the level.
 * @param level Level number we are loading in
 */
void GameView::Load(std::wstring level)
{
    CurrentLevel = std::stoi(level);
    const wxString filename = L"levels/level" + level + L".xml";
    mGame.LoadXml(filename);
    Refresh();
}

/**
 * Timer Events
 * @param timer timer event
 */
void GameView::OnTimer(wxTimerEvent& timer)
{
    Refresh();
}

/**
 * Keyboard Events
 * @param event Key down event
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode()) {
        case WXK_SPACE: {
            // space bar pressed
            if(!mGame.GetLose()) {
                if (!mGnome->GetJump())
                {
                    mGnome->SetV(Vector(0, -800));
                }
                mGnome->SetJump(true);
            }
            break;
        }
        case WXK_LEFT: {
            // left arrow pressed
            if(!mGame.GetLose()){
                if(!mGnome->GetRight()){
                    mGnome->OnLeft(elapsed);
                }
                mGnome->SetLeft(true);
            }
            break;
        }
        case WXK_RIGHT: {
            // right arrow pressed
            if(!mGame.GetLose()){
                if(!mGnome->GetLeft()){
                    mGnome->OnRight(elapsed);
                }
                mGnome->SetRight(true);
            }
            break;
        }
    }

    Refresh();
}

/**
 * Keyboard Events
 * @param event Key up event
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{
    switch (event.GetKeyCode()) {
        case WXK_RIGHT: {
            // right arrow released
            mGnome->SetRight(false);
            break;
        }
        case WXK_LEFT: {
            // left arrow released
            mGnome->SetLeft(false);
            break;
        }
    }
    Refresh();
}