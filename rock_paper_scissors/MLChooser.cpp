#include "MLChooser.hpp"
#include <fstream>

string MLChooser::TYPE = "ML";

MLChooser::MLChooser() {
    initFrequencyMap(5, "");
    loadFile();
    predict = Choice(-1);
}

// Make choice based on prediction and then reset prediction
Choice MLChooser::makeChoice() {
    if (predict == -1) predictChoice();
    Choice choice = Choice((predict + 1) % 3);
    predict = Choice(-1);
    return choice;
}

// Predict opponent's choice based on frequency data, prediction is stored
// If frequency data is not enough, it generates a random choice
Choice MLChooser::predictChoice() 
{
    if (curSequence.length() == 4) {
        map<string, int> nextFreq = frequency[curSequence];
        if (nextFreq[toOneChar(ROCK)] == nextFreq[toOneChar(PAPER)]) {
            predict = rand() % 2 == 0 ? ROCK : PAPER;
        } else if(nextFreq[toOneChar(ROCK)] > nextFreq[toOneChar(PAPER)]) {
            predict = ROCK;
        } else {
            predict = PAPER;
        }
        if (nextFreq[toOneChar(predict)] == nextFreq[toOneChar(SCISSORS)] && rand() % 2 == 0) {
            predict = SCISSORS;
        } else if(nextFreq[toOneChar(predict)] < nextFreq[toOneChar(SCISSORS)]) {
            predict = SCISSORS;
        }
    } else {
        predict = Choice(rand() % 3);
    }
    return predict;
}

// Update sequence of last five choices and its frequency
void MLChooser::feedOpponentChoice(Choice choice) {
    string c = toOneChar(choice);
    if (curSequence.length() == 4) {
        frequency[curSequence][c] += 1;
        curSequence.erase(0, 1);
    }
    curSequence += c;
}

// Save frequency data in file
void MLChooser::postGame() {
    ofstream ofs("previous_choices.txt");
    if(ofs.fail()) {
        cout << "Failed to create previous choices file" << endl;
        exit(1);
    }
    string sequence;
    string last;
    int freq;
    for (const auto &pair1 : frequency) {
        for (const auto &pair2 : pair1.second) {
            ofs << pair1.first + pair2.first << ": " << pair2.second <<"\n";
        }
    }
    ofs.close();
}

// Iterate all sequence possibilities by Depth First Traversal
// n is the number of digits left to traverse
void MLChooser::initFrequencyMap(int n, string sequence) {
    if (n == 1) {
        frequency[sequence] = {
            {toOneChar(ROCK), 0},
            {toOneChar(PAPER), 0},
            {toOneChar(SCISSORS), 0}
        };
        return;
    } 
    initFrequencyMap(n - 1, sequence + toOneChar(ROCK));
    initFrequencyMap(n - 1, sequence + toOneChar(PAPER));
    initFrequencyMap(n - 1, sequence + toOneChar(SCISSORS));
}

void MLChooser::loadFile() {
    ifstream ifs("previous_choices.txt");
    if(ifs.fail()) {
        cout << "Failed to open previous choices file" << endl;
        return;
    }
    string sequence;
    string last;
    int freq;
    while(ifs >> sequence >> freq) {
        sequence.pop_back();
        last = sequence.back();
        sequence.pop_back();
        frequency[sequence][last] = freq;
    }
    ifs.close();
}

string MLChooser::getName() {
    return "Machine Learning Chooser";
}