#include "ComputerPlayer.hpp"

ComputerPlayer::ComputerPlayer() {
    chooser = new MLChooser();
}

Choice ComputerPlayer::makeChoice() {
    return chooser->makeChoice();
}

Choice ComputerPlayer::predictChoice() 
{
    return chooser->predictChoice();
}

string ComputerPlayer::getName() {
    return "Computer with " + chooser->getName();
}

void ComputerPlayer::feedOpponentChoice(Choice choice) {
    chooser->feedOpponentChoice(choice);
}

void ComputerPlayer::postGame() {
    chooser->postGame();
}