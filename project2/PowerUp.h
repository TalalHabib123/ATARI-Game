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


int StartingXJ[10] = { 50,100,150,270,550,700,70,870,900,950 };
int StartingYJ[10] = { 50,100,150,700,650,690,90,150,250,350 };

class PowerUps {
public:
	int Type = -1;
	int speed = -1;					//sets the data
	int Distance = -1;
	int x_coord = -1;
	int y_coord = -1;
	bool Display = false;
	PowerUps()
	{
		Type = -1;
		speed = -1;
		Distance = -1;
		x_coord = -1;
		y_coord = -1;
	}
	PowerUps(int ID)
	{
		if (ID == 1)
		{
			Type = 1;
			speed = 10;
			Distance = 20;
			x_coord = StartingXJ[rand()%10];
			y_coord = StartingYJ[rand() % 10];
		}
		else if (ID == 2)
		{
			Type = 2;
			speed = 20;
			Distance = 50;
			x_coord = StartingXJ[rand() % 10];
			y_coord = StartingYJ[rand() % 10];
		}
	}

	void POWERUPSDisplay(int ID)					//Display differeny type of powerups
	{
		if (ID == 1)
		{
			Type = 1;
			speed = 10;
			Distance = 20;
			x_coord = StartingXJ[rand() % 10];
			y_coord = StartingYJ[rand() % 10];
		}
		else if (ID == 2)
		{
			Type = 2;
			speed = 20;
			Distance = 50;
			x_coord = StartingXJ[rand() % 10];
			y_coord = StartingYJ[rand() % 10];
		}
	}

	void RESET()							//resets the power up
	{
		if (Type == 1)
		{
			Type = 1;
			speed = 10;
			Distance = 20;
			x_coord = StartingXJ[rand() % 10];
			y_coord = StartingYJ[rand() % 10];
			Display = false;
		}
		else if (Type == 2)
		{
			Type = 2;
			speed = 20;
			Distance = 50;
			x_coord = StartingXJ[rand() % 10];
			y_coord = StartingYJ[rand() % 10];
			Display = false;
		}
	}

	void DRAWPOWERUP()					//draws the power up on game display
	{
		if (Type == 1)
		{
			DrawCircle(x_coord, y_coord, 10, colors[PURPLE]);
		}
		else if (Type == 2)
		{
			DrawCircle(x_coord, y_coord, 10, colors[DARK_BLUE]);
		}
	}
};

PowerUps First_PowerUp(1);				//object of class
PowerUps Second_PowerUp(2);				//object of class
