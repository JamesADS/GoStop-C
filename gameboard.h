#pragma once
#include "card.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

/* *********************************************************************
Function Name: gotoxy
Purpose: moves cursor to coordinates (x, y)
Parameters: int x - the x coordinate
			int y - the y coordinate
Return Value: none
Local Variables: Coord coord - for use in the setConsoleCursorPosition function. 
Algorithm: none.
Assistance Received: https://docs.microsoft.com/en-us/windows/console/setconsolecursorposition
********************************************************************* */
inline void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* *********************************************************************
Function Name: convertValue
Purpose: converts card numeric values into strings, so they may be printed to the console or to a save file.
Parameters: int toConvert - the value to convert to string.
Return Value: string - the value is returned as a string.
Local Variables: none.
Algorithm: Handle cases using a switch statement, the face cards and aces each have a case. values 1-9 make up the deafault case. return an appropriate value in each case.
Assistance Received:
********************************************************************* */
inline std::string convertValue(int toConvert)
{
	switch (toConvert) 
	{
	case 14:
		return "1";
	case 10:
		return "X";
	case 11:
		return "J";
	case 12:
		return "Q";
	case 13:
		return "K";

	default:
		return std::to_string(toConvert);
	}

}

/* *********************************************************************
Function Name: revConvert
Purpose: converts a character value into an int value.
Parameters: char toConvert - the character to convert.
Return Value: int -returns the value as an integer.
Local Variables: int x - holds toConvert as an integer data type so it may be returned as such.
Algorithm: handle cases using a switch statement. handle the face cards and ace with a case each, 1-9 comprise the default case.
Assistance Received:
********************************************************************* */
inline int revConvert(char toConvert)
{
	switch (toConvert)
	{
	case '1':
		return 14;
	case 'X':
		return 10;
	case 'J':
		return 11;
	case 'Q':
		return 12;
	case 'K':
		return 13;

	default:
		int x = toConvert - '0';
		return x;
	}

}

class gameboard :
	protected card, protected player
	
{
public:
	gameboard();
	gameboard(int roundNum);
	void roundStart(std::vector<card> &p1Hand, std::vector<card> &compHand);
	void createDeck();
	void shuffleDeck();
	int checkMatches(card &playerCard, std::vector<std::vector<card>> &layoutPile);
	void printPile(std::vector<card> &toPrint, int &x, int &y);
	void printNums(int printCount, int& x, int& y);
	void printCard(std::vector<card> &printFrom, int index, int &x, int &y);
	void drawCard(std::vector<card> &destPile, std::vector<card> &srcPile);
	void drawCard(std::vector<card> &destPile, std::vector<card> &srcPile, int index);
	void dealCards(std::vector<card> &p1Hand, std::vector<card> &compHand);
	std::vector<std::vector<card>> &getLayout();
	void setLayout(std::vector<std::vector<card>> &setTo);
	std::vector<card> &getStock();
	std::vector<int> whereMatch(card& playerCard, std::vector<std::vector<card>>& layoutPile);
	int findPair(std::vector<std::vector<card>> &searchThrough);
	void printStacks(std::vector<std::vector<card>> &toPrint, int &x, int &y);
	void setStock(std::vector<card>& setTo);
	void reduc(std::vector<std::vector<card>>& toReduce);
	int getRoundNum();
	void setRoundNum(int setTo);
	void cleanup();
	~gameboard();
private:
	int roundNum;
protected:
	
	std::vector<card> deck;
	std::vector<card> stockpile;
	std::vector<std::vector<card>> layout;
};

