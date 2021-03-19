#include "player.h"
//#include "gameboard.h"

/* *********************************************************************
Function Name: player
Purpose: player constructor
Parameters: none
Return Value: none.
Local Variables: none.
Algorithm: initializes a player object with data member score = 0.
Assistance Received:
********************************************************************* */
player::player()
{
	score = 0;
}

/* *********************************************************************
Function Name: getHand
Purpose: returns the player hand.
Parameters: none.
Return Value: std::vector<card> - the player hand.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
std::vector<card>player::getHand()
{
	return hand;
}

/* *********************************************************************
Function Name: getCapPile
Purpose: returns the player Capture Pile.
Parameters: none.
Return Value: std::vector<std::vector<<card>> - the player capPile.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
std::vector<std::vector<card>>player::getCapPile()
{
	return capPile;
}

/* *********************************************************************
Function Name: getScore
Purpose: returns the player score.
Parameters: none.
Return Value: int - the player score.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
int player::getScore()
{
	return score;
}

/* *********************************************************************
Function Name: matchesCapPilePair
Purpose: checks if the supplied card matches a pair in the players capture pile.
Parameters: card toMatch - the card to match against the capture pile.
			player matcher - used to get the capPile.
Return Value: int - returns the matching index if there one, otherwise returns -1.
Local Variables: std::vector<std::vector<card>> CP - temporarily holds the capture pile.
				int i - used to iterate through loop.
Algorithm: for each pile in the capture pile data structure, if it is a pair and the values match the value of the card supplied, return the index of this pile. if none, return -1. 
Assistance Received:
********************************************************************* */
int player::matchesCapPilePair(card toMatch, player &matcher)
{
	std::vector<std::vector<card>> CP = matcher.getCapPile();

	//for each vector in the capture pile
	for (int i = 0; i < CP.size(); i++)
	{
		//if the index is a pair (has a size of 2).
		if (CP[i].size() == 2)
		{
			//if a card in the pile matches the passed card, they are the same.
			if (CP[i].front().getValue() == toMatch.getValue())
			{
				//return the matching index
				return i;
			}
		}

	}
	return -1;
}

/* *********************************************************************
Function Name: setScore
Purpose: sets the player score.
Parameters: int setTo- sets the player score to this + current player score.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
void player::setScore(int setTo) 
{
	score += setTo;
}

