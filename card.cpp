#include "card.h"

/* *********************************************************************
Function Name: Card
Purpose: Default Constructor to handle extraneous calls.
Parameters:

Return Value: A card object.
Local Variables: none.
Algorithm:
Assistance Received: None.
********************************************************************* */

card::card()
{

}

/* *********************************************************************
Function Name: Card
Purpose: Parameterized Constructor to automatically set the suit and value of a created card.
Parameters:
			uvalue, a supplied value to instantiate the card's value.
			usuit, a string referring to the suit of card (hearts, spades, clubs, diamonds).
Return Value: A card object with a suit and value.
Local Variables: none.
Algorithm:
Assistance Received: None.
********************************************************************* */

card::card(int uvalue, std::string usuit)
{
	value = uvalue;
	suit = usuit;
}

/* *********************************************************************
Function Name: card 
Purpose: constructor for when reading in cards from save files.
Parameters: int uvalue - value of card to be created.
			char usuit - character that determines suit of card to be created.
Return Value: card.
Local Variables: none.
Algorithm: set value to uvalue, set usuit depending on the character passed in, suing a switch statement.
Assistance Received:
********************************************************************* */
card::card(int uvalue, char usuit) 
{
	value = uvalue;
	switch (usuit) 
	{
	case 'D':
		suit = "Diamonds";
		break;
	case 'H':
		suit = "Hearts";
		break;
	case 'C':
		suit = "Clubs";
		break;
	case 'S':
		suit = "Spades";
		break;
	}
}

/* *********************************************************************
Function Name: getSuit
Purpose: returns the cards suit.
Parameters: none
Return Value: std string - returns the suit data member.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
std::string card::getSuit()
{
	return suit;
}

/* *********************************************************************
Function Name: getValue
Purpose: returns the cards value.
Parameters: none
Return Value: int - returns the value data member.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
int card::getValue()
{
	return value;

}