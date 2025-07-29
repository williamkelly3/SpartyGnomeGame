/**
 * @file Scoreboard.h
 * @author William Alff, Maria Pacifico
 *
 * Class that measures and displays elapsed time as well as money collected by the player
 */

#ifndef PROJECT1_SCOREBOARD_H
#define PROJECT1_SCOREBOARD_H

#include <wx/dcbuffer.h>

/**
 * Class that measures and displays elapsed time as well as money collected by the player
 */
class Scoreboard {
private:
    /// The elapsed time during the game
    wxStopWatch mStopWatch;

    /// Total amount of money collected by the player
    int mTotalMoney = 0;

    /// Time to display
    long mTime = 0;

    /// X position of the Timer
    int mXTimer = 80;

    /// X position of the points
    int mXPoints = mXTimer + 1100;

    /// Y position of the scoreboard
    int mY = 40;


public:
    Scoreboard() = default;

    /// Copy constructor (disabled)
    Scoreboard(const Scoreboard &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Scoreboard &) = delete;

    /**
     * Setter for the amount of money
     * @param total Total money collected
     */
     void SetTotalMoney(int total){ mTotalMoney = total; }

     void IncreaseScore(int value) { mTotalMoney += value; }

     void ResetScore() { mTotalMoney = 0; }

     /**
      * Setter for the time
      * @param time the time to display
      */
     void SetTime(long time){ mTime = time; }

     void Draw(std::shared_ptr<wxGraphicsContext> graphics);

     wxStopWatch GetStopwatch(){ return mStopWatch; }

     void SetStopwatch(wxStopWatch watch){ mStopWatch = watch; }
};

#endif //PROJECT1_SCOREBOARD_H
