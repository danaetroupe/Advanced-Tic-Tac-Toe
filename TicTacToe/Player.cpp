#include "Player.h"

// ------------------------------------------------------------------------
// Check if name is valid to be assigned to player, assign and parse if so
// ------------------------------------------------------------------------
bool Player::assignName(string fullName) 
{
	bool isFirst = true;
	string tempFirstName = "";
	string tempLastName = "";

	// Parse name
	for (char c : fullName) 
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
		{
			if (isFirst) 
			{ 
				tempFirstName += c; 
			}
			else 
			{ 
				tempLastName += c; 
			}
		}
		else if (c == ' ') 
		{
			if (isFirst) 
			{ 
				isFirst = false; 
			}
			else 
			{ 
				return false; 
			}
		}
		else 
		{ 
			return false; 
		}
	}

	if (isFirst) 
	{ 
		return false; 
	}

	// Format first name
	firstName += toupper(tempFirstName[0]);
	for (int i = 1; i < size(tempFirstName); i++) 
	{ 
		firstName += tolower(tempFirstName[i]); 
	}

	// Format last name
	lastName += toupper(tempLastName[0]);
	for (int i = 1; i < size(tempLastName); i++) 
	{ 
		lastName += tolower(tempLastName[i]); 
	}

	nameLength = size(fullName);
	
	return true;
}

// ------------------------
// Get player first name
// ------------------------
string Player::getFirstName() 
{
	return firstName;
}

// ------------------------
// Get player full name
// ------------------------
string Player::getFullName() 
{
	return firstName + " " + lastName;
}

// ------------------------
// Get player name length
// ------------------------
int Player::getNameLength() 
{
	return nameLength;
}

// ------------------------
// Get player wins
// ------------------------
int Player::getWins()
{
	return wins;
}

// ------------------------
// Get player losses
// ------------------------
int Player::getLosses()
{
	return losses;
}

// ------------------------
// Get player draws
// ------------------------
int Player::getDraws()
{
	return draws;
}

// ------------------------
// Record player win
// ------------------------
void Player::addWin()
{
	wins++;;
}

// ------------------------
// Record player loss
// ------------------------
void Player::addLoss()
{
	losses++;
}

// ------------------------
// Record player draw
// ------------------------
void Player::addDraw()
{
	draws++;
}