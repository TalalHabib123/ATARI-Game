//Name:Talal Habib
//Section:SE_P
//Roll No:21I-1111
//Department:Software Engineering

#pragma once
#include <iostream>
#include <fstream>
#include "util.h"
#include <string>
#include <fstream>
#include "Obstacle.h"
#include "BULLET.h"
#include "Map.h"
#include "MENU.h"
#include "Player.h"
#include "PowerUp.h"

using namespace std;

int StartingXN[10] = { 50,100,150,270,550,700,70,870,900,950 };
int StartingYN[10] = { 50,100,150,700,650,690,90,150,250,350 };

class NPC :public Bullet {
public:
	string name;
	int x_coord = StartingXN[rand() % 10];
	int y_coord = StartingYN[rand() % 10];
	int score = 0;
	bool Died = false;
	int wins = 0;
	int speed_Tank = 100;

	bool simple_path = false;
	bool Angled_path = false;
	bool right_up = false;
	bool right_down = false;
	bool left_up = false;
	bool left_down = false;

	bool obstacles_Detected = false;				//From Here
	bool Left_stop = false;
	bool right_stop = false;
	bool up_stop = false;
	bool down_stop = false;
	bool right_go = false;
	bool left_go = false;							//All are variables being used for the obstacle detection algo and path reconfiguring of the AI
	bool up_go = false;
	bool down_up = false;
	int left_obs = -1;
	int right_obs = -1;
	int up_obs = -1;
	int down_obs = -1;								
	bool left_path = false;
	bool right_path = false;
	bool up_path = false;
	bool down_path = false;							//To Here 
	NPC() :Bullet{ x_coord,y_coord,false,false,false,true,false } {}

	void ResetBullet()
	{
		Bullet_x = x_coord;
		Bullet_y = y_coord;
	}

	void NEWGAME()
	{
		x_coord = StartingXN[rand() % 10];
		y_coord = StartingYN[rand() % 10];
		//check_player = false;
		Died = false;
		left = true;
		right = false;
		Top = false;
		bottom = false;
		i = 0;
		j = 0;
		Bullet_x = x_coord;
		Bullet_y = y_coord;

		//NEW_GAME = true;
	}

	void DrawTank()
	{
		if (Game_Menu.PLAYER1 == true)					//Draws the Tank as well as the UFO and the Rocket ship
		{
				if (Game_Menu.level == 1)
				{
					if (right == true)
					{
						DrawRectangle(x_coord + 1 + 2 + 2, y_coord, 15, 23, colors[GREEN]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord + 15, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord - 5, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 1 + 2 + 2, y_coord + 7, 25, 4, colors[GREEN]);
					}
					else if (left == true)
					{
						DrawRectangle(x_coord, y_coord, 15, 23, colors[GREEN]);
						DrawRectangle(x_coord - 5, y_coord + 15, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 5, y_coord - 5, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 10, y_coord + 7, 25, 4, colors[GREEN]);
					}
					else if (Top == true)
					{
						DrawRectangle(x_coord, y_coord + 5, 23, 15, colors[GREEN]);
						DrawRectangle(x_coord + 15, y_coord + 5 - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 5, y_coord + 5 - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 7, y_coord + 5, 4, 25, colors[GREEN]);
					}

					else if (bottom == true)
					{
						DrawRectangle(x_coord, y_coord, 23, 15, colors[GREEN]);
						DrawRectangle(x_coord + 15, y_coord - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 5, y_coord - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 7, y_coord - 10, 4, 25, colors[GREEN]);
					}
					speed_Tank = 120;
				}
				else if (Game_Menu.level == 2)
				{
					if (right == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2 + 3, y_coord + 5 + 3, 10, colors[GREEN]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord + 15, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord - 5, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 1 + 2 + 2, y_coord + 7, 25, 4, colors[GREEN]);
					}
					else if (left == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3, 10, colors[GREEN]);
						DrawRectangle(x_coord - 5, y_coord + 15, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 5, y_coord - 5, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 10, y_coord + 7, 25, 4, colors[GREEN]);
					}
					else if (Top == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3 + 2, 10, colors[GREEN]);
						DrawRectangle(x_coord + 15, y_coord + 5 - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 5, y_coord + 5 - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 7, y_coord + 5, 4, 25, colors[GREEN]);
					}

					else if (bottom == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3, 10, colors[GREEN]);
						DrawRectangle(x_coord + 15, y_coord - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 5, y_coord - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 7, y_coord - 10, 4, 25, colors[GREEN]);
					}
					speed_Tank =100;
				}
				else if (Game_Menu.level == 3)
				{
					if (right == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2 + 3, y_coord + 5 + 3, 10, colors[GREEN]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord - 5, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 1 + 2 + 2, y_coord + 7, 25, 4, colors[GREEN]);
					}
					else if (left == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3, 10, colors[GREEN]);
						DrawRectangle(x_coord - 5, y_coord - 5, 25, 8, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord - 10, y_coord + 7, 25, 4, colors[GREEN]);
					}
					else if (Top == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3 + 2, 10, colors[GREEN]);
						DrawRectangle(x_coord - 5, y_coord + 5 - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 7, y_coord + 5, 4, 25, colors[GREEN]);
					}

					else if (bottom == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3, 10, colors[GREEN]);
						DrawRectangle(x_coord - 5, y_coord - 5, 8, 25, colors[GREEN_YELLOW]);
						DrawRectangle(x_coord + 7, y_coord - 10, 4, 25, colors[GREEN]);
					}
					speed_Tank = 80;
				}
		}
		glutPostRedisplay();
	}

	void PathGeneration()  //Initial Function for the creation of the Path but was not used and dead code 
	{
		if (x_coord < New_Player1.x_coord)
		{

			x_coord += 10;
		}
		else if (x_coord > New_Player1.x_coord)
		{
			x_coord -= 10;
		}
		else if (y_coord < New_Player1.y_coord)
		{
			y_coord += 10;
		}
		else if (y_coord > New_Player1.y_coord)
		{
			y_coord -= 10;
		}
	}

	void BulletPath()						//Checks whether there ibstacles inside the striaght path of the bullet
	{
		if (Bullet_x - 10 <= 5)
		{
			Bullet_x += 10;
			i = 4;
			/*New_Player1.bottom = false;
			New_Player1.Top = false;
			New_Player1.right = true;
			New_Player1.left = false;*/
		}
		if (Bullet_x + 10 >= 995)
		{
			Bullet_x -= 10;
			i = 3;

		}
		if (Bullet_y + 10 >= 725)
		{
			Bullet_y -= 10;
			i = 2;

		}
		if (Bullet_y - 10 <= 5)
		{
			Bullet_y += 10;
			i = 1;
		}
		if (New_Map.No_Obstacles == false)
		{

			for (int o = 0; o < 10; o++)
			{
				if (i == 4)
				{
					if (Bullet_y + 10 >= New_Map.Map_Obstacles[o].y_coor - 5 && Bullet_y <= (New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height))
					{
						if (Bullet_x + 10 >= New_Map.Map_Obstacles[o].x_coor - 5 && Bullet_x <= New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width)
						{
							Bullet_x -= 10;
							i = 3;
							/*/right = false;
							left = true;
							Top = false;
							bottom = false;*/
						}
					}
				}
				if (i == 3)
				{
					if (Bullet_y + 10 >= (New_Map.Map_Obstacles[o].y_coor - 5) && Bullet_y <= (New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height))
					{
						if (Bullet_x >= New_Map.Map_Obstacles[o].x_coor && Bullet_x - 9 <= New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width)
						{
							Bullet_x += 10;
							i = 4;
							/*/Top = false;
							bottom = false;
							right = true;
							left = false;*/
						}
					}
				}
				if (i == 1)
				{
					if (Bullet_x + 15 >= New_Map.Map_Obstacles[o].x_coor - 5 && Bullet_x <= (New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width))
					{
						if (Bullet_y + 15 >= New_Map.Map_Obstacles[o].y_coor - 5 && Bullet_y <= New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height)
						{
							Bullet_y -= 10;
							i = 2;
							/*/Top = false;
							bottom = true;
							right = false;
							left = false;*/
						}
					}
				}
				if (i == 2)
				{
					if (Bullet_x + 15 >= (New_Map.Map_Obstacles[o].x_coor - 5) && Bullet_x <= (New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width))
					{
						if (Bullet_y >= New_Map.Map_Obstacles[o].y_coor && Bullet_y <= New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height)
						{
							Bullet_y += 10;
							i = 1;
							/*Top = true;
							bottom = false;
							right = false;
							left = false;*/
						}
					}
				}
			}
		}
	}

	void ResetObsDetection()					//Resets the Obstacles detected by the Bot
	{
		obstacles_Detected = false;				//From Here
		Left_stop = false;
		right_stop = false;
		up_stop = false;
		down_stop = false;
		right_go = false;
		left_go = false;							//All are variables being used for the obstacle detection algo and path reconfiguring of the AI
		up_go = false;
		down_up = false;
		left_obs = -1;
		right_obs = -1;
		up_obs = -1;
		down_obs = -1;
		left_path = false;
		right_path = false;
		up_path = false;
		down_path = false;							//To Here 
	}

	void PathFinding()							//Creates a new possible path for the Bot in the case of the Obstacles
	{
		if (Left_stop == true)
		{
			if (New_Player1.y_coord >= y_coord)
			{
				if (up_stop == false)
				{
					up_go = true;
					Top = true;
					bottom = false;
					right = false;
					left = false;
				}
				else if (down_stop == false)
				{
					down_up = true;
					Top = false;
					bottom = true;
					right = false;
					left = false;
				}
			}
			else if (New_Player1.y_coord < y_coord)
			{
				if (down_stop == false)
				{
					down_up = true;
					Top = false;
					bottom = true;
					right = false;
					left = false;
				}
				else if (up_stop == false)
				{
					up_go = true;
					Top = true;
					bottom = false;
					right = false;
					left = false;
				}
			}
			
		}
		else if (right_stop == true)
		{
			if (New_Player1.y_coord >= y_coord)
			{
				if (up_stop == false)
				{
					up_go = true;
					Top = true;
					bottom = false;
					right = false;
					left = false;
				}
				else if (down_stop == false)
				{
					down_up = true;
					Top = false;
					bottom = true;
					right = false;
					left = false;
				}
			}
			else if (New_Player1.y_coord < y_coord)
			{
				if (down_stop == false)
				{
					down_up = true;
					Top = false;
					bottom = true;
					right = false;
					left = false;
				}
				else if (up_stop == false)
				{
					up_go = true;
					Top = true;
					bottom = false;
					right = false;
					left = false;
				}
			}
		}
		else if (up_stop == true)
		{
			if (New_Player1.x_coord >= x_coord)
			{
				if (right_stop == false)
				{
					right_go = true;
					Top = false;
					bottom = false;
					right = true;
					left = false;
				}
				else if (Left_stop == false)
				{
					left_go = true;
					Top = false;
					bottom = false;
					right = false;
					left = true;
				}
			}
			else if (New_Player1.x_coord < x_coord)
			{
				if (Left_stop == false)
				{
					left_go = true;
					Top = false;
					bottom = false;
					right = false;
					left = true;
				}
				else if (right_stop == false)
				{
					right_go = true;
					Top = false;
					bottom = false;
					right = true;
					left = false;
				}
			}
			
		}
		else if (down_stop == true)
		{
		if (New_Player1.x_coord >= x_coord)
		{
			if (right_stop == false)
			{
				right_go = true;
				Top = false;
				bottom = false;
				right = true;
				left = false;
			}
			else if (Left_stop == false)
			{
				left_go = true;
				Top = false;
				bottom = false;
				right = false;
				left = true;
			}
		}
		else if (New_Player1.x_coord < x_coord)
		{
			if (Left_stop == false)
			{
				left_go = true;
				Top = false;
				bottom = false;
				right = false;
				left = true;
			}
			else if (right_stop == false)
			{
				right_go = true;
				Top = false;
				bottom = false;
				right = true;
				left = false;
			}
		}
		}
	}

	void PathDetection()				//Checks Whether theres obstacle in the path of the Bot
	{
		for (int o = 0; o < 10; o++)
		{
			if (right == true)
			{
				if (y_coord + 15 >= New_Map.Map_Obstacles[o].y_coor - 5 && y_coord <= (New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height))
				{
					if (x_coord + 15 >= New_Map.Map_Obstacles[o].x_coor - 5 && x_coord <= New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width)
					{
						x_coord -= 10;
						right_stop = true;
						obstacles_Detected = true;
						right_obs = o;
						PathFinding();
					}
				}
			}
			if (left == true)
			{
				if (y_coord + 15 >= (New_Map.Map_Obstacles[o].y_coor - 5) && y_coord <= (New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height))
				{
					if (x_coord >= New_Map.Map_Obstacles[o].x_coor && x_coord - 9 <= New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width)
					{
						x_coord += 10;
						Left_stop = true;
						obstacles_Detected = true;
						left_obs = o;
						PathFinding();
					}
				}
			}
			if (Top == true)
			{
				if (x_coord + 15 >= New_Map.Map_Obstacles[o].x_coor - 5 && x_coord <= (New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width))
				{
					if (y_coord + 15 >= New_Map.Map_Obstacles[o].y_coor - 5 && y_coord <= New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height)
					{
						y_coord -= 10;
						up_stop = true;
						obstacles_Detected = true;
						up_obs = o;
						PathFinding();
					}
				}
			}
			if (bottom == true)
			{
				if (x_coord + 15 >= (New_Map.Map_Obstacles[o].x_coor - 5) && x_coord <= (New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width))
				{
					if (y_coord >= New_Map.Map_Obstacles[o].y_coor && y_coord <= New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height)
					{
						y_coord += 10;
						down_stop = true;
						obstacles_Detected = true;
						down_obs = o;
						PathFinding();
					}
				}
			}
		}
	}

	void AngledPath()					//Checks the Angled path of the Bullet
	{
		if (Bullet_x - 10 <= 5)
		{
			Bullet_x += 10;
			if (left_down == true)
			{
				left_down = false;
				right_down = true;
			}
			else if (left_up == true)
			{
				left_up = false;
				right_up = true;
			}
		}
		if (Bullet_x + 10 >= 995)
		{
			Bullet_x -= 10;
			if (right_up = true)
			{
				right_up = false;
				left_up = true;
			}
			else if (right_down == true)
			{
				right_down = false;
				left_down = true;
			}

		}
		if (Bullet_y + 10 >= 725)
		{
			Bullet_y -= 10;
			if (right_up = true)
			{
				right_up = false;
				right_down = true;
			}
			else if (left_up == true)
			{
				left_up = false;
				left_down = true;
			}
		}
		if (Bullet_y - 10 <= 5)
		{
			Bullet_y += 10;
			if (right_down == true)
			{
				right_down = false;
				right_up = true;
			}
			else if (left_down == true)
			{
				left_down = false;
				left_up = true;
			}
		}
		if (New_Map.No_Obstacles == false)
		{

			for (int o = 0; o < 10; o++)
			{
				if (Bullet_y + 10 >= New_Map.Map_Obstacles[o].y_coor - 5 && Bullet_y <= (New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height))
				{
					if (Bullet_x + 10 >= New_Map.Map_Obstacles[o].x_coor - 5 && Bullet_x <= New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width)
					{
						Bullet_x -= 10;
						if (right_up = true)
						{
							right_up = false;
							left_up = true;
						}
						else if (right_down == true)
						{
							right_down = false;
							left_down = true;
						}
					}
				}
				if (Bullet_y + 10 >= (New_Map.Map_Obstacles[o].y_coor - 5) && Bullet_y <= (New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height))
				{
					if (Bullet_x >= New_Map.Map_Obstacles[o].x_coor && Bullet_x - 9 <= New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width)
					{
						Bullet_x += 10;
						if (left_down == true)
						{
							left_down = false;
							right_down = true;
						}
						else if (left_up == true)
						{
							left_up = false;
							right_up = true;
						}
					}
				}
				if (Bullet_x + 15 >= New_Map.Map_Obstacles[o].x_coor - 5 && Bullet_x <= (New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width))
				{
					if (Bullet_y + 15 >= New_Map.Map_Obstacles[o].y_coor - 5 && Bullet_y <= New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height)
					{
						Bullet_y -= 10;
						if (right_up = true)
						{
							right_up = false;
							right_down = true;
						}
						else if (left_up == true)
						{
							left_up = false;
							left_down = true;
						}
					}
				}
				if (Bullet_x + 15 >= (New_Map.Map_Obstacles[o].x_coor - 5) && Bullet_x <= (New_Map.Map_Obstacles[o].x_coor + New_Map.Map_Obstacles[o].width))
				{
					if (Bullet_y >= New_Map.Map_Obstacles[o].y_coor && Bullet_y <= New_Map.Map_Obstacles[o].y_coor + New_Map.Map_Obstacles[o].height)
					{
						Bullet_y += 10;
						if (right_down == true)
						{
							right_down = false;
							right_up = true;
						}
						else if (left_down == true)
						{
							left_down = false;
							left_up = true;
						}
					}
				}
				
			}
		}
	}

	void SavetoFile()				//Saves the Player Progress inside the File
	{
		ofstream Write;
		Write.open("RESUMEGAMEAI.txt");
		Write << x_coord << "\n" << y_coord << "\n" << wins << "\n" << Game_Menu.level << "\n" << Top << "\n" << bottom << "\n" << left << "\n" << right;
		Write.close();
	}

	void ContinueLastSave()				//Retrieves the Data and sets the Game progress to previous
	{
		fstream Read;
		Read.open("RESUMEGAMEAI.txt");
		int temp1, temp2, temp3, temp4;
		bool temp5, temp6, temp7, temp8;
		Read >> temp1;
		Read >> temp2;
		Read >> temp3;
		Read >> temp4;
		Read >> temp5;
		Read >> temp6;
		Read >> temp7;
		Read >> temp8;
		Read.close();
		x_coord = temp1;
		y_coord = temp2;
		wins = temp3;
		Game_Menu.level = temp4;
		Top = temp5;
		bottom = temp6;
		left = temp7;
		right = temp8;
	}

	void WriteDummyData()					//Replace the Data with Dummy data incase of an game over or game won
	{
		int i = 0;
		ofstream Write;
		Write.open("RESUMEGAMEAI.txt");
		Write << i << "\n" << i << "\n" << i << "\n" << i << "\n" << Top << "\n" << i << "\n" << i << "\n" << i;
		Write.close();
	}
};
NPC AI;
