#include "Client.h"



/* *********************************************************************
Function Name: Client
Purpose: constructor for client object.
Parameters: none.
Return Value: client object.
Local Variables: none, but sets roundNum data member to 1.
Algorithm:
Assistance Received:
********************************************************************* */

Client::Client()
{
	choice = 0;
	roundNum = 1;
}

/* *********************************************************************
Function Name: tryComp
Purpose: Checks for the computer information in a saved game file using RegEx and sets the CPU data structures if there is a match.

Parameters: 
smatch m - holds the captured groups after regex searching.
regex RX - used to identify the lines.
string line - holds the string to parse using regex, and then holds the desired captured group in some scenarios.
comp CPU - used to access and set the CPU data structures hand and capture pile
Return Value: bool, lets the loadGame function know if this function should be called again or not.

Local Variables: 
std::vector<card> tempVec - holds newly created cards until they are ready to be moved to the CPU data structures.

Algorithm: try to match lines in the order of the document, if a line is matched, use it for the data it gives and return true so this function will be called again with a new line to parse.
Assistance Received:
********************************************************************* */

bool Client::tryComp(std::smatch m, std::regex RX, std::string line, comp& CPU) 
{
	RX.assign(("(.*)(Computer:)(.*)"));
	//std::getline(readFrom, line);
	//Enter Computer portion
	if (regex_match(line, RX))
	{
		return true;
	}
	RX.assign("(.*)(Score:)(.*)");
	//std::getline(readFrom, line);

	//find score portion
	if (regex_match(line, RX))
	{
		RX.assign("(.*)(Score: )(\\d+)");

		regex_search(line, m, RX);
		CPU.setScore(std::stoi(m.str(3)));
		return true;
	}


	RX.assign("(.*)(Hand:)(.*)");
	//std::getline(readFrom, line);
	//find Hand portion
	if (regex_match(line, RX))
	{

		RX.assign("(.*)(Hand: )((?:[JKQX1-9][CDHS]\\s)+)+");
		regex_search(line, m, RX);


		line = m.str(3);
		std::vector<card> tempVec;

		for (int i = 0; i < (line.length()); i += 3)
		{


			int tempValue = revConvert(line[i]);
			card tempCard(tempValue, line[i + 1]);
			tempVec.push_back(tempCard);

		}
		CPU.setHand(tempVec);
		return true;
	}

	RX.assign("(.*)(Capture Pile:\\s)((?:[JKQX1-9][CDHS][\\s\-])+)+");
	//std::getline(readFrom, line);
	//find Cap Pile portion
	if (regex_match(line, RX))
	{
		regex_search(line, m, RX);
		line = m.str(3);
		int tempValue = 0;
		std::vector<card> tempVec;
		std::vector<std::vector<card>> tempCP;
		for (int i = 0; i < line.size(); i++)
		{
				tempValue = revConvert(line[i]);
				if (tempValue >= 1 && tempValue <= 14)
				{
					card tempCard(tempValue, line[i + 1]);
					tempVec.push_back(tempCard);

				}
				if (line[i] == ' ')
				{
					tempCP.push_back(tempVec);
					tempVec.clear();
				}

		}
		CPU.setCapPile(tempCP);

		return true;
}

			
		
	return false;
}

/* *********************************************************************
Function Name: tryHuman
Purpose: Checks for the human information in a saved game file using RegEx and sets the human data structures if there is a match.

Parameters:
smatch m - holds the captured groups after regex searching.
regex RX - used to identify the lines.
string line - holds the string to parse using regex, and then holds the desired captured group in some scenarios.
human P1 - used to access and set the human data structures hand and capture pile
Return Value: bool, lets the loadGame function know if this function should be called again or not.

Local Variables:
std::vector<card> tempVec - holds newly created cards until they are ready to be moved to the human data structures.
int tempValue - used to hold the value of the card to be created in each iteration of reading the line.
card tempCard - card to be pushed into the tempVec or tempCP in each iteration.
std::vector<std::vector<card>> tempCP - used to create the desired Capture Pile structure to then set accordingly.

Algorithm: try to match lines in the order of the document, if a line is matched, use it for the data it gives and return true so this function will be called again with a new line to parse.
Assistance Received:
********************************************************************* */

bool Client::tryHuman(std::smatch m, std::regex RX, std::string line, human & P1) 
{
	RX.assign(("(.*)(Human:)(.*)"));
	//std::getline(readFrom, line);
	//Enter Computer portion
	if (regex_match(line, RX))
	{
		return true;
	}
	RX.assign("(.*)(Score:)(.*)");
	//std::getline(readFrom, line);

	//find score portion
	if (regex_match(line, RX))
	{
		RX.assign("(.*)(Score: )(\\d+)");

		regex_search(line, m, RX);
		P1.setScore(std::stoi(m.str(3)));
		return true;
	}


	RX.assign("(.*)(Hand:)(.*)");
	//std::getline(readFrom, line);
	//find Hand portion
	if (regex_match(line, RX))
	{

		RX.assign("(.*)(Hand: )((?:[JKQX1-9][CDHS]\\s)+)+");
		regex_search(line, m, RX);


		line = m.str(3);
		std::vector<card> tempVec;

		for (int i = 0; i < (line.length()); i += 3)
		{


			int tempValue = revConvert(line[i]);
			card tempCard(tempValue, line[i + 1]);
			tempVec.push_back(tempCard);

		}
		P1.setHand(tempVec);
		return true;
	}

	RX.assign("(.*)(Capture Pile: )((?:[JKQX1-9][CDHS][\\s\-])+)+");
	//std::getline(readFrom, line);
	//find Cap Pile portion
	if (regex_match(line, RX))
	{
		regex_search(line, m, RX);
		line = m.str(3);
		int tempValue = 0;
		std::vector<card> tempVec;
		std::vector<std::vector<card>> tempCP;
		for (int i = 0; i < line.size(); i++)
		{
			tempValue = revConvert(line[i]);
			if (tempValue >= 1 && tempValue <= 14)
			{
				card tempCard(tempValue, line[i + 1]);
				tempVec.push_back(tempCard);

			}
			if (line[i] == ' ')
			{
				tempCP.push_back(tempVec);
				tempVec.clear();
			}

		}
		P1.setCapPile(tempCP);

		return true;
	}



	return false;
}

/* *********************************************************************
Function Name: tryLayout
Purpose: Checks for the layout information in a saved game file using RegEx and sets the gameboard layout structure if there is a match.

Parameters:
smatch m - holds the captured groups after regex searching.
regex RX - used to identify the lines.
string line - holds the string to parse using regex, and then holds the desired captured group in some scenarios.
gameboard GB - used to access and set the gameboard data structures hand and capture pile
Return Value: bool, lets the loadGame function know if this function should be called again or not.

Local Variables:
std::vector<card> tempVec - holds newly created cards until they are ready to be moved to the tempCP.
int tempValue - used to hold the value of the card to be created in each iteration of reading the line.
card tempCard - card to be pushed into the tempVec in each iteration.
std::vector<std::vector<card>> tempCP - used to create the desired layout structure to then set accordingly.


Algorithm: try to match lines in the order of the document, if a line is matched, use it for the data it gives and return true so this function will be called again with a new line to parse.
Assistance Received:
********************************************************************* */

bool Client::tryLayout(std::smatch m, std::regex RX, std::string line, gameboard& GB) 
{
	RX.assign(("(.*)(Layout: )((?:[JKQX1-9][CDHS][\\s\-])+)+"));
	if (regex_match(line, RX))
	{
		regex_search(line, m, RX);
		line = m.str(3);
		int tempValue = 0;
		std::vector<card> tempVec;
		std::vector<std::vector<card>> tempCP;
		for (int i = 0; i < line.size(); i++)
		{
			tempValue = revConvert(line[i]);
			if (tempValue >= 1 && tempValue <= 14)
			{
				card tempCard(tempValue, line[i + 1]);
				tempVec.push_back(tempCard);

			}
			if (line[i] == ' ')
			{
				tempCP.push_back(tempVec);
				tempVec.clear();
			}

		}
		GB.setLayout(tempCP);

		return true;
	}



	return false;
}

/* *********************************************************************
Function Name: tryStock
Purpose: Checks for the layout information in a saved game file using RegEx and sets the gameboard stockpile structure if there is a match.

Parameters:
smatch m - holds the captured groups after regex searching.
regex RX - used to identify the lines.
string line - holds the string to parse using regex, and then holds the desired captured group in some scenarios.
gameboard GB - used to access and set the gameboard stockpile structure
Return Value: bool, lets the loadGame function know if this function should be called again or not.

Local Variables:
std::vector<card> tempVec - holds newly created cards until they are ready to be moved to the stockpile structure.
int tempValue - used to hold the value of the card to be created in each iteration of reading the line.
card tempCard - card to be pushed into the tempVec in each iteration.


Algorithm: try to match lines in the order of the document, if a line is matched, use it for the data it gives and return true so this function will be called again with a new line to parse.
Assistance Received:
********************************************************************* */
bool Client::tryStock(std::smatch m, std::regex RX, std::string line, gameboard& GB) 
{
	RX.assign(("(Stock Pile: )(([JKQX1-9][CDHS][\\s])+)+"));
	if (regex_match(line, RX))
	{
		
		regex_search(line, m, RX);
		line = m.str(2);
		int tempValue = 0;
		std::vector<card> tempVec;
		
		for (int i = 0; i < line.size(); i++)
		{
			tempValue = revConvert(line[i]);
			if (tempValue >= 1 && tempValue <= 14)
			{
				card tempCard(tempValue, line[i + 1]);
				tempVec.push_back(tempCard);

			}
			

		}
		GB.setStock(tempVec);

		return true;
	}



	return false;
}

/* *********************************************************************
Function Name: loadGame
Purpose: loads a saved game from a supplied text file name.
Parameters: comp CPU - the computer player to be passed to the various "try____" functions that require it.
			human P1 - the human player to be passed to the various "try____" functions that require it.
			gameboard GB - the gameboard to be passed to the various "try____" functions that require it, and to set the score.

Return Value: 
			int - returns an integer to determine the starting player based on the file, 1 for Computer, 2 for Human. Defaults to 1 if no data is read.

Local Variables: 
				char choice - used to read in the player choice to load a game or not. (with validation)
				std::string fileName - holds the filename to be input by the player. (with validation)
				std::regex enforceFileName - used to enforce and validate the .txt extension of a read file.
				std::string line - takes in lines from the ifstream object.
				std::regex RX - compared to line variable in order to access 'try' functions
				std::ifstream readFrom - ifstream to read in lines of the file named by the player
				std::smatch m - passed to 'try' functions in order to store matching groups of regex matches.
				int rdNum - receives the round number from the file.

Algorithm: 
			after asking for a filename, the Regex is set to attempt to read in the file with an expected format. The lines of the file are read one by one and passed to each 'try' function. Each try function
			is looking to match and distribute data for the section that the name implies. The functions return a true boolean whenever they strike a match, and return to this loadgame function in order to increment
			the line being read. That line is passed to the same try function to be matched and parsed. Each function runs until it returns false, and the next try function steps into line.
Assistance Received: regex cheat sheet used as a reference to assign regular expressions.  https://www.rexegg.com/regex-quickstart.html 
********************************************************************* */
int Client::loadGame(comp& CPU, human& P1, gameboard& GB)
{
	std::cout << "Welcome to GoStop! Would you like to load a game? Y/N";
	char choice;
	std::cin >> choice;

	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
	{
		std::cout << "Invalid choice. Try again.";
		std::cin >> choice;
	}

	if (choice == 'n' || choice == 'N')
	{
		return 0;
	}

	std::cout << "Enter name of .txt file with game save: ";
	std::string fileName;
	std::cin >> fileName;
	std::regex enforceFileName("(.*)(\.txt)");

	while (!regex_match(fileName, enforceFileName))
	{
		std::cout << "invalid extension type, try again.";
		std::cin >> fileName;
	}
	std::string line;
	std::regex RX("(Round: )(\\d+)");

	std::ifstream readFrom(fileName, std::ifstream::in);
	std::getline(readFrom, line);
	std::smatch m;
	regex_search(line, m, RX);
	int rdNum = std::stoi(m.str(2));
	roundNum = rdNum;
	GB.setRoundNum(rdNum);
	
	//std::ifstream readFrom(fileName, std::ifstream::in);
	while (readFrom.good())
	{
		std::getline(readFrom, line);
		while (tryComp(m, RX, line, CPU)) 
		{
			std::getline(readFrom, line);
			tryComp(m, RX, line, CPU);
		}
		
		while (tryHuman(m, RX, line, P1))
		{
			std::getline(readFrom, line);
			tryHuman(m, RX, line, P1);
		}

		if (tryLayout(m, RX, line, GB))
		{
			std::getline(readFrom, line);
		}

		if (tryStock(m, RX, line, GB)) 
		{
			std::getline(readFrom, line);
		}

		RX.assign("(.*)(Next Player: )(Human|Computer)");
		if (regex_match(line, RX)) 
		{
			regex_search(line, m, RX);
			if (m.str(3) == "Human")
			{
				return 2;
			}
			else if (m.str(3) == "Computer") 
			{
				return 1;
			}
		}
			
	}
	
	






	return 1;
}

/* *********************************************************************
Function Name: getChoice
Purpose: returns the choice data member of the client class.
Parameters: none.
Return Value: int choice, which denotes the players choice for a turn.
Local Variables: none.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

int Client::getChoice()
{
	return choice;
}

/* *********************************************************************
Function Name: setRoundNum
Purpose: Sets the gameclient round number to the supplied value.
Parameters: int setTo - value to set the roundnum to.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received: 
********************************************************************* */

void Client::setRoundNum(int setTo) 
{
	roundNum = setTo;
}

/* *********************************************************************
Function Name: roundStart
Purpose: starts a new round of GoStop.
Parameters: int roundNum - the round number which is passed to the gameboard constructor.
			human P1 - human player, used to retrieve hand.
			comp CPU - computer player, used to retrieve hand.
Return Value: gameboard GB, returns the newly created gameboard object which will be used for this round.
Local Variables: none.
Algorithm: create a gameboard and initialize the round number to this rounds number (supplied to the function), have the gameboard then create a deck and deal cards
			to both players.
Assistance Received: none.
********************************************************************* */

void Client::roundStart(gameboard &GB, human &P1, comp &CPU)
{
	 
	GB.createDeck();
	GB.shuffleDeck();
	GB.dealCards(P1.getHand(), CPU.getHand());

	

}

/* *********************************************************************
Function Name: whoIsFirst
Purpose: Determines who goes first based on hand priority via GoStop rules.
Parameters: 
			std::vector<card> P1Hand - used to access human cards to compare to CPU cards.
			std::vector<card> CPUHand - used to acess CPU cards to compare to human cards.
			int cardValue - the value of the cards to be compared.
Return Value: 
			int returns -1 for modulo suit, 0 for computer first, 1 for human first
Local Variables:
				int playercount - keeps track of how many cards of cardValue that P1 has.
				int CPU count - keeps track of how many cards of cardValue that CPU has.
Algorithm:
			return -1 for modulo suit if this function is called with cardvalue less than 2 passed.
			increment playercount and cpucount for each card of cardvalue they contain in their hand.
			compare cpucount and playercount. Return 0 for cpucount is larger or 1 if playercount is larger.
			if they are equal, call whoIsFirst recursively with cardValue - 1 as the third parameter.
			The next card we check will always be one value lower than the current card, so this function will call itself to completion.
Assistance Received: 
********************************************************************* */

int Client::whoIsFirst(std::vector<card> P1Hand, std::vector<card> CPUHand, int cardValue)
{


	if (cardValue <= 1) 
	{
		return -1;
	}


	int playerCount = 0;
	int CPUCount = 0;

	

	for (int i = 0; i < P1Hand.size(); i++) 
	{
		if (P1Hand[i].getValue() == cardValue) 
		{
			playerCount++;
		}
		if (CPUHand[i].getValue() == cardValue) 
		{
			CPUCount++;
		}
	}

	if (CPUCount > playerCount) 
	{
		return 0;
	}
	else if (playerCount > CPUCount) 
	{
		return 1;
	}
	else if (playerCount == CPUCount) 
	{
		return whoIsFirst(P1Hand, CPUHand, cardValue - 1);
	}


}

/* *********************************************************************
Function Name: playerTurn
Purpose: offers the player a turn and handles each case by calling other functions. 
Parameters: 
			gameboard GB - passed to the various functions called by playerTurn. 
			human P1 - passed to the various functions called by playerTurn. 
			comp CPU - passed to the various functions called by playerTurn. 
Return Value: none.
Local Variables: int hVal - used to determine the H-case (H0-H3) after the first move has been played.
Algorithm: facilitate the player choice at the beginning of the turn and call the appropriate functions based on the input
Assistance Received: 
********************************************************************* */

void Client::playerTurn(gameboard& GB, human& P1, comp& CPU) 
{
	offerTurn(GB, P1, CPU, 0);

	switch (getChoice())
	{
	case 1:
	{
		saveGame(GB, P1, CPU, "Human");
		playerTurn(GB, P1, CPU);
		break;
	}
	case 2:
	{
		int hVal = firstMove(GB, P1);
		setScr(GB, P1, CPU, 0);
		secondMove(GB, P1, hVal);
		setScr(GB, P1, CPU, 0);
		break;
	}
	case 3:
	{
		giveHelp(GB, P1);
		playerTurn(GB, P1, CPU);
		break;
	}
	case 4:
	{
		quit();
		break;
	}
	}

}


/* *********************************************************************
Function Name: CPUTurn
Purpose: offers the CPU a turn and handles each case by calling other functions.
Parameters:
			gameboard GB - passed to the various functions called by playerTurn.
			human P1 - passed to the various functions called by playerTurn.
			comp CPU - passed to the various functions called by playerTurn.
Return Value: none.
Local Variables: int hVal - used to determine the H-case (H0-H3) after the first move has been played.
Algorithm: facilitate the computer choice at the beginning of the turn and call the appropriate functions based on the input.
Assistance Received:
********************************************************************* */
void Client::CPUTurn(gameboard& GB, human& P1, comp& CPU) 
{
	offerTurn(GB, P1, CPU, 1);
	switch (getChoice())
	{
	case 1:
	{
		saveGame(GB, P1, CPU, "Computer");
		CPUTurn(GB, P1, CPU);
		break;
	}
	case 2:
	{
		int hVal = firstMove(GB, CPU);
		setScr(GB, P1, CPU, 1);
		secondMove(GB, CPU, hVal);
		setScr(GB, P1, CPU, 1);
		break;
	}
	case 3:
	{
		giveHelp(GB, P1);
		CPUTurn(GB, P1, CPU);
		break;
	}
	case 4:
	{
		quit();
		break;
	}
	}

}

/* *********************************************************************
Function Name: getRoundNum
Purpose: returns the roundNum data member.
Parameters: none.
Return Value: int roundNum.
Local Variables: none.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

int Client::getRoundNum()
{
	return roundNum;
}

/* *********************************************************************
Function Name: offerTurn
Purpose: offers a turn to the human player and prints the board state.
Parameters: gameboard GB, the gameboard being used.
			human P1, the human player.
			comp CPU, the computer player.
Return Value: int Choice, returns the players choice made in the function.
Local Variables: pile2Print a vector of cards created to continually get board piles to print.
Algorithm: get the various piles to print, and continually change the coordinates to be correct as we print - the order of printing is left to right, top to bottom.
			(CPU Hand - > CPU CapPile -> Layout -> Stockpile -> Human Hand -> Human CapPile)
			print the game status (scores and roundnumber).
			offer the player the choice for the turn, with input validation.
Assistance Received: none.
********************************************************************* */

int Client::offerTurn(gameboard &GB, human &P1, comp &CPU, int turn)
{
	

	setScr(GB, P1, CPU, turn);


	std::cin >> choice;
	while (choice < 1 || choice > 4) 
	{
		std::cerr << "Invalid selection. Make a choice between 1 and 4.";
		std::cin >> choice;
	}
	

	return choice;



}

/* *********************************************************************
Function Name: setScr
Purpose: sets the screen to reflect the current game state.
Parameters:
			gameboard GB - used to get the gameboard data members to print.
			human P1 - used to get the human data members to print.
			comp CPU - used to get the computer data members to print.
			int turn - value used to determine who is next up.
Return Value: none.
Local Variables: 
				int x, int y - used to keep track of the coordinates as printing is occur.
				std::vector<card> pile2Print - used to temporarily hold the data structure to print, used for both player hands and the stockpile.
				std::vector<std::vector<card>> stack2Print - used to temporarily hold the data structure to print - used for the layout and capture piles.
				int printCount - number of cards to print values for.
				std::string who - holds the string of the player whose turn it is.
Algorithm: 
			use global function gotoxy to move the cursor around the screen to the starting locations of the various card piles, call the appropriate print functions at those times.
			(see line reference numbers below)
Assistance Received:
********************************************************************* */
void Client::setScr(gameboard& GB, human& P1, comp& CPU, int turn) 
{
	/*Line number references (y coordinate)
	 0: computer hand and capture pile
	 12: layout and stock pile
	 24: player hand and capture pile
	 30: round number, computer score, human score
	 //turn: 0 = human, 1 = CPU
	 */

	system("cls");

	int x = 0;
	int y = 0;
	

	std::vector<card> pile2Print = CPU.getHand();
	
	GB.printPile(pile2Print, x, y);

	x += 20;
	std::vector<std::vector<card>> stack2Print = CPU.getCapPile();
	GB.printStacks(stack2Print, x, y);


	x = 0;
	y = 12;
	
	stack2Print = GB.getLayout();
	int printCount = stack2Print.size();
	GB.printNums(printCount, x, y);

	
	GB.printStacks(stack2Print, x, y);

	pile2Print = GB.getStock();
	x += 20;
	gotoxy(x, y - 1);
	std::cout << "   SP  ";
	gotoxy(x, y);
	GB.printCard(pile2Print, 0, x, y);

	x = 0;
	y = 24;
	pile2Print = P1.getHand();
	printCount = pile2Print.size();
	GB.printNums(printCount, x, y);
	GB.printPile(pile2Print, x, y);

	x += 20;
	stack2Print = P1.getCapPile();
	GB.printStacks(stack2Print, x, y);

	std::string who;
	if (turn == 0) 
	{
		who = "Human";
	}
	else if(turn == 1)
	{
		who = "Computer";
	}
	else
	{
		who = " ";
	}

	std::cout << "\nRound:" << roundNum << "  P1 Score: " << P1.getScore() << "      CPU Score: " << CPU.getScore() << "   Next Up: " << who << "\n";
	std::cout << "What would you like to do? 1) Save the game. 2) Make a move. 3) Help. 4) Quit.";

}

/* *********************************************************************
Function Name: quit
Purpose: Quits the program.
Parameters: none.
Return Value: none.
Local Variables: none.
Algorithm: none.
Assistance Received: none.
********************************************************************* */

void Client::quit()
{
	exit(0);
}

/* *********************************************************************
Function Name: firstMove
Purpose: Handles the first move of the human player, from getting and validating index selection, to placing the hand card into the layout.
Parameters: 
			gameboard GB - used to access gameboard data structures, like the Layout.
			human P1 - used to access human data structures, like the hand and capture pile.

Return Value: int - returns the H case value (0,1,2,3 for H0,H1,H2,H3 respectively.)

Local Variables: 
				std::vector<card> P1Hand - holds the human player Hand for the duration of the function.
				std::vector<std::vector<card>> CP - holds the human Capture Pile for the duration of the function.
				std::vector<std::vector<card>> LAY - holds the layout for the duration of the function.
				int index - holds the selected index of the human hand card to play (with validation)
				card playerCard - holds the selected card from the hand index with which to check against the layout to determine the number of matches.
				int numMatches - holds the number of layout cards that the selected human card matches.
				std::vector<card> newPile - temporarily holds the vector of cards to be pushed onto the layout.
				std::vector<int> layoutIndex - determines the matching layout indices of the selected human card.
				int selectedIndex - the index selected by the player to decide where to place a card with multiple matches.
				std::vector<card> newQuartet - temporarily holds the 3 matching stockpile cards and 1 human hand card to then be moved to the human Capture Pile.

Algorithm: Get the card to play from the hand by index, with validation. Check how many cards in the layout this hand card matches. The number of matches determines the H case, and GoStop rules
			are implemented for each case using a switch statement. The respective H case value is returned in each scenario.
Assistance Received: 
********************************************************************* */
int Client::firstMove(gameboard& GB, human& P1)
{
	std::vector<card> P1Hand = P1.getHand();
	std::vector<std::vector<card>> CP = P1.getCapPile();
	std::vector<std::vector<card>> LAY = GB.getLayout();




	gotoxy(25, 31);
	std::cout << "Select card to play by index: ";

	//get index of player card to play, with validation
	int index = -1;
	std::cin >> index;
	while (index < 0 || index >= P1Hand.size()) {
		std::cerr << "Invalid index selection.";
		std::cin >> index;
	}
	

	card playerCard = P1Hand[index];

	//clear the writing space
	gotoxy(25, 31);
	std::cout << "                                                                              ";
	gotoxy(25, 31);



	//Decide if the card is being added to the layout as a new card or not.
	int numMatches = GB.checkMatches(playerCard, LAY);
	switch (numMatches)
	{
		//the selected card matches no cards in the layout
	case 0:
	{
		std::cout << "No matches, adding this card to the layout.";
		//create a new pile in the layout and move the playerCard to this new pile.
		std::vector<card> newPile;
		GB.drawCard(newPile, P1Hand, index);
		LAY.push_back(newPile);
		GB.setLayout(LAY);
		P1.setHand(P1Hand);
		return 0;
	}
	//the selected card matches one pile in the layout
	case 1:
	{
		std::cout << "1 match, creating stack pair";
		std::vector<int> layoutIndex = GB.whereMatch(playerCard, LAY);
		GB.drawCard(LAY[layoutIndex[0]], P1Hand, index);
		GB.setLayout(LAY);
		P1.setHand(P1Hand);
		return 1;
	}
	//the selected card matches two cards in the loadout
	case 2:
	{
		std::vector<int> layoutIndices = GB.whereMatch(playerCard, LAY);
		std::cout << "Matches at indices: " << layoutIndices[0] << " and " << layoutIndices[1] << ". Where would you like to place?";
		int selectedIndex = -1;
		std::cin >> selectedIndex;

		//validate the input, ensuring that the selected index matches at least one of the given options.
		while (selectedIndex != layoutIndices[0] && selectedIndex != layoutIndices[1])
		{
			std::cerr << "Invalid index selection. Type only allowed indices. ";
			std::cin >> selectedIndex;
		} 

		GB.drawCard(LAY[selectedIndex], P1Hand, index);
		GB.setLayout(LAY);
		P1.setHand(P1Hand);
		return 2;
	}
	case 3:
	{
		std::cout << "matched 3 cards, moving all 4 to Capture Pile. \n";
		system("pause");
		std::vector<int> layoutIndices = GB.whereMatch(playerCard, LAY);

		//newQuartet will store the 4 cards to be moved to the capture pile.
		std::vector<card> newQuartet;

		//move the player's hand card first.
		GB.drawCard(newQuartet, P1Hand, index);

		//for each matching pile in the layout found
		for (int i = 0; i < layoutIndices.size(); i++)
		{

			//for every card in that matching pile
			for (int j = 0; j < LAY[layoutIndices[i]].size(); j++)
			{
				//move the card from each index of the matching pile to the new quartet.
				GB.drawCard(newQuartet, LAY[layoutIndices[i]]);
				j--;
			}
		}
		GB.reduc(LAY);
		CP.push_back(newQuartet);
		GB.setLayout(LAY);
		P1.setHand(P1Hand);
		P1.setCapPile(CP);
		return 3;
	}
	}




}

/* *********************************************************************
Function Name: firstMove
Purpose: Handles the first move of the computer player, from getting index selection, to placing the hand card into the layout.
Parameters:
			gameboard GB - used to access gameboard data structures, like the Layout.
			comp CPU - used to access computer data structures, like the hand and capture pile.

Return Value: int - returns the H case value (0,1,2,3 for H0,H1,H2,H3 respectively.)

Local Variables:
				std::vector<card> CPUHand - holds the computer player Hand for the duration of the function.
				std::vector<std::vector<card>> CP - holds the computer Capture Pile for the duration of the function.
				std::vector<std::vector<card>> LAY - holds the layout for the duration of the function.
				int index - holds the selected index of the computer hand card to play
				card playerCard - holds the selected card from the hand index with which to check against the layout to determine the number of matches.
				int numMatches - holds the number of layout cards that the selected computer card matches.
				std::vector<card> newPile - temporarily holds the vector of cards to be pushed onto the layout.
				std::vector<int> layoutIndex - determines the matching layout indices of the selected computer card.
				std::vector<card> newQuartet - temporarily holds the 3 matching stockpile cards and 1 computer hand card to then be moved to the computer Capture Pile.

Algorithm: Figure out if any cards in the computer hand can earn it a point. 
			Computer Preference of play:
			1) Make a pair in the layout that already exists as a pair in its capture pile, earning 1 point.
			2) Match a triple stack, earning 1 point.
			3) Match the most amount of cards in the layout with the hand card.
			4) Play the hand card at index 0.

			the H case is returned based on the number of matches, and appropriate gameboard actions are taken to change the state of the game using a switch statement.

			
Assistance Received:
********************************************************************* */
int Client::firstMove(gameboard& GB, comp& CPU)
{
	std::vector<card> CPUHand = CPU.getHand();
	std::vector<std::vector<card>> CP = CPU.getCapPile();
	std::vector<std::vector<card>> LAY = GB.getLayout();

	gotoxy(25, 31);
	/*
	
	std::cout << "Select card to play by index: ";

	//get index of player card to play, with validation
	int index = -1;
	std::cin >> index;
	do {
		std::cerr << "Invalid index selection.";
		std::cin >> index;
	} while (index < 0 || index >= CPUHand.size());

	

	//clear the writing space
	gotoxy(25, 30);
	std::cout << "                                                                              ";
	gotoxy(25, 30);
	*/

	//check if we can make a pair that matches a cap Pile pair (earning a point)
	int index = CPU.canMakeQuartet(LAY, GB);
	card playerCard;
	
	//nowhere to play that will earn more points than just playing the most matching card.
	if (index == -1) 
	{
		//find the hand card that matches the most layout cards.
		index = CPU.mostMatches(LAY, GB);
		playerCard = CPUHand[index];
		std::cout << "The computer will play the " << playerCard.getValue() << " from its hand because it matches the most cards in the layout.\n";
	}
	else 
	{
		playerCard = CPUHand[index];
		std::cout << "The computer will play the " << playerCard.getValue() << " from its hand because it can earn a point.\n";
	}
	

	

	system("pause");
	

	

	
	int numMatches = GB.checkMatches(playerCard, LAY);
	
	switch (numMatches)
	{
		//the selected card matches no cards in the layout
	case 0:
	{
		std::cout << "No matches, adding this card to the layout.";
		//create a new pile in the layout and move the playerCard to this new pile.
		std::vector<card> newPile;
		GB.drawCard(newPile, CPUHand, index);
		LAY.push_back(newPile);
		GB.setLayout(LAY);
		CPU.setHand(CPUHand);
		return 0;
	}
	//the selected card matches one pile in the layout
	case 1:
	{
		std::cout << "1 match, creating stack pair";
		std::vector<int> layoutIndex = GB.whereMatch(playerCard, LAY);
		GB.drawCard(LAY[layoutIndex[0]], CPUHand, index);
		GB.setLayout(LAY);
		CPU.setHand(CPUHand);
		return 1;
	}
	//the selected card matches two pairs in the loadout
	case 2:
	{
		std::vector<int> layoutIndices = GB.whereMatch(playerCard, LAY);
		//the computer will just match to the first card in the layout.
		int selectedIndex = layoutIndices[0];
		

		

		GB.drawCard(LAY[selectedIndex], CPUHand, index);
		GB.setLayout(LAY);
		CPU.setHand(CPUHand); 
		return 2;
	}
	case 3:
	{
		std::cout << "matched 3 cards, moving all 4 to Capture Pile. \n";
		std::vector<int> layoutIndices = GB.whereMatch(playerCard, LAY);

		//newQuartet will store the 4 cards to be moved to the capture pile.
		std::vector<card> newQuartet;

		//move the player's hand card first.
		GB.drawCard(newQuartet, CPUHand, index);

		//for each matching pile in the layout found
		for (int i = 0; i < layoutIndices.size(); i++)
		{

			//for every card in that matching pile
			for (int j = 0; j < LAY[layoutIndices[i]].size(); j++)
			{
				//move the card from each index of the matching pile to the new quartet.
				GB.drawCard(newQuartet, LAY[layoutIndices[i]]);
				j--;
			}
		}
		GB.reduc(LAY);
		CP.push_back(newQuartet);
		GB.setLayout(LAY);
		CPU.setCapPile(CP);
		CPU.setHand(CPUHand);
		return 3;
	}
	}

}

/* *********************************************************************
Function Name: secondMove
Purpose: Handles the second move of the human player, from getting the stockpile card, to matching and placing the card into the layout.
Parameters:
			gameboard GB - used to access gameboard data structures, like the Layout.
			human P1 - used to access human data structures, like the hand and capture pile.
			int hVal - used to determine the H case of this second move. H0/H3 have one set of rules, and H1/H2 have another.

Return Value: none.

Local Variables:
				std::vector<card> P1Hand - holds the human player Hand for the duration of the function.
				std::vector<card> SP - used to get the top stockpile card, which will be played.
				std::vector<std::vector<card>> CP - holds the human Capture Pile for the duration of the function.
				std::vector<std::vector<card>> LAY - holds the layout for the duration of the function.
				int Matches - holds the number of layout cards that the stockpile card matches.
				std::vector<card> newPile - temporarily holds the vector of cards to be pushed onto the layout.
				std::vector<int> layoutIndex - determines the matching layout indices of the selected stockpile card.
				std::vector<card> newQuartet - temporarily holds the 3 matching layout cards and 1 stockpile card to then be moved to the human Capture Pile.

Algorithm: Get the card to play from the stockpile. Check how many cards in the layout this hand card matches. The number of matches determines the subcase, and GoStop rules
			are implemented for each subcase and H case using a nested switch statement. H0/H3 have one set of rules for the 4 subcases, and H1/H2 have another.
Assistance Received:
********************************************************************* */
void Client::secondMove(gameboard& GB, human& P1, int hVal)
{
	std::vector<card> P1Hand = P1.getHand();
	std::vector<card> SP = GB.getStock();
	std::vector<std::vector<card>> LAY = GB.getLayout();
	std::vector<std::vector<card>> CP = P1.getCapPile();

	//clear the writing space
	gotoxy(25, 31);
	std::cout << "                                                                              ";
	gotoxy(25, 31);

	std::cout << "Top stockpile card is " << SP[0].getValue() << " of " << SP[0].getSuit() << ".\n";
	system("pause");
	gotoxy(25, 31);

	int matches = GB.checkMatches(SP[0], LAY);
	switch (hVal % 3)
	{
		//H0 or H3
	case 0:
	{
		switch (matches)
		{
			//H0 or H3 with no cards matching drawn stockpile card
		case 0:
		{
			std::vector<card> newPile;
			newPile.push_back(SP[0]);
			SP.erase(SP.begin());
			LAY.push_back(newPile);
			break;
		}
		//H0 or H3 with 1 card matching drawn stockpile card
		case 1:
		{
			std::vector<card> newPair;
			int layoutIndex = GB.whereMatch(SP[0], LAY)[0];

			//move the matching cards from the layout and the stockpile to the temporary holder.
			newPair.push_back(SP[0]);
			SP.erase(SP.begin());
			newPair.push_back(LAY[layoutIndex][0]);
			LAY.erase(LAY.begin() + layoutIndex);

			//move the new pair to the capture pile, while checking to see if there are existing matching pairs.
			P1.matchesCapPilePair(newPair, CP);

			break;
		}
		//H0 or H3 with 2 cards matching the drawn stockpile card
		case 2:
		{
			std::vector<int> layoutIndices = GB.whereMatch(SP[0], LAY);
			std::cout << "Card drawn matches at indices " << layoutIndices[0] << " and " << layoutIndices[1] << ". Where to create a stack pair?\n";
			int selectedIndex = -1;
			std::cin >> selectedIndex;

			while (selectedIndex != layoutIndices[0] && selectedIndex != layoutIndices[1])
			{
				std::cerr << "Invalid index selected. Please choose from specified indices.";
				std::cin >> selectedIndex;
			} 

			//move the card from the top of the stockpile to the selected layout index.
			LAY[selectedIndex].push_back(SP[0]);
			SP.erase(SP.begin());

			//move the cards from the layout to a newPair.
			std::vector<card> newPair = LAY[selectedIndex];
			LAY.erase(LAY.begin() + selectedIndex);

			//checking if it matches a pair in our Capture Pile.
			P1.matchesCapPilePair(newPair, CP);


			break;
		}
		//H0 or H3 with 3 cards matching the drawn stockpile card
		case 3:
		{
			std::vector<int> layoutIndices = GB.whereMatch(SP[0], LAY);
			std::vector<card> newQuartet;

			GB.drawCard(newQuartet, SP);

			//for every matching index
			for (int i = 0; i < layoutIndices.size(); i++)
			{
				//for every card in current matching index
				for (int j = 0; j < LAY[layoutIndices[i]].size(); j++)
				{
					//pop the front card from this layout
					GB.drawCard(newQuartet, LAY[layoutIndices[i]]);
					j--;
				}
			}
			//move the new quartet to the capture pile.
			CP.push_back(newQuartet);
			break;
		}

		}
		break;
	}

	//H1 or H2
	default:
	{
		switch (matches)
		{
			//H1 or H2 with 0 layout cards matching drawn stockpile card.
		case 0:
		{
			//add the card from the stockpile to the layout.
			std::vector<card> newPile;
			GB.drawCard(newPile, SP);
			LAY.push_back(newPile);

			//find the pair made from the played card
			int pairIndex = GB.findPair(LAY);
			//for every card in the pair index
			std::vector<card> newPair;
			for (int i = 0; i < LAY[pairIndex].size(); i++)
			{
				newPair.push_back(LAY[pairIndex][i]);
			}
			LAY.erase(LAY.begin() + pairIndex);
			//check if the newly created pair matches another PAIR (not quartet) in the capture pile.
			P1.matchesCapPilePair(newPair, CP);

			break;

		}
		//H1 or H2 with 1 layout card matching the drawn stockpile card.
		case 1:
		{
			//we capture the stack pair from H1, and the new stack pair.
			int newStackMatch = GB.whereMatch(SP[0], LAY)[0];

			//move the card from the SP and the matching layout index to a newPair.
			std::vector<card> newPair;
			GB.drawCard(newPair, SP);
			GB.drawCard(newPair, LAY[newStackMatch]);

			//check if the newly created pair matches another PAIR (not quartet) in the capture pile.
			P1.matchesCapPilePair(newPair, CP);



			//capture the pair from H1.
			int layPairIndex = GB.findPair(LAY);
			std::vector<card> h1Pair;

			//move the pair from the layout to the temporary holder.
			for (int i = 0; i < 2; i++)
			{
				h1Pair.push_back(LAY[layPairIndex][i]);
			}
			LAY.erase(LAY.begin() + layPairIndex);
			//check if the pair in the layout matches any capture pile pairs.
			P1.matchesCapPilePair(h1Pair, CP);



			break;
		}
		//H1 or H2 with 2 layout cards matching the drawn stockpile card.
		case 2:
		{
			//find where the matching stackpair is located.
			int pairIndex = GB.findPair(LAY);

			//move the card from the stockpile to the layout at the matching pair index.
			GB.drawCard(LAY[pairIndex], SP);
			break;
		}
		//H1 or H2 with 3 layout cards matching the drawn stockpile card.
		case 3:
		{
			
		//CAPTURE THE 4 MATCHING CARDS FIRST
			//newPile will give a temporary spot to hold the quartet to move.
			std::vector<card> newPile;
			std::vector<int> quarInd = GB.whereMatch(SP[0], LAY);

			GB.drawCard(newPile, SP);

			for (int i = 0; i < quarInd.size(); i++)
			{
				//for every card in current matching index
				for (int j = 0; j < LAY[quarInd[i]].size(); j++)
				{
					//pop the front card from this layout
					GB.drawCard(newPile, LAY[quarInd[i]]);
					j--;
				}
			}

			CP.push_back(newPile);

		//find the remaining pair from H1 or H2 and capture it
			int pairIndex = GB.findPair(LAY);

			newPile.erase(newPile.begin(), newPile.begin() + newPile.size());
			
			if (pairIndex != -1) 
			{
				for (int i = 0; i < 2; i++) 
				{
					GB.drawCard(newPile, LAY[pairIndex]);
				}
			}
			CP.push_back(newPile);

		}
		}
		break;
	}

	}
	GB.reduc(LAY);
	GB.setLayout(LAY);
	P1.setHand(P1Hand);
	P1.setCapPile(CP);
	GB.reduc(CP);
	GB.setStock(SP);
}

/* *********************************************************************
Function Name: secondMove
Purpose: Handles the second move of the computer player, from getting the stockpile card, to matching and placing the card into the layout, and capturing the necessary cards at the end of the turn.
Parameters:
			gameboard GB - used to access gameboard data structures, like the Layout.
			comp CPU - used to access computer data structures, like the hand and capture pile.
			int hVal - used to determine the H case of this second move. H0/H3 have one set of rules, and H1/H2 have another.

Return Value: none.

Local Variables:
				std::vector<card> CPUHand - holds the computer player Hand for the duration of the function.
				std::vector<card> SP - used to get the top stockpile card, which will be played.
				std::vector<std::vector<card>> CP - holds the computer Capture Pile for the duration of the function.
				std::vector<std::vector<card>> LAY - holds the layout for the duration of the function.
				int Matches - holds the number of layout cards that the stockpile card matches.
				std::vector<card> newPile - temporarily holds the vector of cards to be pushed onto the layout.
				std::vector<int> layoutIndex - determines the matching layout indices of the selected stockpile card.
				std::vector<card> newQuartet - temporarily holds the 3 matching layout cards and 1 stockpile card to then be moved to the computer Capture Pile.

Algorithm: Get the card to play from the stockpile. Check how many cards in the layout this hand card matches. The number of matches determines the subcase, and GoStop rules
			are implemented for each subcase and H case using a nested switch statement. H0/H3 have one set of rules for the 4 subcases, and H1/H2 have another.
Assistance Received:
********************************************************************* */
void Client::secondMove(gameboard& GB, comp& CPU, int hVal) 
{
	std::vector<card> CPUHand = CPU.getHand();
	std::vector<card> SP = GB.getStock();
	std::vector<std::vector<card>> LAY = GB.getLayout();
	std::vector<std::vector<card>> CP = CPU.getCapPile();

	//clear the writing space
	gotoxy(25, 31);
	std::cout << "                                                                              ";
	gotoxy(25, 31);

	std::cout << "Top stockpile card is " << SP[0].getValue() << " of " << SP[0].getSuit() << ".";
	system("pause");
	gotoxy(25, 31);

	int matches = GB.checkMatches(SP[0], LAY);
	switch (hVal % 3)
	{
		//H0 or H3
	case 0:
	{
		switch (matches)
		{
			//H0 or H3 with no cards matching drawn stockpile card
		case 0:
		{
			std::vector<card> newPile;
			GB.drawCard(newPile, SP);
			LAY.push_back(newPile);
			break;
		}
		//H0 or H3 with 1 card matching drawn stockpile card
		case 1:
		{
			std::vector<card> newPair;
			int layoutIndex = GB.whereMatch(SP[0], LAY)[0];

			//move the matching cards from the layout and the stockpile to the temporary holder.
			GB.drawCard(newPair, SP);
			GB.drawCard(newPair, LAY[layoutIndex]);

			//move the new pair to the capture pile, while checking to see if there are existing matching pairs.
			CPU.matchesCapPilePair(newPair, CP);

			break;
		}
		//H0 or H3 with 2 cards matching the drawn stockpile card
		case 2:
		{
			std::vector<int> layoutIndices = GB.whereMatch(SP[0], LAY);
			
			int selectedIndex = 0;
			

			

			//move the card from the top of the stockpile to the selected layout index.
			GB.drawCard(LAY[selectedIndex], SP);

			//move the cards from the layout to a newPair.
			std::vector<card> newPair = LAY[selectedIndex];
			LAY.erase(LAY.begin() + selectedIndex);

			//checking if it matches a pair in our Capture Pile.
			CPU.matchesCapPilePair(newPair, CP);


			break;
		}
		//H0 or H3 with 3 cards matching the drawn stockpile card
		case 3:
		{
			std::vector<int> layoutIndices = GB.whereMatch(SP[0], LAY);
			std::vector<card> newQuartet;

			//for every matching index
			for (int i = 0; i < layoutIndices.size(); i++)
			{
				//for every card in current matching index
				for (int j = 0; j < LAY[layoutIndices[i]].size(); j++)
				{
					//pop the front card from this layout
					newQuartet.push_back(LAY[layoutIndices[i]][j]);
				}
				LAY.erase(LAY.begin() + layoutIndices[i]);
			}
			newQuartet.push_back(SP[0]);
			SP.erase(SP.begin());
			
			//move the new quartet to the capture pile.
			CP.push_back(newQuartet);
			break;
		}

		}
		break;
	}

	//H1 or H2
	default:
	{
		switch (matches)
		{
			//H1 or H2 with 0 layout cards matching drawn stockpile card.
		case 0:
		{
			//add the card from the stockpile to the layout.
			std::vector<card> newPile;
			GB.drawCard(newPile, SP);
			LAY.push_back(newPile);

			//find the pair made from the played card
			int pairIndex = GB.findPair(LAY);
			//for every card in the pair index
			std::vector<card> h1Pair;
			for (int i = 0; i < LAY[pairIndex].size(); i++)
			{
				h1Pair.push_back(LAY[pairIndex][i]);
			}
			LAY.erase(LAY.begin() + pairIndex);

			//check if the newly created pair matches another PAIR (not quartet) in the capture pile.
			CPU.matchesCapPilePair(h1Pair, CP);

			break;

		}
		//H1 or H2 with 1 layout card matching the drawn stockpile card.
		case 1:
		{
			//we capture the stack pair from H1, and the new stack pair.
			int newStackMatch = GB.whereMatch(SP[0], LAY)[0];

			//move the card from the SP and the matching layout index to a newPair.
			std::vector<card> newPair;
			newPair.push_back(SP[0]);
			SP.erase(SP.begin());
			newPair.push_back(LAY[newStackMatch][0]);
			LAY.erase(LAY.begin() + newStackMatch);

			//check if the newly created pair matches another PAIR (not quartet) in the capture pile.
			CPU.matchesCapPilePair(newPair, CP);



			//capture the pair from H1.
			int layPairIndex = GB.findPair(LAY);
			std::vector<card> h1Pair;

			//move the pair from the layout to the temporary holder.
			for (int i = 0; i < 2; i++)
			{
				h1Pair.push_back(LAY[layPairIndex][i]);
			}
			LAY.erase(LAY.begin() + layPairIndex);
			//check if the pair in the layout matches any capture pile pairs.
			CPU.matchesCapPilePair(h1Pair, CP);



			break;
		}
		//H1 or H2 with 2 layout cards matching the drawn stockpile card.
		case 2:
		{
			std::vector<int> matchingIndices = GB.whereMatch(SP[0], LAY);

			//the stockpile card only matches the stack pair
			if (matchingIndices.size() == 1)
			{
				//find where the matching stackpair is located.
				int pairIndex = GB.findPair(LAY);

				//move the card from the stockpile to the layout at the matching pair index.
				LAY[pairIndex].push_back(SP[0]);
				SP.erase(SP.begin());
			}
			else
			{
				//capture the new pair
				std::vector<card> newPair;
				GB.drawCard(newPair, LAY[matchingIndices[0]]);
				GB.drawCard(newPair, SP);

				CPU.matchesCapPilePair(newPair, CP);

				//capture the pair from H1/H2.
				int layPairIndex = GB.findPair(LAY);
				std::vector<card> h1Pair;

				//move the pair from the layout to the temporary holder.
				for (int i = 0; i < 2; i++)
				{
					h1Pair.push_back(LAY[layPairIndex][i]);
				}
				LAY.erase(LAY.begin() + layPairIndex);
				//check if the pair in the layout matches any capture pile pairs.
				CPU.matchesCapPilePair(h1Pair, CP);

				


			}
			break;
			break;
		}
		//H1 or H2 with 3 layout cards matching the drawn stockpile card.
		case 3:
		{
			//move the pair from H1 to stockpile.

			//newPile will give a temporary spot to hold the pair to move.
			std::vector<card> newPile;
			int pairIndex = GB.findPair(LAY);

			//if findPair returns a match.
			if (pairIndex != -1)
			{
				//move each card from the pair index to the temporary pile.
				for (int i = 0; i < 2; i++)
				{
					newPile.push_back(LAY[pairIndex][i]);
				}
				LAY.erase(LAY.begin() + pairIndex);
			}

			//find where (if anywhere) there is already a matching PAIR (not quartet) in the capture pile.
			CPU.matchesCapPilePair(newPile, CP);

			//capture the newly made quartet.
			std::vector<int> layoutIndices = GB.whereMatch(SP[0], LAY);
			std::vector<card> newQuartet;

			//for every matching index
			for (int i = 0; i < layoutIndices.size(); i++)
			{
				//for every card in current matching index
				for (int j = 0; j < LAY[layoutIndices[i]].size(); j++)
				{
					//pop the front card from this layout
					newQuartet.push_back(LAY[layoutIndices[i]][j]);
				}
				LAY.erase(LAY.begin() + layoutIndices[i]);
			}
			newQuartet.push_back(SP[0]);
			SP.erase(SP.begin());
			//move the new quartet to the capture pile.
			CP.push_back(newQuartet);



		}
		}
		break;
	}

	}
	GB.reduc(LAY);
	GB.setLayout(LAY);
	CPU.setHand(CPUHand);
	CPU.setCapPile(CP);
	GB.reduc(CP);
	GB.setStock(SP);
}


/* *********************************************************************
Function Name: calcScores
Purpose: Determine the round scores for each player, set the running total scores, and return a value to indicate who scored more for the round.
Parameters: 
			human P1 - used to get the human capture pile.
			comp CPU - used to get the CPU capture pile.
Return Value: int - returns 0 if the computer scored higher, returns 1 if the human scored higher. If the round scores are tied, whoIsFirst() is called, which checks playerhands and returns an appropriate value.
Local Variables:
				std::vector<int> toRet - holds the roundscores for the two players, these values are compared to determine the value to return.
				std::vector<std::vector<card>> CP - temporarily holds the human, and then the computer Capture Pile.
				int roundScore - a counter for the score of the player currently being checked.
Algorithm: check the human capture pile, then the computer. Increment a counter for each stack of 4 cards in the Capture Pile. Store the two scores in a vector, and compare them to determine what value to return.
			if there is a tie, called the whoIsFirst function, which will compare playerhands. 
Assistance Received:
********************************************************************* */
int Client::calcScores(human & P1, comp & CPU)
{
	std::vector<int> toRet;
	int roundScore = 0;
	gotoxy(25, 35);
	//set player score for round
	std::vector<std::vector<card>> CP = P1.getCapPile();
	for (int i = 0; i < CP.size(); i++) 
	{
		if (CP[i].size() == 4) 
		{
			roundScore++;
		}
	}
	std::cout << "P1 round score: " << roundScore;
	P1.setScoreAdd(roundScore);
	toRet.push_back(roundScore);

	//reset score.
	roundScore = 0;

	//set CPU score for round.
	CP = CPU.getCapPile();
	for (int i = 0; i < CP.size(); i++)
	{
		if (CP[i].size() == 4)
		{
			roundScore++;
		}
	}
	std::cout << " CPU round score: " << roundScore << "\n";
	CPU.setScoreAdd(roundScore);
	system("pause");
	toRet.push_back(roundScore);

	//human scored more points during the round
	if (toRet[0] > toRet[1])
	{
		return 1;
	}

	//computer scored more points during the round
	else if (toRet[1] > toRet[0])
	{
		return 0;
	}

	else return whoIsFirst(P1.getHand(), CPU.getHand(), 13);

}

/* *********************************************************************
Function Name: declareWin
Purpose: Determines the winning player based on the running total scores.
Parameters: 
			human P1 - used to access the human score.
			comp CPU - used to access the computer score.
Return Value: none.
Local Variables: none.
Algorithm: if the scores are the same, output tie. If either player has more points, declare that player the winner.
Assistance Received:
********************************************************************* */
void Client::declareWin(human& P1, comp& CPU) 
{
	if (P1.getScore() == CPU.getScore()) 
	{
		std::cout << "Tie game!";
	}
	else if (P1.getScore() > CPU.getScore()) 
	{
		std::cout << "Player wins!";
	}
	else 
	{
		std::cout << "CPU wins!";
	}
}

/* *********************************************************************
Function Name: saveGame
Purpose: saves the current game state in a text file.
Parameters: 
			gameboard GB - used to get the gameboard data structures.
			human P1 - used to get the human data structures.
			comp CPU - used to get the computer data structures.
			std::string turn - the player whose turn it is.
Return Value: none.
Local Variables:
				std::ofstream log - the ofstream object that writes the file.
				std::vector<card> Hand - temporarily holds any vector data structure to be printed (player hands, stockpile)
				std::vector<std::vector<card>> CP - temporarily holds and vector of vector data structures to be printed (layout, capture piles)
Algorithm: open the log, write the values of the current pile using getter functions and loops.
Assistance Received:
********************************************************************* */

void Client::saveGame(gameboard & GB, human &P1, comp & CPU, std::string turn) {
	std::ofstream log;

	//Computer Stats
	std::vector<card> Hand = CPU.getHand();
	std::vector<std::vector<card>> CP = CPU.getCapPile();
	log.open("savedGame.txt");
	log << "Round: " << GB.getRoundNum();
	log << "\n\nComputer:\n   Score: " << CPU.getScore();
	log << "\n   Hand: ";
	for (int i = 0; i < Hand.size(); i++) 
	{
		log << convertValue(Hand[i].getValue()) << Hand[i].getSuit()[0] << " ";
	}
	log << "\n   Capture Pile: ";
	for (int i = 0; i < CP.size(); i++) 
	{
		if (CP[i].size() > 1) 
		{
			for (int j = 0; j < CP[i].size(); j++) 
			{
				log << convertValue(CP[i][j].getValue()) << CP[i][j].getSuit()[0];
				if (j < CP[i].size() - 1) log << "-";
			}
		}
		else
		{
			log << convertValue(CP[i][0].getValue()) << CP[i][0].getSuit()[0];
		}
		log << " ";
	}

	//Player Stats
	Hand = P1.getHand();
	CP = P1.getCapPile();
	
	
	log << "\n\nHuman:\n   Score: " << P1.getScore();
	log << "\n   Hand: ";
	for (int i = 0; i < Hand.size(); i++)
	{
		log << convertValue(Hand[i].getValue()) << Hand[i].getSuit()[0] << " ";
	}
	log << "\n   Capture Pile: ";
	for (int i = 0; i < CP.size(); i++)
	{
		if (CP[i].size() > 1)
		{
			for (int j = 0; j < CP[i].size(); j++)
			{
				log << convertValue(CP[i][j].getValue()) << CP[i][j].getSuit()[0];
				if (j < CP[i].size() - 1) log << "-";
			}
		}
		else
		{
			log << convertValue(CP[i][0].getValue()) << CP[i][0].getSuit()[0];
		}
		log << " ";
	}

	//Layout
	log << "\n\nLayout: ";
	CP = GB.getLayout();
	for (int i = 0; i < CP.size(); i++)
	{
		if (CP[i].size() > 1)
		{
			for (int j = 0; j < CP[i].size(); j++)
			{
				log << convertValue(CP[i][j].getValue()) << CP[i][j].getSuit()[0];
				if (j < CP[i].size() - 1) log << "-";
			}
		}
		else
		{
			log << convertValue(CP[i][0].getValue()) << CP[i][0].getSuit()[0];
		}
		log << " ";
	}

	//Stock Pile
	Hand = GB.getStock();
	log << "\n\nStock Pile: ";
	for (int i = 0; i < Hand.size(); i++) 
	{
		log << convertValue(Hand[i].getValue()) << Hand[i].getSuit()[0] << " ";
	}

	log << "\n\nNext Player: " << turn;

	std::cout << "Saved, goodbye!\n";
	system("pause");
	exit(0);

}


/* *********************************************************************
Function Name: giveHelp
Purpose: supplies the human player with assistance for which card to play from the hand on their turn. 
Parameters: gameboard GB - the gameboard object which holds the current layout and stockpile.
			human P1 - the human player object which holds P1's current hand and capture pile.
Return Value: none, but outputs the help to the console window.
Local Variables: std::vector<std::vector<card>> LAY - used to obtain the current layout.
				std::vector<card> P1Hand - used to obtain the current P1 hand.
				int index - used to hold the index of the card that should be played from the P1Hand.
				card playerCard - used to hold the card information of the card at index, so that the value of the card may be accessed and output.
Algorithm: 
								Suggestion Heuristic
1) Check if the player can COMPLETE a quartet based on available hand, layout, and capture pile cards
2) Check if the player can make a quartet by matching 3 existing layout cards.
3) Check for the hand card that matches the most layout cards.
4) If no matches, suggest the card at index 0.
Assistance Received: none.
********************************************************************* */
void Client::giveHelp(gameboard &GB, human &P1) 
{
	std::vector<std::vector<card>> LAY = GB.getLayout();
	std::vector<card> P1Hand = P1.getHand();
	int index = P1.canMakeQuartet(LAY, GB);
	card playerCard;

	//nowhere to play that will earn more points than just playing the most matching card.
	if (index == -1)
	{
		//find the hand card that matches the most layout cards.
		index = P1.mostMatches(LAY, GB);
		playerCard = P1Hand[index];
		std::cout << "The computer recommends you play the " << playerCard.getValue() << " from your hand because it matches the most cards in the layout.\n";
	}
	else
	{
		playerCard = P1Hand[index];
		std::cout << "The computer recommends you play the " << playerCard.getValue() << " from your hand because it can earn a point.\n";
	}




	system("pause");
	
}

