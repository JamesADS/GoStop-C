#pragma once
#include "card.h"
//#include "gameboard.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

class player :
	protected card
{
public:
	player();
	std::vector<card> getHand();
	std::vector<std::vector<card>> getCapPile();
	int getScore();
	void setScore(int setTo);
	int matchesCapPilePair(card toMatch, player &matcher);
private:
protected:
	int score;
	std::vector<card> hand;
	std::vector<std::vector<card>> capPile;

};



