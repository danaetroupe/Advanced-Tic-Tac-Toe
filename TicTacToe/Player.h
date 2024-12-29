#pragma once
#include <string>
using namespace std;

class Player
{
    string firstName = "";
    string lastName = "";
    int nameLength = 0;
    
    int wins = 0;
    int losses = 0;
    int draws = 0;

  public:
    bool assignName(string fullName);
    string getFirstName();
    string getFullName();

    int getWins();
    int getLosses();
    int getDraws();

    void addWin();
    void addLoss();
    void addDraw();

    int getNameLength();
};