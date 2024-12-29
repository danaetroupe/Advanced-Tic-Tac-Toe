#pragma once
#include <string>
#include "Player.h"
#include "global.h"
using namespace std;

class TicTacToe
{
    enum cases { Win, Draw, Continue };

    // Player Values
    int playerAmt = MIN_PLAYERS;
    Player* players[MAX_PLAYERS];
    int currentPlayer = START_PLAYER;

    // Board Values
    int rows = MIN_ROWS;
    int columns = MIN_COLUMNS;
    char board[MAX_ROWS][MAX_COLUMNS] = { ' ' };

    // Game
    int gameNum = 0;
    int moves = 0;
    int lastRow = 0;
    int lastCol = 0;

    // Methods
    void getPlayers();
    void getBoardValues();

    void drawBoard();
    void drawVerticalBorder(int row);
    void drawHorizontalBorder();
    void drawNumbers();
    void clearBoard();

    void drawStatsBorder();
    void drawBuffer(int num);
    void showStats();

    cases checkWin();
    bool checkValues(int row, int col, int endRow, int endCol, int rowDirection, int colDirection);
    void selectMove();
    void switchPlayer(int direction);
    void play();

    bool isNumber(string input);
    void showError();

public:
    TicTacToe();
    ~TicTacToe();
};