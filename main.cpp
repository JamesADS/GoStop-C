#include "Client.h"

/************************************************************
* Name:  James Giordano
* Project : Project #1 GoStop
* Class : OPL CMPS 366 01 Sp20 
* Date : 3/11/2020
************************************************************/

int main()
{
	Client gameClient;
	gameboard GB;
	comp CPU;
	human P1;
	int loadState = gameClient.loadGame(CPU, P1, GB);
	bool emptyHands = false;

	std::vector<card> P1Hand = P1.getHand();
	std::vector<card> CPUHand = CPU.getHand();
	char roundChoice = 'y';
	int roundNum = 1;
	int sortValue = 0;

	//a game was not loaded
	if (loadState == 0)
	{


		gameClient.roundStart(GB, P1, CPU);
		P1Hand = P1.getHand();
		CPUHand = CPU.getHand();

		sortValue = gameClient.whoIsFirst(P1Hand, CPUHand, 13);

	}

	//a game was loaded, computer goes first
	else if (loadState == 1)
	{
		sortValue = 0;
		P1.reduceCP();
		CPU.reduceCP();

	}

	//a game was loaded, player goes first
	else if (loadState == 2)
	{
		sortValue = 1;
		P1.reduceCP();
		CPU.reduceCP();

	}

	do {
		if (loadState == 3)
		{

			gameClient.roundStart(GB, P1, CPU);
			emptyHands = false;
		}


		P1Hand = P1.getHand();
		CPUHand = CPU.getHand();



		do {


			if (P1.getHand().size() == 0 && CPU.getHand().size() == 0)
			{
				emptyHands = true;
			}

			if (!emptyHands) {
				//the player goes first.
				if (sortValue == 1)
				{
					gameClient.playerTurn(GB, P1, CPU);

					if (P1.getHand().size() == 0 && CPU.getHand().size() == 0)
					{
						emptyHands = true;
						break;
					}

					gameClient.CPUTurn(GB, P1, CPU);
				}
				//the computer gets to go first.
				else if (sortValue == 0)
				{
					gameClient.CPUTurn(GB, P1, CPU);

					if (P1.getHand().size() == 0 && CPU.getHand().size() == 0)
					{
						emptyHands = true;
						break;
					}

					gameClient.playerTurn(GB, P1, CPU);
				}
				else
				{
					//modulo suit, reset the board state and the player hands and start the round again.
					P1.cleanup();
					CPU.cleanup();
					GB.~gameboard();
					gameboard GB(roundNum);
					gameClient.roundStart(GB, P1, CPU);
					P1Hand = P1.getHand();
					CPUHand = CPU.getHand();
					int sortValue = gameClient.whoIsFirst(P1Hand, CPUHand, 13);
				}
			}

		} while (!emptyHands);

		sortValue = gameClient.calcScores(P1, CPU);
		loadState = 3;

		gameClient.setScr(GB, P1, CPU, 2);

		std::cout << "Play another round? Y/N ";
		std::cin >> roundChoice;

		while (roundChoice != 'y' && roundChoice != 'Y' && roundChoice != 'n' && roundChoice != 'N')
		{
			std::cout << "invalid choice, try again. ";
			std::cin >> roundChoice;

		}


		GB.cleanup();
		P1.cleanup();
		CPU.cleanup();
		gameClient.setRoundNum(gameClient.getRoundNum() + 1);
	} while (roundChoice == 'y' || roundChoice == 'Y');

	gameClient.declareWin(P1, CPU);
}