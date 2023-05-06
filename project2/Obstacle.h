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


class Obstacles {
public:
	int x_coor;
	int y_coor;
	int width;		//Sets the Obstacels data such as x_axis,y_axis ,height,type..
	int height;
	int type;
	int dummy;
	Obstacles()
	{
		x_coor = -1;
		y_coor = -1;
		width = -1;
		height = -1;
		type = -1;
		dummy = -1;
	}
};
