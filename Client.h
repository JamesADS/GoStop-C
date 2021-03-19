#pragma once
#include "player.h"
#include "gameboard.h"
#include "comp.h"
#include "human.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <regex>

class Client :
	protected gameboard, protected player, protected comp, protected human
{
public:
	Client();
	int loadGame(comp& CPU, human& P1, gameboard& GB);
	bool tryComp(std::smatch m, std::regex RX, std::string line, comp& CPU);
	bool tryHuman(std::smatch m, std::regex RX, std::string line, human& P1);
	bool tryLayout(std::smatch m, std::regex RX, std::string line, gameboard& GB);
	bool tryStock(std::smatch m, std::regex RX, std::string line, gameboard& GB);
	void roundStart(gameboard &GB, human &P1, comp &CPU);
	int whoIsFirst(std::vector<card> P1Hand, std::vector<card> CPUHand, int cardValue);
	void playerTurn(gameboard& GB, human& P1, comp& CPU);
	void CPUTurn(gameboard& GB, human& P1, comp& CPU);
	int getRoundNum();
	void setRoundNum(int setTo);
	int getChoice();
	int offerTurn(gameboard &GB, human &P1, comp &CPU, int turn);
	void setScr(gameboard& GB, human& P1, comp& CPU, int turn);
	int firstMove(gameboard &GB, human &P1);
	int firstMove(gameboard &GB, comp &CPU);
	void secondMove(gameboard& GB, human& P1, int hVal);
	void secondMove(gameboard& GB, comp& CPU, int hVal);
	void quit();
	void saveGame(gameboard &GB, human &P1, comp & CPU, std::string turn);
	void giveHelp(gameboard& GB, human& P1);
	int calcScores(human &P1, comp &CPU);
	void declareWin(human& P1, comp& CPU);
private:
	int roundNum;
	int choice;
protected:
	
};



