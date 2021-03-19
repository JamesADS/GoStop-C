#include "human.h"
/* *********************************************************************
Function Name: getHand
Purpose: returns the player hand.
Parameters: none.
Return Value: std::vector<card> - the player hand.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
std::vector<card> &human::getHand()
{
	return hand;
}

/* *********************************************************************
Function Name: getCapPile
Purpose: returns the capture pile.
Parameters: none.
Return Value: std::vector<std::vector<card>> - the capture pile.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
std::vector<std::vector<card>>&human::getCapPile()
{
	return capPile;
}

/* *********************************************************************
Function Name: getScore
Purpose: returns the score.
Parameters: none.
Return Value: int - the player score.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
int human::getScore()
{
	return score;
}

/* *********************************************************************
Function Name: setHand
Purpose: sets the player hand to a supplied vector of cards.
Parameters: std::vector<card> & setTo - the vector to set the hand to.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
void human::setHand(std::vector<card> & setTo) 
{
	hand = setTo;
}

/* *********************************************************************
Function Name: setCapPile
Purpose: sets the player Capture Pile to a supplied vector of vector of cards.
Parameters: std::vector<std::vector<card>> & setTo - the vector of vector of cards to set the capture pile to.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
void human::setCapPile(std::vector<std::vector<card>>& setTo) 
{
	capPile = setTo;
}

/* *********************************************************************
Function Name: reduceCP
Purpose: consolidates pairs in the capture pile.
Parameters: none.
Return Value: none.
Local Variables: int i - iterates through each pile in the capture pile
				 int j - looks ahead in the capture pile and iterates through.
				 int k - iterates through a pile if two piles match and need to be consilidated.
Algorithm: for each pile, look ahead in the vector at other piles. if any other pile has the same card values, and both piles currently being checked are size of 2 or less, combine them.
Assistance Received:
********************************************************************* */
void human::reduceCP() 
{
	for (int i = 0; i < capPile.size(); i++) 
	{
		for (int j = 1; j < 4; j++) 
		{
			if ((i+j) < capPile.size()) 
			{


				if (capPile[i][0].getValue() == capPile[i + j][0].getValue() && capPile[i].size() <= 2 && capPile[i+j].size() <= 2)
				{
					for (int k = 0; k < capPile[i + j].size(); k++) 
					{
						capPile[i].push_back(capPile[i + j][0]);
					}
					capPile.erase(capPile.begin() + i + j);
					i--;
				}
			}
		}
	}
}

/* *********************************************************************
Function Name: matchesCapPilePair
Purpose: determines if a supplied pile (which will be presumably added to the capture pile) matches any current pairs in the capture pile, so that they may make a 4 stack.
Parameters: std::vector<card> newPile - the pile which will be presumably added.
			std::vector<std::vector<card>> CP - the vector of vectors to check each pile against.
Return Value: none.
Local Variables: int i - iterates through each pile in the capture pile
				 int k - iterates through the pile to be added to the existing capture pile pair if need be.

Algorithm: for each pile in the capture pile, if it has a size of 2, check if the front card value is the same as the value of the new pile. if they are the same, push each card from the new pile
			into this capture pile pile.
			if there are no matching pairs, just push the new pile onto the end of the capture pile.
Assistance Received:
********************************************************************* */
void human::matchesCapPilePair(std::vector<card> &newPile, std::vector<std::vector<card>> &CP)
{


	//for each vector in the capture pile
	for (int i = 0; i < CP.size(); i++)
	{
		//if the index is a pair (has a size of 2).
		if (CP[i].size() == 2)
		{
			//if a card in the pile matches the passed card, they are the same.
			if (CP[i].front().getValue() == newPile[0].getValue())
			{

				for (int k = 0; k < newPile.size(); k++)
				{
					//move each card from the newPair to the matching capPile index.
					CP[i].push_back(newPile[k]);
				}
				return;
			}
		}

	}
	CP.push_back(newPile);
}

/* *********************************************************************
Function Name: setScore
Purpose: sets the score data member to the supplied int value.
Parameters: int setTo - the value to set the score to.
Return Value: none.
Local Variables: none.
Algorithm:
Assistance Received:
********************************************************************* */
void human::setScore(int setTo)
{
	score = setTo;
}

/* *********************************************************************
Function Name: setScoreAdd
Purpose: adds to the score data member the supplied int value.
Parameters: int setTo - the value to add to the score.
Return Value: none.
Local Variables: none.
Algorithm:
Assistance Received:
********************************************************************* */
void human::setScoreAdd(int setTo)
{
	score += setTo;
}

/* *********************************************************************
Function Name: cleanup
Purpose: clears out the data structures for the human so the object may be reused.
Parameters: none.
Return Value: none.
Local Variables: none.
Algorithm: erase the entries in the hand and capture pile.
Assistance Received:
********************************************************************* */
void human::cleanup() 
{
	if (hand.size() > 0)
	{
		hand.erase(hand.begin(), hand.end());
	}
	capPile.erase(capPile.begin(), capPile.end());
}

/* *********************************************************************
Function Name: mostMatches
Purpose: returns the hand index of the card that matches the most layout cards.
Parameters: std::vector<std::vector<card>> LAY - the layout to match with.
			gameboard GB - used to access the checkMatches function, to update the most matching index if need be.
Return Value: int - the most matching hand index.
Local Variables: int mostMatchingIndex - the value to be returned.
				int matches - temporary holder to determine number of matches in this iteration.
Algorithm:		
Assistance Received:
********************************************************************* */
int human::mostMatches(std::vector<std::vector<card>>& LAY, gameboard& GB)
{
	int mostMatchingIndex = 0;
	int matches = 0;
	//for every card in the hand
	for (int i = 0; i < hand.size(); i++)
	{

		if (GB.checkMatches(hand[i], LAY) > matches)
		{
			mostMatchingIndex = i;
		}

	}
	return mostMatchingIndex;
}

/* *********************************************************************
Function Name: canMakeQuartet
Purpose: determines if the human player can complete an existing capture pile pair based on their hand and the layout. (for use in the help function)
Parameters: std::vector<std::vector<card>> LAY - the layout. 
			gameboard GB - used to access gameboard member functions
Return Value: int - returns the index of the hand card that can be played to complete a quartet. returns -1 if no such card exists.
Local Variables: std::vector<int> index - holds indices of matching cards.
Algorithm:  for each hand card, if the value matches a PAIR in the capture pile, check if the hand cards matches any layout cards. If it does, this means a stack pair can be created on the layout,
			which will then make its way to the Capture Pile, forming a quartet and earning a point.
Assistance Received:
********************************************************************* */
int human::canMakeQuartet(std::vector<std::vector<card>>& LAY, gameboard& GB)
{
	GB.reduc(capPile);
	std::vector<int> index;
	//for every card in the hand
	for (int i = 0; i < hand.size(); i++)
	{
		//check every pile in the capture pile.
		for (int j = 0; j < capPile.size(); j++)
		{
			//if the value of the card in your hand matches the value of a capture pile and the capture pile is only a pair.
			if (hand[i].getValue() == capPile[j][0].getValue() && capPile[j].size() == 2)
			{
				index = GB.whereMatch(hand[i], LAY);
				//if there is a match somewhere on the board, this means the computer can make the match and add it to the capPile pair, earning a point.
				if (index.size() > 0)
				{
					//return the index of the hand of the card to play.
					return i;
				}
			}
		}
	}
	return -1;
}