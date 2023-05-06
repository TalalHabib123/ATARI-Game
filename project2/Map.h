//Name:Talal Habib
//Section:SE_P
//Roll No:21I-1111
//Department:Software Engineering

#pragma once
#include <iostream>
#include "util.h"
#include <string>
#include <fstream>
#include "Obstacle.h"

using namespace std;


class Map {
public:
	Obstacles Map_Obstacles[10];			//total obstacles on each map
	bool No_Obstacles = false;
	bool Map_Load[3];
	Map()
	{
		Map_Load[0] = false;
		Map_Load[1] = false;
		Map_Load[2] = false;
	}
	void MapLoad1()						//first map with obstacles being dislay and obstackeles 
	{
		DrawLine(0, 5, 1020, 5, 10, colors[ORANGE_RED]);
		DrawLine(5, 0, 5, 750, 10, colors[ORANGE_RED]);
		DrawLine(0, 745, 1020, 745, 10, colors[ORANGE_RED]);
		DrawLine(1015, 750, 1015, 0, 10, colors[ORANGE_RED]);


		DrawRectangle(200, 300, 30, 200, colors[LIME_GREEN]);
		Map_Obstacles[0].x_coor = 200;
		Map_Obstacles[0].y_coor = 300;
		Map_Obstacles[0].height = 200;
		Map_Obstacles[0].width = 30;
		Map_Obstacles[0].type = 1;
		
		DrawRectangle(180, 600, 60, 20, colors[LIME_GREEN]);
		Map_Obstacles[1].x_coor = 180;
		Map_Obstacles[1].y_coor = 600;
		Map_Obstacles[1].height = 20;
		Map_Obstacles[1].width = 60;
		Map_Obstacles[1].type = 1;
		DrawRectangle(180, 170, 60, 20, colors[LIME_GREEN]);
		Map_Obstacles[2].x_coor = 180;
		Map_Obstacles[2].y_coor = 170;
		Map_Obstacles[2].height = 20;
		Map_Obstacles[2].width = 60;
		Map_Obstacles[2].type = 1;

		DrawRectangle(510, 530, 30, 50, colors[LIME_GREEN]);
		Map_Obstacles[3].x_coor = 510;
		Map_Obstacles[3].y_coor = 530;
		Map_Obstacles[3].height = 50;
		Map_Obstacles[3].width = 30;
		Map_Obstacles[3].type = 1;
		DrawRectangle(510, 210, 30, 50, colors[LIME_GREEN]);
		Map_Obstacles[4].x_coor = 510;
		Map_Obstacles[4].y_coor = 210;
		Map_Obstacles[4].height = 50;
		Map_Obstacles[4].width = 30;
		Map_Obstacles[4].type = 1;

		DrawRectangle(340, 390, 50, 30, colors[LIME_GREEN]);
		Map_Obstacles[5].x_coor = 340;
		Map_Obstacles[5].y_coor = 390;
		Map_Obstacles[5].height = 30;
		Map_Obstacles[5].width = 50;
		Map_Obstacles[5].type = 1;
		DrawRectangle(650, 390, 50, 30, colors[LIME_GREEN]);
		Map_Obstacles[6].x_coor = 650;
		Map_Obstacles[6].y_coor = 390;
		Map_Obstacles[6].height = 30;
		Map_Obstacles[6].width = 50;
		Map_Obstacles[6].type = 1;


		DrawRectangle(800, 300, 30, 200, colors[LIME_GREEN]);
		Map_Obstacles[7].x_coor = 800;
		Map_Obstacles[7].y_coor = 300;
		Map_Obstacles[7].height = 200;
		Map_Obstacles[7].width = 30;
		Map_Obstacles[7].type = 1;
	
		DrawRectangle(800, 600, 60, 20, colors[LIME_GREEN]);
		Map_Obstacles[8].x_coor = 800;
		Map_Obstacles[8].y_coor = 600;
		Map_Obstacles[8].height = 20;
		Map_Obstacles[8].width = 60;
		Map_Obstacles[8].type = 1;
		DrawRectangle(800, 170, 60, 20, colors[LIME_GREEN]);
		Map_Obstacles[9].x_coor = 800;
		Map_Obstacles[9].y_coor = 170;
		Map_Obstacles[9].height = 20;
		Map_Obstacles[9].width = 60;
		Map_Obstacles[9].type = 1;

		No_Obstacles = false;

	}
	void MapLoad2()									//second map with obstacles being dislay and obstackeles 
	{
		DrawLine(0, 5, 1020, 5, 10, colors[ORANGE_RED]);
		DrawLine(5, 0, 5, 750, 10, colors[ORANGE_RED]);
		DrawLine(0, 745, 1020, 745, 10, colors[ORANGE_RED]);          //Draws the Border of the Map
		DrawLine(1015, 750, 1015, 0, 10, colors[ORANGE_RED]);

		DrawRectangle(200, 300, 30, 200, colors[LIME_GREEN]);
		Map_Obstacles[0].x_coor = 200;
		Map_Obstacles[0].y_coor = 300;
		Map_Obstacles[0].height = 200;
		Map_Obstacles[0].width = 30;
		Map_Obstacles[0].type = 1;




		DrawRectangle(350, 300, 20, 50, colors[LIME_GREEN]);
		Map_Obstacles[1].x_coor = 350;
		Map_Obstacles[1].y_coor = 300;
		Map_Obstacles[1].height = 50;
		Map_Obstacles[1].width = 20;
		Map_Obstacles[1].type = 1;
		DrawRectangle(430, 200, 50, 20, colors[LIME_GREEN]);
		Map_Obstacles[2].x_coor = 430;
		Map_Obstacles[2].y_coor = 200;
		Map_Obstacles[2].height = 20;
		Map_Obstacles[2].width = 50;
		Map_Obstacles[2].type = 1;

		DrawRectangle(350, 450, 20, 50, colors[LIME_GREEN]);
		Map_Obstacles[3].x_coor = 350;
		Map_Obstacles[3].y_coor = 450;
		Map_Obstacles[3].height = 50;
		Map_Obstacles[3].width = 20;
		Map_Obstacles[3].type = 1;
		DrawRectangle(430, 550, 50, 20, colors[LIME_GREEN]);
		Map_Obstacles[4].x_coor = 430;
		Map_Obstacles[4].y_coor = 550;
		Map_Obstacles[4].height = 20;
		Map_Obstacles[4].width = 50;
		Map_Obstacles[4].type = 1;

		DrawRectangle(680, 300, 20, 50, colors[LIME_GREEN]);
		Map_Obstacles[5].x_coor = 680;
		Map_Obstacles[5].y_coor = 300;
		Map_Obstacles[5].height = 50;
		Map_Obstacles[5].width = 20;
		Map_Obstacles[5].type = 1;
		DrawRectangle(580, 200, 50, 20, colors[LIME_GREEN]);
		Map_Obstacles[6].x_coor = 580;
		Map_Obstacles[6].y_coor = 200;
		Map_Obstacles[6].height = 20;
		Map_Obstacles[6].width = 50;
		Map_Obstacles[6].type = 1;

		DrawRectangle(680, 450, 20, 50, colors[LIME_GREEN]);
		Map_Obstacles[7].x_coor = 680;
		Map_Obstacles[7].y_coor = 450;
		Map_Obstacles[7].height = 50;
		Map_Obstacles[7].width = 20;
		Map_Obstacles[7].type = 1;
		DrawRectangle(580, 550, 50, 20, colors[LIME_GREEN]);
		Map_Obstacles[8].x_coor = 580;
		Map_Obstacles[8].y_coor = 550;
		Map_Obstacles[8].height = 20;
		Map_Obstacles[8].width = 50;
		Map_Obstacles[8].type = 1;

		DrawRectangle(800, 300, 30, 200, colors[LIME_GREEN]);
		Map_Obstacles[9].x_coor = 800;
		Map_Obstacles[9].y_coor = 300;
		Map_Obstacles[9].height = 200;
		Map_Obstacles[9].width = 30;
		Map_Obstacles[9].type = 1;
	

		No_Obstacles = false;
	}
	void MapLoad3()											//third map with obstacles being dislay and obstackeles 
	{
		DrawLine(0, 5, 1020, 5, 10, colors[ORANGE_RED]);
		DrawLine(5, 0, 5, 750, 10, colors[ORANGE_RED]);
		DrawLine(0, 745, 1020, 745, 10, colors[ORANGE_RED]);          //Draws the Border of the Map
		DrawLine(1015, 750, 1015, 0, 10, colors[ORANGE_RED]);

		DrawRectangle(200, 300, 30, 200, colors[LIME_GREEN]);
		Map_Obstacles[0].x_coor = 200;
		Map_Obstacles[0].y_coor = 300;
		Map_Obstacles[0].height = 200;
		Map_Obstacles[0].width = 30;
		Map_Obstacles[0].type = 1;
	
		DrawRectangle(180, 600, 60, 20, colors[LIME_GREEN]);
		Map_Obstacles[1].x_coor = 180;
		Map_Obstacles[1].y_coor = 600;
		Map_Obstacles[1].height = 20;
		Map_Obstacles[1].width = 60;
		Map_Obstacles[1].type = 1;
		DrawRectangle(180, 170, 60, 20, colors[LIME_GREEN]);
		Map_Obstacles[2].x_coor = 180;
		Map_Obstacles[2].y_coor = 170;
		Map_Obstacles[2].height = 20;
		Map_Obstacles[2].width = 60;
		Map_Obstacles[2].type = 1;

		//DrawString(500, 400, "MAP 3", colors[MISTY_ROSE]);


		DrawRectangle(460, 530, 150, 20, colors[LIME_GREEN]);
		Map_Obstacles[3].x_coor = 460;
		Map_Obstacles[3].y_coor = 530;
		Map_Obstacles[3].height = 20;
		Map_Obstacles[3].width = 150;
		Map_Obstacles[3].type = 1;
		DrawRectangle(460, 230, 150, 20, colors[LIME_GREEN]);
		Map_Obstacles[4].x_coor = 460;
		Map_Obstacles[4].y_coor = 230;
		Map_Obstacles[4].height = 20;
		Map_Obstacles[4].width = 150;
		Map_Obstacles[4].type = 1;

		DrawRectangle(340, 320, 20, 150, colors[LIME_GREEN]);
		Map_Obstacles[5].x_coor = 340;
		Map_Obstacles[5].y_coor = 320;
		Map_Obstacles[5].height = 150;
		Map_Obstacles[5].width = 20;
		Map_Obstacles[5].type = 1;
		DrawRectangle(690, 320, 20, 150, colors[LIME_GREEN]);
		Map_Obstacles[6].x_coor = 690;
		Map_Obstacles[6].y_coor = 320;
		Map_Obstacles[6].height = 150;
		Map_Obstacles[6].width = 20;
		Map_Obstacles[6].type = 1;

		DrawRectangle(800, 300, 30, 200, colors[LIME_GREEN]);
		Map_Obstacles[7].x_coor = 800;
		Map_Obstacles[7].y_coor = 300;
		Map_Obstacles[7].height = 200;
		Map_Obstacles[7].width = 30;
		Map_Obstacles[7].type = 1;
		
		DrawRectangle(800, 600, 60, 20, colors[LIME_GREEN]);
		Map_Obstacles[8].x_coor = 800;
		Map_Obstacles[8].y_coor = 600;
		Map_Obstacles[8].height = 20;
		Map_Obstacles[8].width = 60;
		Map_Obstacles[8].type = 1;
		DrawRectangle(800, 170, 60, 20, colors[LIME_GREEN]);
		Map_Obstacles[9].x_coor = 800;
		Map_Obstacles[9].y_coor = 170;
		Map_Obstacles[9].height = 20;
		Map_Obstacles[9].width = 60;
		Map_Obstacles[9].type = 1;

		No_Obstacles = false;
	}
	void MapLoad4()
	{
		DrawLine(0, 5, 1020, 5, 10, colors[ORANGE_RED]);
		DrawLine(5, 0, 5, 750, 10, colors[ORANGE_RED]);
		DrawLine(0, 745, 1020, 745, 10, colors[ORANGE_RED]);          //Draws the Border of the Map
		DrawLine(1015, 750, 1015, 0, 10, colors[ORANGE_RED]);
		No_Obstacles = true;
	}
};


Map New_Map;