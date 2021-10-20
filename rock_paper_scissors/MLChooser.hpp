#ifndef MLCHOOSER_H
#define MLCHOOSER_H

#include "Choice.hpp"
#include <map>

class MLChooser {
  public:
    MLChooser();
    static string TYPE;
    map<string,map<string,int>> frequency;
    Choice makeChoice();
    Choice predictChoice();
    void feedOpponentChoice(Choice choice);
    void postGame();
    string getName();
  private:
    string curSequence;
    Choice predict;
    void initFrequencyMap(int n, string sequence);
    void loadFile();
};


#endif