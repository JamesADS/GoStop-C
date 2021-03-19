#pragma once
#include "player.h"
#include "gameboard.h"
class comp :
	protected player
{
public:

	

	std::vector<card>&getHand();
	std::vector<std::vector<card>>&getCapPile();
	int getScore();
	void reduceCP();
	int canMakeQuartet(std::vector<std::vector<card>>& LAY, gameboard& GB);
	int mostMatches(std::vector<std::vector<card>> &LAY, gameboard &GB);
	void setHand(std::vector<card>& setTo);
	void setCapPile(std::vector<std::vector<card>>& setTo);
	void matchesCapPilePair(std::vector<card>& toMatch, std::vector<std::vector<card>>& CP);
	void setScore(int setTo);
	void setScoreAdd(int setTo);
	void cleanup();
};



