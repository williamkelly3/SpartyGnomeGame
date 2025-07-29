/**
 * @file GameView.h
 * @author LeeAnn Alsaeed
 * @author William Alff
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H

#include "Game.h"
#include "Scoreboard.h"

/**
 * View class for our Game
 */
class GameView : public wxWindow {
private:
    void OnPaint(wxPaintEvent& event);

    void OnAddLevel0(wxCommandEvent& event);
    void OnAddLevel1(wxCommandEvent& event);
    void OnAddLevel2(wxCommandEvent& event);
    void OnAddLevel3(wxCommandEvent& event);

    void ResetLevel();

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnTimer(wxTimerEvent& timer);

    /// An object that describes our game
    Game  mGame;
    /// The timer that allows for animation
    wxTimer mTimer;
    /// Frame duration in milliseconds
    const int FrameDuration = 30;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    /// The last stopwatch time
    long mTime = 0;
    /// Left key pressed variable
    //bool mLeft = false;
    /// Right key pressed variable
    //bool mRight = false;
    /// The Gnome in our game
    std::shared_ptr<SpartyGnome> mGnome;
    /// The scoreboard used by our game
    std::shared_ptr<Scoreboard> mScoreboard;
    /// Elapsed time
    double elapsed;

public:
    void Initialize(wxFrame* parent);

    void Load(std::wstring level);

    /**
    * Stop the timer so the window can close
    */
    void Stop() {mTimer.Stop();}


};

#endif //PROJECT1_GAMEVIEW_H
