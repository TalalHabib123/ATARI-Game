//Name:Talal Habib
//Section:SE_P
//Roll No:21I-1111
//Department:Software Engineering

#pragma once
#include <iostream>
#include "util.h"
#include <string>
#include <fstream>

using namespace std;
class Menu {
public:
	bool MENU = false;
	bool RESUME = false;
	bool HOW = false;
	bool LEADER = false;
	bool DIIFICULTY = false;
	bool PLAYER1 = false;
	bool PLAYER2 = false;
	bool KILLME = true;							//All bools for the menu functionality
	bool GAMEEND = false;
	bool CHECK_HELL = true;
	int Type = 0;
	bool DUMMY = false;
	int level = 1;
	bool Player1End = false;				//The Player has lost againts the Bot
	bool GamePlayerEnd = false;				//The Player has won in this against Bot
	bool SUBMenu = false;
	bool SelectLevel = false;
	bool FlagNo = true;
	bool Player1Name = true;
	bool Player2Name = false;
};

Menu Game_Menu;				//Object of class
