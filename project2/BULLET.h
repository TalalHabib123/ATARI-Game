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
class Bullet {
protected:
	int Bullet_x;
	int Bullet_y;


public:
	bool Top;
	bool bottom;
	bool left;
	bool right;
	bool bullet;
	int i = 0;						//different data for bullet class for the tank
	int j = 0;
	int max_dis = 40;
	bool PowerUp = false;
	int PowerUpType = false;

	Bullet(int x, int y, bool i, bool j, bool k, bool l, bool speed)
	{
		Bullet_x = x;
		Bullet_y = y;
		PowerUp = false;
		PowerUpType = -1;
		Top = i;
		bottom = j;
		left = k;
		right = l;
		bullet = speed;
	}
	void setX(int i)				//setter
	{
		Bullet_x += i;
	}
	void setY(int j)				//setter
	{
		Bullet_y += j;
	}
	int GetX()						//getter
	{
		return Bullet_x;
	}
	int GetY()						//getter
	{
		return Bullet_y;
	}

};
