/**
 * @file Scoreboard.cpp
 * @author William Alff, Maria Pacifico
 */

#include "pch.h"
#include "Scoreboard.h"
#include <wx/graphics.h>
#include <string>

using namespace std;

/**
 * Draws the scoreboard
 * @param graphics
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxColour bkColor(*wxBLACK);
    wxColour textColor(*wxBLUE);
    wxFont font(60, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    graphics->SetFont(font, textColor);
    string timeString;

    // Longer than a minute
    if (mTime >= 60)
    {
        long minutes = mTime / 60;
        long seconds = mTime % 60;

        // Set the minutes
        if (minutes >= 10)
        {
            timeString = (to_string(minutes))+':';
        }
        else
        {
            timeString = ("0"+to_string(minutes))+':';
        }

        // Set the seconds
        if (seconds >= 10)
        {
            timeString = timeString+to_string(seconds);
        }
        else
        {
            timeString = timeString+'0'+to_string(seconds);
        }
    }

    // Longer than 10 seconds, but less than a minute
    else if (mTime >= 10)
    {
        timeString = "00:"+(to_string(mTime));
    }

    // Less than ten seconds
    else
    {
        timeString = "00:0"+(to_string(mTime));
    }

    graphics->DrawText(timeString, mXTimer, mY);
    graphics->DrawText('$'+to_string(mTotalMoney), mXPoints, mY);
}