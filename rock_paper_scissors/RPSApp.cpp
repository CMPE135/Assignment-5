#include "RPSApp.hpp"

bool RPSApp::OnInit() 
{
	if (!wxApp::OnInit()) return false;

	RPSFrame *frame = new RPSFrame();
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(RPSApp);