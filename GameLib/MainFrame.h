/**
 * @file MainFrame.h
 * @author Will K
 * @author William Alff
 *
 * Main Frame of App
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H

class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    /// View class for our game
    GameView* mGameView;

    void OnExit(wxCommandEvent& event);
    void InternalOnPopupMenu(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
public:
    void Initialize();
};

#endif //PROJECT1_MAINFRAME_H
