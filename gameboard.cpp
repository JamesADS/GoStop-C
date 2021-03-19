#include "gameboard.h"
#include <algorithm>


/* *********************************************************************
Function Name: gameboard
Purpose: constructor for a gameboard object used when no round number is supplied.
Parameters: none.
Return Value: none, this is a constructor.
Local Variables: none, but sets the roundNum member of the gameboard class to 1.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

gameboard::gameboard()
{
	
	roundNum = 1;
}

/* *********************************************************************
Function Name: gameboard
Purpose: constructor for a gameboard object used to also set the round number.
Parameters: int thisRoundNum - denotes the new rounds number.
Return Value: none, this is a constructor.
Local Variables: none, but sets the roundNum member of the gameboard class to the supplied value.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

gameboard::gameboard(int thisRoundNum)
{
	roundNum = thisRoundNum;

}

/* *********************************************************************
Function Name: getLayout
Purpose: returns the gameboards layout member.
Parameters: none.
Return Value: a vector of cards, namely the layout.
Local Variables: none.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

std::vector<std::vector<card>> &gameboard::getLayout()
{
	
	return layout;
}

/* *********************************************************************
Function Name: setLayout
Purpose: sets the gameboards layout member.
Parameters: std::vector<std::vector<card>> setTo - the structure to set the layout to.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

void gameboard::setLayout(std::vector<std::vector<card>>& setTo) 
{
	layout = setTo;
}

/* *********************************************************************
Function Name: getStock
Purpose: returns the gameboards stockpile member.
Parameters: none.
Return Value: a vector of cards, namely the stockpile.
Local Variables: none.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

std::vector<card> &gameboard::getStock()
{
	return stockpile;
}

/* *********************************************************************
Function Name: getRoundNum
Purpose: returns the gameboards roundNum member.
Parameters: none.
Return Value: int - the round number.
Local Variables: none.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

int gameboard::getRoundNum() 
{
	return roundNum;
}

/* *********************************************************************
Function Name: createDeck
Purpose: Creates 104 card objects with proper suits and values and moves them into the deck data structure.
Parameters: none.
Return Value: none.
Local Variables: i and j, integers for nested loop. x a card object created to be pushed onto the vector many times.
Algorithm: nested loop, i is the value of the card from 2 to 14, and for each i value one of four j values determines the suit via a switch.
Assistance Received: None.
********************************************************************* */

void gameboard::createDeck()
{
	/*Create the NUMBER cards iterating through a loop to give value, and switching on local int j to assign suit. Create 2 cards for each because we are using 2 decks.
	Push the cards onto the deck vector as we go.*/

	//REFERENCE: 11 = Jack, 12 = Queen, 13 = King, 14 = Ace

	for (int i = 2; i < 15; i++)
	{
		for (int j = 0; j < 4; j++) {
			switch (j)
			{
				//need to delete card "x" after it is created each time.
			case 0:
			{
				card x(i, "Hearts");
				deck.push_back(x);
				deck.push_back(x);
				break;
			}

			case 1:
			{
				card x(i, "Spades");
				deck.push_back(x);
				deck.push_back(x);
				break;
			}

			case 2:
			{
				card x(i, "Diamonds");
				deck.push_back(x);
				deck.push_back(x);
				break;
			}

			case 3:
			{
				card x(i, "Clubs");
				deck.push_back(x);
				deck.push_back(x);
				break;
			}
			}
		}
	}






	return;
}

/* *********************************************************************
Function Name: shuffleDeck
Purpose: shuffles the deck data member randomly.
Parameters: none.
Return Value: none.
Local Variables: none.
Algorithm: call std::random_shuffle for the range of the deck.
Assistance Received: None.
********************************************************************* */
void gameboard::shuffleDeck() 
{
	std::random_shuffle(deck.begin(), deck.end());
}

/* *********************************************************************
Function Name: drawCard
Purpose: Moves a card object from the designated source pile to the designated destination pile.
Parameters:destPile a vector of cards passed by reference.
			srcPile a vector of cards passed by reference.
Return Value: none.
Local Variables: none.
Algorithm: push the front card of the sourcepile to destination pile, then erase it from the sourcepile.
Assistance Received: None.
********************************************************************* */

void gameboard::drawCard(std::vector<card>& destPile, std::vector<card>& srcPile)
{
	destPile.push_back(srcPile.front());
	srcPile.erase(srcPile.begin());
	return;


}

/* *********************************************************************
Function Name: drawCard (index overload)
Purpose: Moves a card object from the designated source pile to the designated destination pile from a specified index.
Parameters:vector<card> destPile a vector of cards passed by reference.
		vector<card> srcPile a vector of cards passed by reference.
		int index, the index from the sourcepile to move the card from.
Return Value: none.
Local Variables: none.
Algorithm: push the selected card of the sourcepile to destination pile, then erase it from the sourcepile.
Assistance Received: None.
********************************************************************* */

void gameboard::drawCard(std::vector<card>& destPile, std::vector<card>& srcPile, int index)
{
	destPile.push_back(srcPile[index]);
	srcPile.erase(srcPile.begin() + index);
	return;


}




/* *********************************************************************
Function Name: dealCards
Purpose: Deals cards at the beginning of the game to both players, the layout, and then the stockpile.
Parameters:p1Hand and compHand, respective player hands.
Return Value: none.
Local Variables: k and j, integers used in the 5-5-4 deal loop that occurs at the beginning of a round.
Algorithm: deal 5 to player, 5 to computer, 4 to layout two times, then move the remaining deck cards to the stockpile.
Assistance Received: None.
********************************************************************* */
void gameboard::dealCards(std::vector<card> &p1Hand, std::vector<card> &compHand)
{
	int k = 0;

	//Deal in 5,5,4 order two times. Player, Computer, Layout.
	do
	{
		int j = 0;
		do
		{
			drawCard(p1Hand, deck);
			j++;
		} while (j < 5);
		j = 0;
		do
		{
			drawCard(compHand, deck);
			j++;
		} while (j < 5);
		j = 0;
		std::vector<card> firstLayout;
		do
		{
			drawCard(firstLayout, deck);
			layout.push_back(firstLayout);
			firstLayout.clear();
			j++;
		} while (j < 4);



		k++;
	} while (k < 2);

	//Move the remaining cards from the deck to the stockpile.
	do
	{
		drawCard(stockpile, deck);
	} while (!deck.empty());

	return;
}

/* *********************************************************************
Function Name: printCard
Purpose: Print the card (ASCII) located at a given vector index.
Parameters: printFrom, a vector of cards that designates the pile to print the card from.
			index, where in the printFrom pile to print from.
Return Value: none.
Local Variables: j, an integer used in a switch to print the face card value correctly. (11 -> J, 12 -> Q, 13 -> K, 14 -> A)
Algorithm: if the value is below 11, just print the cards stored value, otherwise handle the 4 face card cases with a switch.
Assistance Received: none.
********************************************************************* */

void gameboard::printCard(std::vector<card>& printFrom, int index, int &x, int &y)
{
	//handle 2-10 values.
	if (printFrom.at(index).getValue() < 11) {
		std::cout << " _______\n";
		gotoxy(x, y + 1);
		std::cout << "|" << printFrom.at(index).getValue() << "      |\n";
		gotoxy(x, y + 2);
		std::cout << "|       |\n";
		gotoxy(x, y + 3);
		std::cout << "|   " << printFrom.at(index).getSuit()[0] << "   |\n";
		gotoxy(x, y + 4);
		std::cout << "|       |\n";
		gotoxy(x, y + 5);
		std::cout << "|     " << printFrom.at(index).getValue() << " |\n";
		gotoxy(x, y + 6);
		std::cout << " -------\n";
	}
	//handle face card values.
	else
	{
		int j = printFrom.at(index).getValue();

		std::cout << " _______\n";
		gotoxy(x, y + 1);
		switch (j)
		{
		case 11:
		{
			std::cout << "|" << 'J' << "      |\n";
			gotoxy(x, y + 2);
			break;
		}
		case 12:
		{
			std::cout << "|" << 'Q' << "      |\n";
			gotoxy(x, y + 2);
			break;
		}
		case 13:
		{
			std::cout << "|" << 'K' << "      |\n";
			gotoxy(x, y + 2);
			break;
		}
		case 14:
		{
			std::cout << "|" << 'A' << "      |\n";
			gotoxy(x, y + 2);
			break;
		}

		}

		std::cout << "|       |\n";
		gotoxy(x, y + 3);
		std::cout << "|   " << printFrom.at(index).getSuit()[0] << "   |\n";
		gotoxy(x, y + 4);
		std::cout << "|       |\n";
		gotoxy(x, y + 5);
		
		switch (j)
		{
		case 11:
		{
			std::cout << "|      " << 'J' << "|\n";
			gotoxy(x, y + 6);
			break;
		}
		case 12:
		{
			std::cout << "|      " << 'Q' << "|\n";
			gotoxy(x, y + 6);
			break;
		}
		case 13:
		{
			std::cout << "|      " << 'K' << "|\n";
			gotoxy(x, y + 6);
			break;
		}
		case 14:
		{
			std::cout << "|      " << 'A' << "|\n";
			gotoxy(x, y + 6);
			break;
		}

		}

		std::cout << " -------\n";
		
	}

	return;

}

/* *********************************************************************
Function Name: printPile
Purpose: Uses the printCard function to print an entire designated pile.
Parameters: toPrint, a vector of cards passed by reference that designates the pile to print.
Return Value: none.
Local Variables: i, an integer used to call printCard the correct number of times, which is also passed to printCard to designate the index.
Algorithm: printCard the number of times that is needed (size of the pile), incrementing the index to print each time.
Assistance Received: none.
********************************************************************* */

void gameboard::printPile(std::vector<card>& toPrint, int& x, int& y)
{
	/*Line number references
	0: computer hand and capture pile
	12: layout and stock pile
	24: player hand and capture pile
	30: round number, computer score, human score
	*/



	for (int i = 0; i < toPrint.size(); i++)
	{
		gotoxy(x, y);
		
		
		printCard(toPrint, i, x, y);
		x += 10;

	}

	return;




}

/* *********************************************************************
Function Name: printNums
Purpose: prints the index numbers above the human hand and the layout.
Parameters: int printCount - How many numbers to print
			int x - x position to go to.
			int y - y position to go to.
Return Value: none.
Local Variables: int i - used in for loop until i reaches printcount.
Algorithm: print "   [i]   " printCount number of times.
Assistance Received:
********************************************************************* */

void gameboard::printNums(int printCount, int &x, int &y) 
{
	gotoxy(x, y - 1);
	for (int i = 0; i < printCount; i++) 
	{
		std::cout << "   [" << i << "]    ";
	}
}

/* *********************************************************************
Function Name: printStacks
Purpose: print a vector of vector of cards, with functionality to give the appearance of a stack pair, triplet, or 4 stack.
Parameters: std::vector<std::vector<card>>& toPrint - the stack to print.
			int x - the starting x coordinate
			int y - the starting y coordinate
Return Value: none.
Local Variables: int i - used to move through each pile in the vector
				int j - used to mvee through each card in a pile.
Algorithm: 
			for each pile in the vector, check if that pile has a size greater than 1. If it does, print the cards with special considerations to the coordinates. (+1 to both each time)
			if it doesn't, print just the card normally.
			increment x by 10 after each pile to separate the piles appropriately.
Assistance Received:
********************************************************************* */

void gameboard::printStacks(std::vector<std::vector<card>>& toPrint, int& x, int& y)
{
	//for every pile in the vector
	for (int i = 0; i < toPrint.size(); i++)
	{
		//if it is a double or triple stack, we need to handle printing differently.
		if (toPrint[i].size() > 1)
		{
			//for every card in the stack 
			for (int j = 0; j < toPrint[i].size(); j++)
			{
				//print the card and increment x and y specially.
				gotoxy(x, y);
				printCard(toPrint[i], j, x, y);
				x++;
				y++;
			}
			//we need to reset our y coordinate; 
			y -= toPrint[i].size();
		}
		else if (toPrint[i].size() == 0) 
		{
			
		}
		//if it is not we can call printCard normally.
		else
		{
			gotoxy(x, y);
			printCard(toPrint[i], 0, x, y);

		}
		x += 10;
	}
}





/* *********************************************************************
Function Name: roundStart
Purpose: used by a gameboard object at the start of the round to create the deck which will be used and subsequently deal cards.
Parameters: p1Hand and compHand, vectors passed by reference to be given to the dealCards function.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

void gameboard::roundStart(std::vector<card>& p1Hand, std::vector<card>& compHand)
{
	createDeck();
	dealCards(p1Hand, compHand);


}


/* *********************************************************************
Function Name: checkMatches
Purpose: checks for the number of matches a particular card has with a supplied vector of vector of cards (e.g. layout)
Parameters: card playerCard - the card to check against the pile.
			std::vector<std::vector<<card>> - the pile to be checked against.
Return Value: int - returns the number of matches the card has with a pile.
Local Variables: int matches - holds the running total of matches.
Algorithm: for each pile in the vector of vectors, check if the value of the playercard matches the pile. Increment matches for each card matched, not just each pile.
Assistance Received:
********************************************************************* */
int gameboard::checkMatches(card& playerCard, std::vector<std::vector<card>>& layoutPile)
{
	int matches = 0;
	//iterate through each vector inside the the vector
	for (int j = 0; j < layoutPile.size(); j++)
	{

		//Check each card in the matching layout pile, so we know how many cards we are matching.
		for (int i = 0; i < layoutPile[j].size(); i++)
			if (playerCard.getValue() == (layoutPile[j])[i].getValue())
			{
				matches++;
			}





	}
	return matches;
}

/* *********************************************************************
Function Name: whereMatch
Purpose: returns a vector of pile indices where a supplied card matches.
Parameters: card playerCard - the card to check against the pile.
			std::vector<std::vector<card>> layoutPile - the pile to check against.
Return Value: std::vector<int> - a vector of all the matching indices.
Local Variables: int index - the index to be checked, initialized to 0.
				std::vector<int> indcies - stores the indices that are matching, is eventually returned.
				
Algorithm: for every pile, if the value of the playercard matches the value of the first card in pile[index], add the index to the indices vector.
Assistance Received:
********************************************************************* */

std::vector<int> gameboard::whereMatch(card& playerCard, std::vector<std::vector<card>>& layoutPile)
{
	int index = 0;
	std::vector<int> indices;
	for (index = 0; index < layoutPile.size(); index++)
	{

		//we just need to check the first value in each pile of the layout, since stack pairs or triplets can only be of that value.
		if (playerCard.getValue() == (layoutPile[index])[0].getValue())
		{
			indices.push_back(index);
		}

	}
	return indices;

}


/* *********************************************************************
Function Name: findPair
Purpose: finds the index of a pair in the given vector of vector of cards
Parameters: std::vector<std::vector<card>> searchThrough - the data structure to search through
Return Value: int - -1 if no pair indices. otherwise the index of the pair.
Local Variables: int i - used to iterate through loop.
Algorithm: for each pile in the data structure, if the size is 2, return i (the index). otherwise return -1.
Assistance Received:
********************************************************************* */
int gameboard::findPair(std::vector<std::vector<card>>& searchThrough)
{
	for (int i = 0; i < searchThrough.size(); i++)
	{
		if (searchThrough[i].size() == 2)
		{
			return i;
		}
	}
	return -1;

}

/* *********************************************************************
Function Name: setStock
Purpose: sets the stockpile
Parameters: std::vector<card> setTo - the vector to set the stockpile to.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
void gameboard::setStock(std::vector<card>& setTo)
{
	stockpile = setTo;
}

/* *********************************************************************
Function Name: reduc
Purpose: remove the 'holes' in a vector of vector of cards that can be created during GoStop play.
Parameters: std::vector<std::vector<card>> toReduce - the pile to be reduced in size.
Return Value: none.
Local Variables: int i - used to iterate through the loop.
Algorithm: for every pile, if the size is less than or equal to 0, delete this pile from the data structure. decrement i in this scenario to prevent out of bounds vector subscript.
Assistance Received:
********************************************************************* */
void gameboard::reduc(std::vector<std::vector<card>>& toReduce) 
{
	for (int i = 0; i < toReduce.size(); i++) 
	{
		if (toReduce[i].size() <= 0) {
			toReduce.erase(toReduce.begin() + i);
			i--;
		}
	}
}

/* *********************************************************************
Function Name: setRoundNum
Purpose: sets the gameboard round number data member.
Parameters: int setTo - the number to set to.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received:
********************************************************************* */
void gameboard::setRoundNum(int setTo) 
{
	roundNum = setTo;
}

/* *********************************************************************
Function Name: cleanup
Purpose: erases the gameboard data members in the event that the gameboard needs to be reused.
Parameters: none.
Return Value: none.
Local Variables: none.
Algorithm: if the stockpile or the layout have anything in them, erase their contents.
Assistance Received:
********************************************************************* */
void gameboard::cleanup() 
{
	if (stockpile.size() > 0)
	{
		stockpile.erase(stockpile.begin(), stockpile.end());
	}
	if (layout.size() > 0)
	{
		layout.erase(layout.begin(), layout.end());
	}

}

/* *********************************************************************
Function Name: ~gameboard
Purpose: gameboard destructor
Parameters: none
Return Value: none
Local Variables: none.
Algorithm: erases the stockpile and layout.
Assistance Received:
********************************************************************* */

gameboard::~gameboard() 
{
	if (stockpile.size() > 0) 
	{
		stockpile.erase(stockpile.begin(), stockpile.end());
	}
	if (layout.size() > 0)
	{
		layout.erase(layout.begin(), layout.end());
	}
}