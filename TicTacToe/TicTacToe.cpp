#include "TicTacToe.h"
#include <iostream>
using namespace std;

// ----------------------
// TicTacToe Constructor
// ----------------------
TicTacToe::TicTacToe()
{
    getPlayers();
    play();
}

// ----------------------
// TicTacToe DeConstructor
// ----------------------
TicTacToe::~TicTacToe() 
{
    for (int i = 0; i < playerAmt; i++) 
    { 
        delete players[i];
    }
}

// ------------------------------------------
// Gets Values to Draw Board
// ------------------------------------------
void TicTacToe::getBoardValues() 
{
    bool valid = false;
    string input;
    
    cout << "\nPlease enter the dimension of the board." << endl;
    
    // Get rows
    while (!valid) 
    {
        cout << "\nEnter the number of rows    -> ";
        getline(cin, input);
        if (!isNumber(input) || stoi(input) < MIN_ROWS || stoi(input) > MAX_ROWS) 
        { 
            showError(); 
        }
        else 
        { 
            rows = stoi(input); 
            valid = true; 
        }
    }
    
    // Get columns
    valid = false;
    while (!valid) 
    {
        cout << "\nEnter the number of columns -> ";

        getline(cin, input);
        int c = stoi(input);

        if (!isNumber(input) || c < MIN_COLUMNS || c > MAX_COLUMNS) 
        { 
            showError(); 
        }
        else 
        { 
            columns = c; 
            valid = true; 
        }
    }
}

// ------------------------------------------
// Draws Tic Tac Board Based on Stored Values
// ------------------------------------------
void TicTacToe::drawBoard()
{
    cout << "\n";
    drawNumbers();
    for (int i = 0; i < rows; i++) 
    {
        drawHorizontalBorder();
        drawVerticalBorder(i);
    }
    drawHorizontalBorder();
    drawNumbers();
}

// ------------------------------------------------------------------------------------
// Prompts Users for Player1 and Player2 Full Names and Determines Starting Player
// ------------------------------------------------------------------------------------
void TicTacToe::getPlayers()
{
    string input;

    // Get number of players
    bool valid = false;
    while (!valid)
    {
        cout << "\nPlease enter number of players -> ";

        getline(cin, input);

        if (isNumber(input) && stoi(input) <= MAX_PLAYERS && stoi(input) >= MIN_PLAYERS)
        {
            playerAmt = stoi(input);
            valid = true;
        }
        else 
        { 
            showError(); 
        }
    }


    // Get player names
    for (int i = 0; i < playerAmt; i++) 
    {
        Player* newPlayer = new Player();
        bool valid = false;
        while (!valid) 
        {
            cout << '\n' << to_string(i + 1) << ". Enter full name -> ";

            getline(cin, input);
            valid = newPlayer->assignName(input);
            if (!valid) 
            { 
                showError(); 
            }
        }
        players[i] = newPlayer;
    }
}

// ---------------------------------------------------------------
// Check current values to see game state (win, draw, or continue)
// ---------------------------------------------------------------
TicTacToe::cases TicTacToe::checkWin()
{
    cases state = Continue;
    int topRow = lastRow - 2;
    int btmRow = lastRow + 2;
    int leftCol = lastCol - 2;
    int rightCol = lastCol + 2;

    // Check Diagonal
    if (checkValues(topRow, leftCol, btmRow, rightCol, 1, 1)) 
    { 
        state = Win; 
    }
    if (checkValues(topRow, rightCol, btmRow, leftCol, 1, -1))
    {
        state = Win;
    }

    // Check Cross
    if (checkValues(topRow, lastCol, btmRow, lastCol, 1, 0))
    {
        state = Win;
    }
    if (checkValues(lastRow, leftCol, lastRow, rightCol, 0, 1))
    {
        state = Win;
    }

    // Check Draw
    if (state == Continue && moves >= (rows * columns))
    {
        return Draw;
    }
    
    return state;
}

// -------------------------------
// Update values if win condition
// -------------------------------
bool TicTacToe::checkValues(int row, int col, int endRow, int endCol, int rowDirection, int colDirection)
{
    char currPiece = char(SEQUENCE_START + currentPlayer);
    int count = 0;
    char piece;

    while ((row != endRow + rowDirection || col != endCol + colDirection))
    {
        if (row >= 0 && row < rows && col >= 0 && col < columns)
        {
            piece = board[row][col];

            if (tolower(piece) == currPiece)
            {
                count++;
            }
            else if (count >= 3)
            {
                break;
            }
            else
            {
                count = 0;
            }
        }
        else if (count >= 3)
        {
            break;
        }
        else
        {
            count = 0;
        }

        row += rowDirection;
        col += colDirection;
    }

    if (count >= 3) 
    { 
        for (int i = 0; i < count; i++) 
        {
            row -= rowDirection;
            col -= colDirection;
            board[row][col] = toupper(currPiece); 
        } 
        return true; 
    }
    return false;
};

// -----------------------
// Runs main game loop
// -----------------------
void TicTacToe::play()
{
    string input;
    gameNum++;

    getBoardValues();
    clearBoard();

    cases status = Continue;
    while (status == Continue)
    {
        drawBoard();

        // Move Selection
        selectMove();

        status = checkWin();
        if (status == Continue) 
        { 
            switchPlayer(1); 
        }
    }
    // Display game conditions
    if (status == Win)
    {
        cout << "\nCongratulations! You win!" << endl;
        // Award points
        for (int i = 0; i < playerAmt; i++) 
        {
            if (i == currentPlayer) 
            { 
                players[i]->addWin(); 
            }
            else 
            { 
                players[i]->addLoss(); 
            }
        }
        switchPlayer(1);
    }
    else
    {
        cout << "\nSorry, you drew. :(" << endl;
        for (int i = 0; i < playerAmt; i++) 
        { 
            players[i]->addDraw(); 
        }
        switchPlayer(-1);
    }

    // Display Player Stats
    showStats();
    drawBoard();

    // Prompt player to play again
    bool valid = false;
    while (!valid)
    {
        cout << "\nPlay again? (Y/N) -> ";
        getline(cin, input);

        if (size(input) != 1)
        { 
            showError(); 
            continue;
        }

        // Evaluate input
        switch (toupper(input[0]))
        {
            case('Y'):
                valid = true;
                play();
                break;
            case('N'):
                valid = true;
                cout << "Thanks for playing!" << endl;
                break;
            default:
                showError();
        }
    }
}

// ---------------------------------
// Resets board and clears values.
// ---------------------------------
void TicTacToe::clearBoard()
{
    for (int row = 0; row < MAX_ROWS; row++)
    {
        fill(board[row] , board[row] + MAX_COLUMNS, ' ');
    }

    moves = 0;
}

// -------------------------
// Draw horizontal lines
// -------------------------
void TicTacToe::drawHorizontalBorder() 
{
    cout << "  ";
    for (int i = 0; i < columns; i++) 
    { 
        cout << " ---"; 
    }
    cout << endl;
}

// -------------------------
// Draw vertical lines
// -------------------------
void TicTacToe::drawVerticalBorder(int row)
{
    cout << char('A' + row);
    for (int i = 0; i < columns; i++) 
    { 
        cout << " | " << board[row][i]; 
    }
    cout << " | " << char('A' + row) << endl;
}

// -------------------------
// Draw column numbers
// -------------------------
void TicTacToe::drawNumbers()
{
    cout << ' ';
    for (int i = 0; i < columns; i++) 
    { 
        int value = i + 1;

        if (value <= 10) 
        { 
            cout << " ";
        }
        
        cout << "  " << value;
    }
    cout << endl;
}

// -------------------------
// Get player move
// -------------------------
void TicTacToe::selectMove()
{
    char currentPiece = char(SEQUENCE_START + currentPlayer);
    bool valid = false;
    string input;

    while (!valid)
    {
        cout << "\n" << players[currentPlayer]->getFirstName() << ", please select your move(" << currentPiece << ") -> ";
        getline(cin, input);

        if (size(input) >= 2) 
        { 
            valid = true; 
        }

        // Determine row position
        if (valid)
        {
            char letter = toupper(input[0]);
            if (letter >= 'A' || letter <= 'Z') 
            { 
                lastRow = letter - 'A'; 
                valid = true; 
            }
        }

        // Determine column position
        if (valid)
        { 
            string nums = input.substr(1);
            if (isNumber(nums) && stoi(nums) > 0 && stoi(nums) <= columns) 
            { 
                lastCol = stoi(nums) - 1; 
            }
            else 
            { 
                valid = false; 
            }
        }
        
        if (valid && board[lastRow][lastCol] != ' ') 
        { 
            valid = false; 
        }

        if (!valid) 
        { 
            showError(); 
        }
    }
    
    // Select move
    board[lastRow][lastCol] = currentPiece;
    moves++;
}

// --------------------------------------
// Check if string is composed of digits
// --------------------------------------
bool TicTacToe::isNumber(string input)
{
    if (size(input) == 0)
    {
        return false;
    }
    for (char c : input) 
    { 
        if (!isdigit(c)) 
        { 
            return false; 
        } 
    }
    return true;
}

// -------------------------
// Selects next player
// -------------------------
void TicTacToe::switchPlayer(int direction)
{
    currentPlayer += direction;

    if (currentPlayer >= playerAmt) 
    { 
        currentPlayer = 0; 
    }
    else if (currentPlayer < 0) 
    { 
        currentPlayer = playerAmt - 1; 
    }
}

// --------------------------
// Display player statistics
// --------------------------
void TicTacToe::showStats()
{
    int maxLength = 0;
    int nameLength;

    for (int i = 0; i < playerAmt; i++) 
    {
        nameLength = players[i]->getNameLength();
        maxLength = (nameLength > maxLength) ? nameLength : maxLength;
    }

    cout << "\nTotal games played = " << gameNum << '\n' << endl;

    drawBuffer(maxLength + 1);
    drawStatsBorder();
    drawBuffer(maxLength + 1);
    cout << "|  WIN | LOSS | DRAW |" << endl;

    for (int i = 0; i < playerAmt; i++) 
    {
        Player* p = players[i];

        // Draw Border
        drawBuffer(maxLength + 1);
        drawStatsBorder();

        // Show Name
        drawBuffer(maxLength - p->getNameLength());
        cout << p->getFullName() << " |";
        
        // Show Wins
        drawBuffer(5 - size(to_string(p->getWins())));
        cout << p->getWins() << " |";

        // Show Losses
        drawBuffer(5 - size(to_string(p->getLosses())));
        cout << p->getLosses() << " |";

        // Show Draws
        drawBuffer(5 - size(to_string(p->getDraws())));
        cout << p->getDraws() << " |" << endl;
    }

    drawBuffer(maxLength + 1);
    drawStatsBorder();
}
// -----------------------------------------
// Show error message for invalid input
// -----------------------------------------
void TicTacToe::showError() 
{ 
    cout << "Input invalid. Please try again." << endl; 
}

// -----------------------------------------
// Draw horizontal border for stats display
// -----------------------------------------
void TicTacToe::drawStatsBorder()
{
    cout << " ------ ------ ------" << endl;
}

// -----------------------------------------
// Display num amount of spaces
// -----------------------------------------
void TicTacToe::drawBuffer(int num)
{
    for (int i = 0; i < num; i++) 
    { 
        cout << ' '; 
    }
}