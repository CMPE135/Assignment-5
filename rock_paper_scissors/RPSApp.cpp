#include "RPSApp.hpp"

bool RPSApp::OnInit() 
{
	if (!wxApp::OnInit()) return false;

	RPSFrame *frame = new RPSFrame("Rock Paper Scissors: 20 rounds/game", wxPoint(50,50), wxSize(500,440));
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(RPSApp);