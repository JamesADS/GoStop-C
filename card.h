#pragma once
#include <string>


class card
{
public:
	card();
	card(int uvalue, std::string usuit);
	card(int uvalue, char usuit);
	std::string getSuit();
	int getValue();
private:
protected:
	int value;
	std::string suit;
};


