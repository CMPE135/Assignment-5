#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "MLChooser.hpp"

class ComputerPlayer {
  public:
	ComputerPlayer();
	Choice makeChoice();
    Choice predictChoice();
	string getName();
	void feedOpponentChoice(Choice choice);
	void postGame();
  private:
	MLChooser* chooser;
};

#endif