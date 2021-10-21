#ifndef __RPSFRAME_H__
#define __RPSFRAME_H__

#include <iostream>
#include "ComputerPlayer.hpp"
#include <wx/wx.h>

using namespace std;

class RPSFrame: public wxFrame {
  public:
    RPSFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  private:
    ComputerPlayer computer;
    wxStaticText *roundCount;
    wxStaticText *humanChoiceName;
    wxStaticText *predictChoiceName;
    wxStaticText *computerChoiceName;
    wxStaticText *winnerName;
    wxStaticText *humanWinCount;
    wxStaticText *computerWinCount;
    wxStaticText *tieCount;
	void OnRock(wxCommandEvent& event);
    void OnPaper(wxCommandEvent& event);
    void OnScissors(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void endRound(Choice choice);
    void updateComputerChoices();
    int round;
    int humanWin;
    int computerWin;
    int tie;
    Choice predictChoice;
    Choice computerChoice;
};

#endif // __RPSFRAME_H__