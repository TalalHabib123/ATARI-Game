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
#include "BULLET.h"
#include "Map.h"
#include "MENU.h"
#include "NPC.h"
#include "PowerUp.h"

using namespace std;

int StartingXP[10] = { 50,100,150,270,550,700,70,870,900,950 };
int StartingYP[10] = { 50,100,150,700,650,690,90,150,250,350 };

class Player1 :public Bullet {
public:
	string name;
	int x_coord = StartingXP[rand()%10];
	int y_coord = StartingYP[rand()%10];
	int score = 0;
	bool check_player = false;
	bool Died = false;
	bool NEW_GAME = false;
	int movement = 0;
	int Speed = 20;
	int ammo = 0;
	int wins=0;
	Player1() :Bullet{ x_coord,y_coord,false,false,false,true,false } {}

	void ResetBullet()
	{
		Bullet_x = x_coord;
		Bullet_y = y_coord;
	}

	void NEWGAME(int ID)				//Sets the Data for the Two Players
	{
		if (ID == 1)
		{
			check_player = true;
			x_coord = StartingXP[rand() % 10];
			y_coord = StartingYP[rand() % 10];
			Died = false;
			left = false;
			right = true;
			Top = false;
			bottom = false;
			i = 0;
			j = 0;
			Bullet_x = x_coord;
			Bullet_y = y_coord;
			NEW_GAME = true;

		}
		else if (ID == 2)
		{
			x_coord = StartingXP[rand() % 10];
			y_coord = StartingYP[rand() % 10];
			check_player = false;
			Died = false;
			left = true;
			right = false;
			Top = false;
			bottom = false;
			i = 0;
			j = 0;
			Bullet_x = x_coord;
			Bullet_y = y_coord;
			NEW_GAME = true;
		}
	}

	void DrawTank()
	{
		if (check_player == true)			//Draws the Tank as well as the UFO and the Rocket ship
		{
			if (Game_Menu.PLAYER1 == true)
			{
				if (Game_Menu.level == 1)
				{
					if (right == true)
					{
						DrawRectangle(x_coord + 1 + 2 + 2, y_coord, 15, 23, colors[RED]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord + 15, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord - 5, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 1 + 2 + 2, y_coord + 7, 25, 4, colors[RED]);
					}
					else if (left == true)
					{
						DrawRectangle(x_coord, y_coord, 15, 23, colors[RED]);
						DrawRectangle(x_coord - 5, y_coord + 15, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 5, y_coord - 5, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 10, y_coord + 7, 25, 4, colors[RED]);
					}
					else if (Top == true)
					{
						DrawRectangle(x_coord, y_coord + 5, 23, 15, colors[RED]);
						DrawRectangle(x_coord + 15, y_coord + 5 - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 5, y_coord + 5 - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 7, y_coord + 5, 4, 25, colors[RED]);
					}

					else if (bottom == true)
					{
						DrawRectangle(x_coord, y_coord, 23, 15, colors[RED]);
						DrawRectangle(x_coord + 15, y_coord - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 5, y_coord - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 7, y_coord - 10, 4, 25, colors[RED]);
					}
				}
				else if (Game_Menu.level == 2)
				{
					if (right == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2 + 3, y_coord + 5 + 3, 10, colors[RED]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord + 15, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord - 5, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 1 + 2 + 2, y_coord + 7, 25, 4, colors[RED]);
					}
					else if (left == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3, 10, colors[RED]);
						DrawRectangle(x_coord - 5, y_coord + 15, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 5, y_coord - 5, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 10, y_coord + 7, 25, 4, colors[RED]);
					}
					else if (Top == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3 + 2, 10, colors[RED]);
						DrawRectangle(x_coord + 15, y_coord + 5 - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 5, y_coord + 5 - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 7, y_coord + 5, 4, 25, colors[RED]);
					}

					else if (bottom == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3, 10, colors[RED]);
						DrawRectangle(x_coord + 15, y_coord - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 5, y_coord - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 7, y_coord - 10, 4, 25, colors[RED]);
					}
				}
				else if (Game_Menu.level == 3)
				{
					if (right == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2 + 3, y_coord + 5 + 3, 10, colors[RED]);
						DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord - 5, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 1 + 2 + 2, y_coord + 7, 25, 4, colors[RED]);
					}
					else if (left == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3, 10, colors[RED]);
						DrawRectangle(x_coord - 5, y_coord - 5, 25, 8, colors[ORANGE_RED]);
						DrawRectangle(x_coord - 10, y_coord + 7, 25, 4, colors[RED]);
					}
					else if (Top == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3 + 2, 10, colors[RED]);
						DrawRectangle(x_coord - 5, y_coord + 5 - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 7, y_coord + 5, 4, 25, colors[RED]);
					}

					else if (bottom == true)
					{
						DrawCircle(x_coord + 1 + 2 + 2 + 2 + 2, y_coord + 5 + 3, 10, colors[RED]);
						DrawRectangle(x_coord - 5, y_coord - 5, 8, 25, colors[ORANGE_RED]);
						DrawRectangle(x_coord + 7, y_coord - 10, 4, 25, colors[RED]);
					}
				}
			}
			if (Game_Menu.PLAYER2 == true)
			{
				if (right == true)
				{
					DrawRectangle(x_coord + 1 + 2 + 2, y_coord, 15, 23, colors[RED]);
					DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord + 15, 25, 8, colors[ORANGE_RED]);
					DrawRectangle(x_coord - 5 + 1 + 2 + 2, y_coord - 5, 25, 8, colors[ORANGE_RED]);
					DrawRectangle(x_coord + 1 + 2 + 2, y_coord + 7, 25, 4, colors[RED]);
				}
				else if (left == true)
				{
					DrawRectangle(x_coord, y_coord, 15, 23, colors[RED]);
					DrawRectangle(x_coord - 5, y_coord + 15, 25, 8, colors[ORANGE_RED]);
					DrawRectangle(x_coord - 5, y_coord - 5, 25, 8, colors[ORANGE_RED]);
					DrawRectangle(x_coord - 10, y_coord + 7, 25, 4, colors[RED]);
				}
				else if (Top == true)
				{
					DrawRectangle(x_coord, y_coord + 5, 23, 15, colors[RED]);
					DrawRectangle(x_coord + 15, y_coord + 5 - 5, 8, 25, colors[ORANGE_RED]);
					DrawRectangle(x_coord - 5, y_coord + 5 - 5, 8, 25, colors[ORANGE_RED]);
					DrawRectangle(x_coord + 7, y_coord + 5, 4, 25, colors[RED]);
				}

				else if (bottom == true)
				{
					DrawRectangle(x_coord, y_coord, 23, 15, colors[RED]);
					DrawRectangle(x_coord + 15, y_coord - 5, 8, 25, colors[ORANGE_RED]);
					DrawRectangle(x_coord - 5, y_coord - 5, 8, 25, colors[ORANGE_RED]);
					DrawRectangle(x_coord + 7, y_coord - 10, 4, 25, colors[RED]);
				}
			}
		}
		//DrawCircle(x_coord, y_coord, 16, colors[WHITE]);
		//DrawSquare(x_coord, y_coord, 20, colors[GREEN]);


		else if (check_player == false)
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
		}



		glutPostRedisplay();
	}

	void PathDetection()		//Obstacle detection of the Player Tank
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
						/*/right = false;
						left = true;
						Top = false;
						bottom = false;*/
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
						/*/Top = false;
						bottom = false;
						right = true;
						left = false;*/
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
						/*/Top = false;
						bottom = true;
						right = false;
						left = false;*/
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
						/*Top = true;
						bottom = false;
						right = false;
						left = false;*/
					}
				}
			}
		}
	}

	void BulletPath()				//Checks if the Bullet has Hit the Border or the Obstacle
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

	void SaveToFile()					//Saves the Player Progress inside the File
	{
		ofstream Write;
		Write.open("RESUMEGAMEPLAYER.txt");
		Write << x_coord << "\n" << y_coord << "\n" << wins << "\n" << Game_Menu.level << "\n" << Top << "\n" << bottom << "\n" << left << "\n" << right;
		Write << "\n" << score << "\n" <<PowerUp << "\n" <<PowerUpType << "\n" <<ammo;
		Write.close();
	}

	void DummyData()					//Replace the Data with Dummy data incase of an game over or game won
	{
		int i = 0;
		ofstream Write;
		Write.open("RESUMEGAMEPLAYER.txt");
		Write << i << "\n" << i << "\n" << i << "\n" << i << "\n" << i << "\n" << i << "\n" << i << "\n" << i;
		Write << "\n" << i << "\n" <<i << "\n" <<i << "\n" <<i;
		Write.close();
	}

	void ContinueGame()					//Retrieves the Data and sets the Game progress to previous
	{
		fstream Read;
		Read.open("RESUMEGAMEPLAYER.txt");
		int temp1, temp2, temp3, temp4,temp9,temp11,temp12;
		bool temp5, temp6, temp7, temp8,temp10;
		Read >> temp1;
		Read >> temp2;
		Read >> temp3;
		Read >> temp4;
		Read >> temp5;
		Read >> temp6;
		Read >> temp7;
		Read >> temp8;
		Read >> temp9;
		Read >> temp10;
		Read >> temp11;
		Read >> temp12;
		Read.close();
		x_coord = temp1;
		y_coord = temp2;
		wins = temp3;
		Game_Menu.level = temp4;
		Top = temp5;
		bottom = temp6;
		left = temp7;
		right = temp8;
		score = temp9;
		PowerUp = temp10;
		PowerUpType = temp11;
		ammo = temp12;
	}
};


Player1 New_Player1;
Player1 New_Player2;