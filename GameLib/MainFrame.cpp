/**
 * @file MainFrame.cpp
 * @author Will K
 * @author William Alff
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty Gnome", wxDefaultPosition,  wxSize( 1000,800 ));

    auto sizer = new wxBoxSizer( wxVERTICAL );

    auto gameView = new GameView();
    gameView->Initialize(this);

    sizer->Add(gameView,1, wxEXPAND | wxALL );

    SetSizer( sizer );
    Layout();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    levelMenu->Append(IDM_LEVEL0, L"&Level 0", L"Go to Level 0");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1", L"Go to Level 1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2", L"Go to Level 2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3", L"Go to Level 3");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    SetMenuBar( menuBar );
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::InternalOnPopupMenu, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handler
 * @param event
 */
void MainFrame::InternalOnPopupMenu(wxCommandEvent& event)
{
    wxMessageBox(L"SpartyGnome",
                 L"About Sparty Gnome",
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}