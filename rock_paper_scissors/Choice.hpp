#ifndef CHOICE_H
#define CHOICE_H

#include <iostream>
#include <string>

using namespace std;

enum Choice {
    ROCK,
    PAPER,
    SCISSORS,
};

inline string toString(Choice choice) {
    if (choice == ROCK)    return "Rock";
    if (choice == PAPER)   return "Paper";
    return "Scissors";
}

inline ostream& operator << (ostream& ofs, Choice choice) {
    ofs << toString(choice);
    return ofs;
}

inline bool operator > (Choice choice1, Choice choice2) {
    if (choice1 == ROCK)    return choice2 == SCISSORS;
    if (choice1 == PAPER)   return choice2 == ROCK;
    return choice2 == PAPER;
}

inline string toOneChar(Choice choice) {
    return toString(choice).substr(0, 1);
}



#endif