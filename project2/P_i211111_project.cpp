//Name:Talal Habib
//Section:SE_P
//Roll No:21I-1111
//Department:Software Engineering


//============================================================================
// Name        : 21I-1111.cpp
// Author      : FAST SE Department
// Version     :Combat Atari game
// Copyright   : (c) Reserved
// Description : Basic 2D game...
//============================================================================

#ifndef COMBAT_CPP_
#define COMBAT_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include <time.h>
#include <fstream>
#include "Obstacle.h"
#include "BULLET.h"
#include "Map.h"
#include "MENU.h"
#include "NPC.h"
#include "Player.h"
#include "PowerUp.h"
#include <windows.h>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

bool flag = true;
int max_dis = 40;
int ID_NO = 0;
bool END_ROUND = true;


// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void WriteTOFile()									//Function to write the data of player for single player to file
{
	fstream READ;
	READ.open("SCORES.txt");
	string name1, name2, name3;
	string score1, score2, score3;
	getline(READ, name1);
	getline(READ, score1);
	getline(READ, name2);
	getline(READ, score2);						//getting the old scores from the file 
	getline(READ, name3);
	getline(READ, score3);
	cout << New_Player1.score;
	if (stoi(score1) <= New_Player1.score)
	{
		cout << "Ypor 1 work";
		name3 = name2;
		name2 = name1;
		name1 = New_Player1.name;
		score3 = score2;							//Checking if current score is equal or greter than top score 
		score2 = score1;
		score1 = to_string(New_Player1.score);
	}
	else if (stoi(score2) <= New_Player1.score)
	{
		cout << "Ypor 2 work";
		name3 = name2;
		name2 = New_Player1.name;
		score3 = score2;								//Checking if score is greater than that of second place and sorting it
		score2 = to_string(New_Player1.score);
	}
	else if (stoi(score3) <= New_Player1.score)
	{
		cout << "Ypor 3 work";
		name3 = New_Player1.name;
		score3 = to_string(New_Player1.score);					//Checking if score is greater than that of third place and sorting it
	}
	READ.close();
	ofstream Write;										//Writing the updated score to the Scores fille
	Write.open("SCORES.txt");
	Write << name1 << "\n" << score1 << "\n" << name2 << "\n" << score2 << "\n" << name3 << "\n" << score3;
	Write.close();
	
}
bool FlagNo = true;									//Used for the Movement of the AI Tank


bool CHECK_HELL = true;									//Used to Reset the Tanks after every death


void MoveBullet3(int m)                                //This Function is responsible for the movement of the Bullet
{
	if (AI.Died == false && CHECK_HELL == false && AI.bullet == true)    //Responsible for the direction for the bullet travel
	{
		if (AI.simple_path == true)
		{
			if (AI.i == 1)
			{
				AI.setY(10);
				AI.BulletPath();
				AI.j++;
			}
			else if (AI.i == 2)
			{
				AI.setY(-10);
				AI.BulletPath();
				AI.j++;
			}
			else if (AI.i == 3)				//Moving the bullet and checking for obstacles
			{
				AI.setX(-10);
				AI.BulletPath();
				AI.j++;
			}
			else if (AI.i == 4)
			{
				AI.setX(10);
				AI.BulletPath();
				AI.j++;
			}
		}
		
		else if (AI.Angled_path == true)
		{
			if (AI.right_up==true)
			{
				AI.setX(10);
				AI.setY(10);
				AI.AngledPath();
				AI.j++;
			}
			else if (AI.right_down==true)
			{
				AI.setX(10);
				AI.setY(-10);
				AI.AngledPath();									//Moving the Bullet on an ANgled path
				AI.j++;
			}
			else if (AI.left_up==true)
			{
				AI.setX(-10);
				AI.setY(10);
				AI.AngledPath();
				AI.j++;
			}
			else if (AI.left_down==true)
			{
				AI.setX(-10);
				AI.setY(-10);
				AI.AngledPath();
				AI.j++;
			}
		}

		if ((AI.GetX() >= New_Player1.x_coord - 10 && AI.GetX() <= New_Player1.x_coord + 10) && (AI.GetY() >= New_Player1.y_coord - 10 && AI.GetY() <= New_Player1.y_coord + 10))
		{
			Beep(700, 200);
			New_Player1.Died = true;
			AI.bullet = false;
			AI.i = 0;
			CHECK_HELL = true;
			FlagNo = true;
			New_Player1.bullet = false;                       //Checks if bullet has hit the enenmy player tank
			AI.wins++;
			AI.ResetObsDetection();
			if (AI.wins == 10)
			{
				Game_Menu.Player1End = true;
				Game_Menu.PLAYER1 = false;
				AI.WriteDummyData();
				New_Player1.DummyData();
			}

		}
		if ((AI.GetX() >= AI.x_coord - 10 && AI.GetX() <= AI.x_coord + 10) && (AI.GetY() >= AI.y_coord - 20 && AI.GetY() <= AI.y_coord + 15) && AI.j>=3)
		{
			Beep(700, 200);
			AI.Died = true;
			CHECK_HELL = true;
			New_Player1.i = 0;
			New_Player1.score += 10;
			New_Player1.bullet = false;
			AI.bullet = false;
			FlagNo = true;
			New_Player1.wins++;
			AI.ResetObsDetection();
			if (New_Player1.wins == 10)							//Checks if ai kills itself
			{
				Game_Menu.level++;
				New_Player1.wins = 0;
				AI.wins = 0;
				if (Game_Menu.level == 4)
				{
					Game_Menu.GamePlayerEnd = true;
					Game_Menu.PLAYER1 = false;
					AI.WriteDummyData();
					New_Player1.DummyData();
				}
			}
			//Game_Menu.KILLME = true;
		}
		if (!(AI.j == AI.max_dis) && !(AI.Died))
		{														//Conditon for the repaeting of the timer
			glutTimerFunc(20, MoveBullet3, 0);
		}
		if (AI.j == AI.max_dis)//|| New_Player1.Died)
		{
			AI.simple_path = false;
			AI.Angled_path = false;
			AI.bullet = false;
			FlagNo = true;										//This is run when max dis is traveled by bullet
			AI.i = 0;
			AI.j = 0;
		}
	}
}

bool x_path = false;           //For the Dodging Functionality of AI
bool y_path = false;			//For the Dodging Functionality of AI
int q = 3;						//For the Dodging Functionality of AI
int w = 0;						//For the Dodging Functionality of AI



void Timer(int m) {                     //This Timer Function is responsible for the Movement and shooting of the tank



	if (Game_Menu.PLAYER1 == true ) //this is the dodging function of ai tank
	{
		if (New_Player1.bullet == true)
		{

			if (New_Player1.GetX() == AI.x_coord || x_path == true)
			{
				x_path = true;
				AI.x_coord += 10;
				w++;
				if (AI.x_coord + 15 >= 1015)
				{
					AI.x_coord -= 10;
				}
				if (w == q)
				{															//Dodges the Bullet on the x_axis
					w = 0;
					x_path = false;
				}
			}

			if (New_Player1.GetY() == AI.y_coord || y_path == true)
			{
				y_path = true;
				AI.y_coord += 10;
				if (AI.y_coord + 15 >= 745)
				{
					AI.y_coord -= 10;
				}
				w++;
				if (w == q)													//Dodges the Bullet of the Player on y_axis 
				{
					w = 0;
					y_path = false;
				}
			}
		}
		if (AI.bullet == false)  //shooting of ai tank
		{
			if (AI.x_coord+10 <= New_Player1.x_coord - 100 && AI.bullet == false)
			{
				if (AI.y_coord < New_Player1.y_coord)
				{
					if (AI.y_coord == New_Player1.y_coord-100)
					{
						AI.right_up = true;
						AI.right_down = false;
						AI.left_down = false;													//Moving the Bullet on angled path
						AI.left_up = false;
						AI.bullet = true;
						AI.Angled_path = true;
						AI.simple_path = false;
						AI.ResetBullet();
						glutTimerFunc(20, MoveBullet3, 0);
					}
				}
				else if (AI.y_coord > New_Player1.y_coord)
				{
					if (AI.y_coord == 100 + New_Player1.y_coord)
					{
						AI.right_up = false;
						AI.right_down = true;
						AI.left_down = false;
						AI.left_up = false;
						AI.bullet = true;												//Moving the Bullet on angled path
						AI.Angled_path = true;
						AI.simple_path = false;
						AI.ResetBullet();
						glutTimerFunc(20, MoveBullet3, 0);
					}
				}
			}
			else if (AI.x_coord-10 >= New_Player1.x_coord + 100 && AI.bullet == false)
			{
				if (AI.y_coord < New_Player1.y_coord)
				{
					if (AI.y_coord == New_Player1.y_coord - 100)
					{
						AI.right_up = false;
						AI.right_down = false;
						AI.left_down = false;
						AI.left_up = true;
						AI.bullet = true;
						AI.Angled_path = true;										//Moving the Bullet on angled path
						AI.simple_path = false;
						AI.ResetBullet();
						glutTimerFunc(20, MoveBullet3, 0);
					}
				}
				else if (AI.y_coord > New_Player1.y_coord)
				{
					if (AI.y_coord == 100 + New_Player1.y_coord)
					{
						AI.right_up = false;
						AI.right_down = false;
						AI.left_down = true;
						AI.left_up = false;											//Moving the Bullet on angled path
						AI.bullet = true;
						AI.Angled_path = true;
						AI.simple_path = false;
						AI.ResetBullet();
						glutTimerFunc(20, MoveBullet3, 0);
					}
				}
			}
			else if (AI.x_coord == New_Player1.x_coord && AI.bullet == false)
			{
				if (AI.y_coord < New_Player1.y_coord)
				{
					if (New_Player1.y_coord - AI.y_coord < 200)
					{
						AI.Top = true;
						AI.bottom = false;
						AI.right = false;
						AI.left = false;			//shooting upwards
						FlagNo = false;
						AI.i = 1;
						AI.bullet = true;
						AI.simple_path = true;
						AI.ResetBullet();
						glutTimerFunc(20, MoveBullet3, 0);
					}
				}
				else if (AI.y_coord > New_Player1.y_coord)
				{
					if (AI.y_coord - New_Player1.y_coord < 200)
					{
						AI.Top = false;
						AI.bottom = true;
						AI.right = false;
						AI.left = false;						//Shooting downwards
						FlagNo = false;
						AI.i = 2;
						AI.bullet = true;
						AI.simple_path = true;
						AI.ResetBullet();
						glutTimerFunc(20, MoveBullet3, 0);
					}
				}
			}
			else if (AI.y_coord == New_Player1.y_coord && AI.bullet == false)
			{
				if (AI.x_coord < New_Player1.x_coord)
				{
					if (New_Player1.x_coord - AI.x_coord < 200)
					{
						AI.Top = false;
						AI.bottom = false;
						AI.right = true;
						AI.left = false;
						FlagNo = false;							//Shooting upwards 
						AI.i = 4;
						AI.bullet = true;
						AI.simple_path = true;
						AI.ResetBullet();
						glutTimerFunc(20, MoveBullet3, 0);
					}
				}
				else if (AI.x_coord > New_Player1.x_coord)
				{
					if (AI.x_coord - New_Player1.x_coord < 200)
					{
						AI.Top = false;
						AI.bottom = false;
						AI.right = false;
						AI.left = true;							//shooting downwards
						FlagNo = false;
						AI.i = 3;
						AI.bullet = true;
						AI.simple_path = true;
						AI.ResetBullet();
						glutTimerFunc(20, MoveBullet3, 0);
					}
				}
			}
		}
		if (AI.obstacles_Detected == true)    //This Whole condition is used to check and create a path around an obstacle
		{
			FlagNo = false;
			if (AI.Left_stop == true)
			{
				if (AI.up_go == true && AI.up_stop == false)
				{
					if (AI.left_path == false)
					{
						AI.y_coord += 10;
						AI.Top = true;
						AI.bottom = false;
						AI.right = false;
						AI.left = false;
					}
					if (AI.y_coord-15 > New_Map.Map_Obstacles[AI.left_obs].y_coor + New_Map.Map_Obstacles[AI.left_obs].height+5 && AI.left_path==false)
					{
						AI.left_path = true;
					}
					else if (AI.left_path == true)
					{
						AI.x_coord -= 10;
						AI.Top = false;
						AI.bottom = false;
						AI.right = false;
						AI.left = true;
						if (AI.x_coord+15 < New_Map.Map_Obstacles[AI.left_obs].x_coor-5)
						{
							AI.Left_stop = false;
							AI.left_path = false;
							AI.up_go = false;
							AI.left_obs = -1;
						}
					}
				}
				else if (AI.down_up == true && AI.down_stop == false)
				{
					if (AI.left_path == false)
					{
						AI.y_coord -= 10;
						AI.Top = false;
						AI.bottom = true;
						AI.right = false;
						AI.left = false;
					}
					if (AI.y_coord+15< New_Map.Map_Obstacles[AI.left_obs].y_coor-5 && AI.left_path == false)
					{
						AI.left_path = true;
					}
					else if (AI.left_path == true)
					{
						AI.x_coord -= 10;
						AI.bottom = false;
						AI.right = false;
						AI.left = true;
						if (AI.x_coord+15 < New_Map.Map_Obstacles[AI.left_obs].x_coor-5)
						{
							AI.Left_stop = false;
							AI.left_path = false;
							AI.down_up = false;
							AI.left_obs = -1;
						}
					}
				}
			}
			if (AI.right_stop == true)
			{
				if (AI.up_go == true && AI.up_stop == false)
				{
					if (AI.right_path == false)
					{
						AI.y_coord += 10;
						AI.Top = true;
						AI.bottom = false;
						AI.right = false;
						AI.left = false;
					}
					if (AI.y_coord-15 > New_Map.Map_Obstacles[AI.right_obs].y_coor + New_Map.Map_Obstacles[AI.right_obs].height+5 && AI.right_path == false)
					{
						AI.right_path = true;
					}
					else if (AI.right_path == true)
					{
						AI.x_coord += 10;
						AI.Top = false;
						AI.bottom = false;
						AI.right = true;
						AI.left = false;
						if (AI.x_coord-15 > New_Map.Map_Obstacles[AI.right_obs].x_coor + New_Map.Map_Obstacles[AI.right_obs].width+5)
						{
							AI.right_path = false;
							AI.right_stop = false;
							AI.up_go = false;
							AI.right_obs = -1;
						}
					}
				}
				else if (AI.down_up == true && AI.down_stop == false)
				{
					if (AI.right_path == false)
					{
						AI.y_coord -= 10;
						AI.Top = false;
						AI.bottom = true;
						AI.right = false;
						AI.left = false;
					}
					
					if (AI.y_coord+15 < New_Map.Map_Obstacles[AI.right_obs].y_coor-5 && AI.right_path == false)
					{
						AI.right_path = true;
					}
					else if (AI.right_path == true)
					{
						AI.x_coord += 10;
						AI.Top = false;
						AI.bottom = false;
						AI.right = true;
						AI.left = false;
						if (AI.x_coord-15 > New_Map.Map_Obstacles[AI.right_obs].x_coor + New_Map.Map_Obstacles[AI.right_obs].width+5)
						{
							AI.right_path = false;
							AI.right_stop = false;
							AI.down_up = false;
							AI.right_obs = -1;
						}
					}
				}
			}
			if (AI.up_stop == true)
			{
				if (AI.right_go == true && AI.right_stop == false)
				{
					if (AI.up_path == false)
					{
						AI.x_coord += 10;
						AI.Top = false;
						AI.bottom = false;
						AI.right = true;
						AI.left = false;
					}
					if (AI.x_coord - 15 > New_Map.Map_Obstacles[AI.up_obs].x_coor + New_Map.Map_Obstacles[AI.up_obs].width+5 && AI.up_path == false)
					{
						AI.up_path = true;
					}
					else if (AI.up_path == true)
					{
						AI.y_coord += 10;
						AI.Top = true;
						AI.bottom = false;
						AI.right = false;
						AI.left = false;
						if (AI.y_coord - 15 > New_Map.Map_Obstacles[AI.up_obs].y_coor + New_Map.Map_Obstacles[AI.up_obs].height+5)
						{
							AI.up_path = false;
							AI.up_stop = false;
							AI.right_go == false;
							AI.up_obs = -1;
						}
					}
					
				}
				else if (AI.left_go == true && AI.Left_stop == false)
				{
					if (AI.up_path == false)
					{
						AI.x_coord -= 10;
						AI.Top = false;
						AI.bottom = false;
						AI.right = false;
						AI.left = true;
					}
					if (AI.x_coord + 25 < New_Map.Map_Obstacles[AI.up_obs].x_coor-5 && AI.up_path == false)
					{
						AI.up_path = true;
					}
					else if (AI.up_path == true)
					{
						AI.y_coord += 10;
						AI.Top = true;
						AI.bottom = false;
						AI.right = false;
						AI.left = false;
						if (AI.y_coord - 15 > New_Map.Map_Obstacles[AI.up_obs].y_coor + New_Map.Map_Obstacles[AI.up_obs].height+5)
						{
							AI.up_path = false;
							AI.up_stop = false;
							AI.left_go == false;
							AI.up_obs = -1;
						}
					}
				}
			}
			if (AI.down_stop == true)
			{
				if (AI.right_go == true && AI.right_stop == false)
				{
					if (AI.down_path == false)
					{
						AI.x_coord += 10;
						AI.Top = false;
						AI.bottom = false;
						AI.right = true;
						AI.left = false;
					}
					if (AI.x_coord - 15 > New_Map.Map_Obstacles[AI.down_obs].x_coor + New_Map.Map_Obstacles[AI.down_obs].width+5 && AI.down_path == false)
					{
						AI.down_path = true;
					}
					else if (AI.down_path == true)
					{
						AI.y_coord -= 10;
						AI.Top = false;
						AI.bottom = true;
						AI.right = false;
						AI.left = false;
						if (AI.y_coord + 15 < New_Map.Map_Obstacles[AI.down_obs].y_coor-5)
						{
							AI.down_path = false;
							AI.down_stop = false;
							AI.right_go = false;
							AI.down_obs = -1;
						}
					}
				}
				else if (AI.left_go == true && AI.Left_stop == false)
				{
					if (AI.down_path == false)
					{
						AI.x_coord -= 10;
						AI.Top = false;
						AI.bottom = false;
						AI.right = false;
						AI.left = true;
					}
					if (AI.x_coord + 10 < New_Map.Map_Obstacles[AI.down_obs].x_coor  && AI.down_path == false)
					{
						AI.down_path = true;
					}				
					else if (AI.down_path == true)
					{
						AI.y_coord -= 10;
						AI.Top = false;
						AI.bottom = true;
						AI.right = false;
						AI.left = false;
						if (AI.y_coord + 15 < New_Map.Map_Obstacles[AI.down_obs].y_coor-5)
						{
							AI.down_path = false;
							AI.down_stop = false;
							AI.left_go = false;
							AI.down_obs = -1;
						}
					}
				}
			}
			AI.PathDetection();
			if (AI.Left_stop == false && AI.right_stop == false && AI.up_stop == false && AI.down_stop == false)
			{
				FlagNo = true;
				AI.obstacles_Detected = false;
			}
		}
		if (FlagNo == true && New_Player1.bullet == false)
		{
			if (AI.x_coord < New_Player1.x_coord)
			{
				AI.x_coord += 10;
				AI.Top = false;
				AI.bottom = false;
				AI.right = true;
				AI.left = false;
				AI.PathDetection();
				if (AI.x_coord + 15 >= 1015)						//moivng right
				{
					AI.x_coord -= 10;
				}
			}
			if (AI.x_coord > New_Player1.x_coord)
			{
				AI.x_coord -= 10;
				AI.Top = false;
				AI.bottom = false;
				AI.right = false;
				AI.left = true;										//moving left
				AI.PathDetection();
				if (AI.x_coord - 15 <= 5)
				{
					AI.x_coord += 10;
				}
			}
			if (AI.y_coord < New_Player1.y_coord)
			{
				AI.y_coord += 10;
				AI.Top = true;
				AI.bottom = false;
				AI.right = false;
				AI.left = false;									//moving up
				AI.PathDetection();
				if (AI.y_coord + 15 >= 745)
				{
					AI.y_coord -= 10;
				}
			}
			if (AI.y_coord > New_Player1.y_coord)
			{
				AI.y_coord -= 10;
				AI.Top = false;
				AI.bottom = true;
				AI.right = false;								//moving down
				AI.PathDetection();
				AI.left = false;
				if (AI.y_coord - 15 <= 5)
				{
					AI.y_coord += 10;
				}
			}
		}
		if (AI.Died == false && New_Player1.Died == false)
		{
			glutTimerFunc(AI.speed_Tank, Timer, 0);				//Timer Function
		}
		
	}
}


void moveBullet1(int m)												//Timer function to move the bullet for player 1
{
	if (CHECK_HELL == false && New_Player1.Died==false && New_Player1.bullet==true)
	{
		if (AI.Died == false)
		{
			if (New_Player1.i == 1)
			{
				New_Player1.setY(10);
				New_Player1.BulletPath();
				New_Player1.j++;
			}
			else if (New_Player1.i == 2)
			{
				New_Player1.setY(-10);
				New_Player1.BulletPath();
				New_Player1.j++;
			}													//Moving the bullet 
			else if (New_Player1.i == 3)
			{
				New_Player1.setX(-10);
				New_Player1.BulletPath();
				New_Player1.j++;
			}
			else if (New_Player1.i == 4)
			{
				New_Player1.setX(10);
				New_Player1.BulletPath();
				New_Player1.j++;
			}
			if ((New_Player1.GetX() >= AI.x_coord - 10 && New_Player1.GetX() <= AI.x_coord + 10) && (New_Player1.GetY() >= AI.y_coord - 20 && New_Player1.GetY() <= AI.y_coord + 15))
			{
				Beep(700, 200);
				AI.Died = true;
				CHECK_HELL = true;
				New_Player1.i = 0;
				New_Player1.score += 10;
				New_Player1.bullet = false;
				AI.bullet = false;
				FlagNo = true;
				New_Player1.wins++;
				AI.ResetObsDetection();
																	//Checks if Player 1 has killed the Bot
				if (New_Player1.wins == 10)
				{
					Game_Menu.level++;
					New_Player1.wins = 0;
					AI.wins = 0;
					if (Game_Menu.level == 4)
					{
						Game_Menu.GamePlayerEnd = true;
						Game_Menu.PLAYER1 = false;
						AI.WriteDummyData();
						New_Player1.DummyData();
					}
				}
				//Game_Menu.KILLME = true;
			}
			if ((New_Player1.GetX() >= New_Player1.x_coord - 10 && New_Player1.GetX() <= New_Player1.x_coord + 10) && (New_Player1.GetY() >= New_Player1.y_coord - 10 && New_Player1.GetY() <= New_Player1.y_coord + 15) && New_Player1.j >= 2)
			{
				Beep(700, 200);
				New_Player1.Died = true;
				AI.bullet = false;
				AI.i = 0;
				CHECK_HELL = true;
				FlagNo = true;
				New_Player1.bullet = false;
				AI.wins++;												//This is checking if the player has killed himself 
				AI.ResetObsDetection();
				if (AI.wins == 10)
				{
					Game_Menu.Player1End = true;
					Game_Menu.PLAYER1 = false;
					AI.WriteDummyData();
					New_Player1.DummyData();
				}
			}
			if (!(New_Player1.j == New_Player1.max_dis) && !(New_Player1.Died))
			{
				glutTimerFunc(New_Player1.Speed, moveBullet1, 0);					//Timer only works if max dis is not reached 
			}
			if (New_Player1.j >= New_Player1.max_dis)
			{
				New_Player1.bullet = false;
				New_Player1.i = 0;
				New_Player1.j = 0;
			}

		}

		if (New_Player2.Died == false)
		{
			if (New_Player1.i == 1)
			{
				New_Player1.setY(10);
				New_Player1.BulletPath();
				New_Player1.j++;
			}
			else if (New_Player1.i == 2)
			{
				New_Player1.setY(-10);
				New_Player1.BulletPath();
				New_Player1.j++;
			}
			else if (New_Player1.i == 3)
			{
				New_Player1.setX(-10);
				New_Player1.BulletPath();
				New_Player1.j++;
			}
			else if (New_Player1.i == 4)
			{
				New_Player1.setX(10);
				New_Player1.BulletPath();
				New_Player1.j++;
			}
			if ((New_Player1.GetX() >= New_Player2.x_coord - 10 && New_Player1.GetX() <= New_Player2.x_coord + 10) && (New_Player1.GetY() >= New_Player2.y_coord - 10 && New_Player1.GetY() <= New_Player2.y_coord + 15))
			{
				Beep(700, 200);
				New_Player2.Died = true;
				New_Player1.score += 10;
				CHECK_HELL = true;
				New_Player1.bullet = false;
				New_Player2.bullet = false;
				New_Player1.i = 0;
				END_ROUND = true;
				if (New_Player1.score == 100)					//Checks if Player 1 has killed player 2
				{
					Game_Menu.PLAYER2 = false;
					Game_Menu.GAMEEND = true;
				}
			}
			if ((New_Player1.GetX() >= New_Player1.x_coord - 10 && New_Player1.GetX() <= New_Player1.x_coord + 10) && (New_Player1.GetY() >= New_Player1.y_coord - 10 && New_Player1.GetY() <= New_Player1.y_coord + 15) && New_Player1.j >= 2)
			{
				Beep(700, 200);
				New_Player1.Died = true;
				New_Player2.score += 10;
				CHECK_HELL = true;								//Checks player 1 has killed himself 
				New_Player1.i = 0;
				New_Player2.bullet = false;
				New_Player1.bullet = false;								
				END_ROUND = true;
				if (New_Player2.score == 100)
				{
					Game_Menu.PLAYER2 = false;
					Game_Menu.GAMEEND = true;
				}
			}
			if (!(New_Player1.j == New_Player1.max_dis) && !(New_Player1.Died))
			{
				glutTimerFunc(New_Player1.Speed, moveBullet1, 0);					//Timer function for the bullet
			}
			if (New_Player1.j == New_Player1.max_dis)
			{
				New_Player1.bullet = false;
				New_Player1.i = 0;								//Stops the Tier of the Bullet
				New_Player1.j = 0;
			}
		}
	}
}

void moveBullet2(int m)												//timer function for player 2
{
	if (CHECK_HELL == false)
	{
		if (New_Player2.i == 1)
		{
			New_Player2.setY(10);
			New_Player2.BulletPath();
			New_Player2.j++;
		}
		else if (New_Player2.i == 2)
		{
			New_Player2.setY(-10);
			New_Player2.BulletPath();
			New_Player2.j++;
		}														//Moves the bullet in one of the x y -y -x axis
		else if (New_Player2.i == 3)
		{
			New_Player2.setX(-10);
			New_Player2.BulletPath();
			New_Player2.j++;
		}
		else if (New_Player2.i == 4)
		{
			New_Player2.setX(10);
			New_Player2.BulletPath();
			New_Player2.j++;
		}
		if ((New_Player2.GetX() >= New_Player1.x_coord - 10 && New_Player2.GetX() <= New_Player1.x_coord + 10) && (New_Player2.GetY() >= New_Player1.y_coord - 10 && New_Player2.GetY() <= New_Player1.y_coord + 15))
		{
			Beep(700, 200);
			New_Player1.Died = true;
			CHECK_HELL = true;
			New_Player2.i = 0;
			New_Player2.score += 10;
			New_Player2.bullet = false;
			New_Player1.bullet = false;
			END_ROUND = true;								//Checks if player2 has killed the playeer 1
			if (New_Player2.score == 100)
			{
				Game_Menu.PLAYER2 = false;
				Game_Menu.GAMEEND = true;
			}
		}
		if ((New_Player2.GetX() >= New_Player2.x_coord - 10 && New_Player2.GetX() <= New_Player2.x_coord + 10) && (New_Player2.GetY() >= New_Player2.y_coord - 10 && New_Player2.GetY() <= New_Player2.y_coord + 15) && New_Player2.j >= 2)
		{
			Beep(700, 200);
			New_Player2.Died = true;
			CHECK_HELL = true;
			New_Player2.i = 0;
			New_Player1.score += 10;
			New_Player2.bullet = false;
			New_Player1.bullet = false;
			END_ROUND = true;
			if (New_Player1.score == 100)					//Checks if Player 2 has killed himself or not
			{
				Game_Menu.PLAYER2 = false;
				Game_Menu.GAMEEND = true;
			}
		}
		if (!(New_Player2.j == New_Player2.max_dis) && !(New_Player2.Died))
		{
			glutTimerFunc(New_Player2.Speed, moveBullet2, 0);				//Timer funstion called for the Movement of bullet
		}	
		if (New_Player2.j == New_Player2.max_dis)
		{																//Stops the timer Funtion of tghe Bullet
			New_Player2.bullet = false;
			New_Player2.i = 0;
			New_Player2.j = 0;
		}
	}
}

/*
 * Main Canvas drawing function.
 * */





void PATH()
{
	if (AI.Died == false && Game_Menu.PLAYER1 == true )
	{
		glutTimerFunc(100, Timer, 0);
	}
}

void GameDisplay()/**/ {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	int y = rand() % 3;
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors

	if (Game_Menu.RESUME == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		DrawString(400, 550, "F1-Resume Game", colors[BLUE_VIOLET]);
		DrawString(400, 450, "F2-Main Menu", colors[BLUE_VIOLET]);						//this is showing the resume menu
		DrawString(400, 350, "F4-Exit Game", colors[BLUE_VIOLET]);
	}

	if (Game_Menu.MENU == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		DrawString(400,600, "Combat Atari Game", colors[CADET_BLUE]);
		DrawString(380, 550, "By Talal Habib 21I-1111", colors[CADET_BLUE]);
		DrawString(100, 100, "Press the correspondent button on keyboard to access different functions of game", colors[WHITE]);
		DrawString(400, 500, "F1-1 Player", colors[BLUE_VIOLET]);						//this is showing the menu
		DrawString(400, 450, "F2-2 Players", colors[BLUE_VIOLET]);
		DrawString(400, 400, "F3-LeaderBoard", colors[BLUE_VIOLET]);
		DrawString(400, 350, "F4-How To Play", colors[BLUE_VIOLET]);
		DrawString(400, 300, "F5-Exit Game", colors[BLUE_VIOLET]);
	}

	else if (Game_Menu.Player1Name == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		DrawString(400, 500, "Enter Player 1 Name:", colors[WHITE]);
		DrawRectangle(300, 430, 400, 50, colors[WHITE]);
		DrawString(400, 450, New_Player1.name, colors[BLACK]);
		DrawString(400, 300, "Press F1 to Continue", colors[BLUE_VIOLET]);
	}
	else if (Game_Menu.Player2Name == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		DrawString(400, 500, "Enter Player 2 Name:", colors[WHITE]);
		DrawRectangle(300, 430, 400, 50, colors[WHITE]);
		DrawString(400, 450, New_Player2.name, colors[BLACK]);
		DrawString(400, 300, "Press F1 to Continue", colors[BLUE_VIOLET]);
	}

	else if (Game_Menu.DUMMY == true)
	{
		New_Map.MapLoad2();
		//DrawCircle(870, 350, 10, colors[WHITE]);								//this is for me so leave it
	}

	else if (Game_Menu.GAMEEND == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		if (New_Player1.score == 100)
		{
			DrawString(450, 550, New_Player1.name + " HAS WON", colors[BLUE_VIOLET]);
		}																								//game end display for 2 player
		else if (New_Player2.score == 100)
		{
			DrawString(400, 550, New_Player2.name + " HAS WON", colors[BLUE_VIOLET]);
		}
		DrawString(300, 450, "Press F2 for a Rematch", colors[BLUE_VIOLET]);
		DrawString(300, 350, "Press F1 to Go Back To Menu", colors[BLUE_VIOLET]);
	}
	else if (Game_Menu.Player1End == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		DrawString(400, 450, "You Lose", colors[BLUE_VIOLET]);
		AI.WriteDummyData();
		New_Player1.DummyData();
		DrawString(300, 350, "Press F1 to Go Back To Menu", colors[BLUE_VIOLET]);						//game end display for 1 player
	}
	else if (Game_Menu.GamePlayerEnd == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		DrawString(400, 450, "You Win", colors[BLUE_VIOLET]);
		AI.WriteDummyData();
		New_Player1.DummyData();
		DrawString(300, 350, "Press F1 to Go Back To Menu", colors[BLUE_VIOLET]);					//game end display for 1 player
	}

	else if (Game_Menu.HOW == true)
	{
		DrawRectangle(200, 30, 600, 750, colors[ORANGE]);
		DrawString(300, 750, "For Player 1", colors[BLUE_VIOLET]);
		DrawString(300, 700, "Press Up Key to Move Upwards", colors[BLUE_VIOLET]);
		DrawString(300, 650, "Press Down Key to Move Downwards", colors[BLUE_VIOLET]);
		DrawString(300, 600, "Press Right Key to Move Right", colors[BLUE_VIOLET]);
		DrawString(300, 550, "Press Left Key to Move Left", colors[BLUE_VIOLET]);
		DrawString(300, 500, "Press Left Shift to Shoot", colors[BLUE_VIOLET]);
																									//how to play menu
		DrawString(300, 400, "For Player 2", colors[BLUE_VIOLET]);
		DrawString(300, 350, "Press W Key to Move Upwards", colors[BLUE_VIOLET]);
		DrawString(300, 300, "Press S Key to Move Downwards", colors[BLUE_VIOLET]);
		DrawString(300, 250, "Press D Key to Move Right", colors[BLUE_VIOLET]);
		DrawString(300, 200, "Press A Key to Move Left", colors[BLUE_VIOLET]);
		DrawString(300, 150, "Press R key to Shoot", colors[BLUE_VIOLET]);

		DrawString(300, 50, "Press F1 to Go Back To Menu", colors[BLUE_VIOLET]);
	}

	else if (Game_Menu.SelectLevel == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		DrawString(300, 550, "F1 -> Level 1 -------------->Easy", colors[BLUE_VIOLET]);								//selected level menu
		DrawString(300, 450, "F2 -> Level 2 -------------->Medium", colors[BLUE_VIOLET]);
		DrawString(300, 350, "F3 -> Level 3 -------------->Hard", colors[BLUE_VIOLET]);
	}

	else if (Game_Menu.SUBMenu == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		DrawString(400, 550, "F1 -> New Game", colors[BLUE_VIOLET]);
		DrawString(400, 450, "F2 -> Select Level", colors[BLUE_VIOLET]);						//select option for single playre
		DrawString(400, 350, "F3 -> Continue game", colors[BLUE_VIOLET]);
	}

	else if (Game_Menu.PLAYER1 == true)
	{
		DrawString(50, 800, to_string(New_Player1.wins), colors[MISTY_ROSE]);
		DrawString(500, 800, "Level\t\t\t"+to_string(Game_Menu.level), colors[MISTY_ROSE]);
		DrawString(900, 800, to_string(AI.wins), colors[MISTY_ROSE]);
		if (CHECK_HELL == true)
		{
			AI.Died = false;
			New_Player1.Died = false;
			AI.NEWGAME();
			New_Player1.NEWGAME(1);
			CHECK_HELL = false;
		}																								//Actual single player game
		else if (Game_Menu.KILLME == true)
		{
			Game_Menu.KILLME = false;
			PATH();
		}
		//
		if (Game_Menu.level == 1)
		{
			New_Map.MapLoad1();
		}
		else if (Game_Menu.level == 2)
		{
			New_Map.MapLoad2();
		}
		else if (Game_Menu.level == 3)
		{
			New_Map.MapLoad3();
		}
		New_Player2.Died = true;
		//AI.Died = true;
		if (First_PowerUp.Display == true)
		{
			First_PowerUp.DRAWPOWERUP();
		}
		if (Second_PowerUp.Display == true)
		{
			Second_PowerUp.DRAWPOWERUP();
		}
		if (AI.Died == false)
		{
			AI.DrawTank();
		}
		if (New_Player1.Died == false)
		{
			New_Player1.DrawTank();
		}
		if (New_Player1.PowerUp == true)
		{
			if (New_Player1.PowerUpType == 1)
			{
				DrawCircle(50, 770, 15, colors[MAGENTA]);
			}
			else if (New_Player1.PowerUpType == 2)
			{
				DrawCircle(50, 770, 15, colors[BLUE]);
			}
		}
		if (New_Player1.bullet == true && New_Player1.Died == false && (New_Player2.Died == false || AI.Died == false))
		{
			DrawCircle(New_Player1.GetX() + 8, New_Player1.GetY() + 8, 5, colors[GREEN]);
		}
		if (AI.bullet == true && AI.Died == false && New_Player1.Died == false)
		{
			DrawCircle(AI.GetX() + 3, AI.GetY() + 7, 5, colors[RED]);
		}
	}
	else if (Game_Menu.LEADER == true)
	{
		DrawRectangle(200, 200, 600, 500, colors[ORANGE]);
		fstream READ;
		READ.open("SCORES.txt");
		string name1, name2, name3;
		string score1, score2, score3;
		getline(READ, name1);
		getline(READ, score1);
		getline(READ, name2);															//leaderboard display
		getline(READ, score2);
		getline(READ, name3);
		getline(READ, score3);
		DrawString(380, 600, "LEADERBOARD", colors[BLACK]);
		DrawString(380, 500, "1." + name1 + "\t\t\t\t\t\t" + score1, colors[BLACK]);
		DrawString(380, 450, "2." + name2 + "\t\t\t\t\t\t" + score2, colors[BLACK]);
		DrawString(380, 400, "3." + name3 + "\t\t\t\t\t\t" + score3, colors[BLACK]);
		DrawString(300, 300, "Press F1 to Go Back To Menu", colors[BLACK]);
		READ.close();
	}
	else if (Game_Menu.PLAYER2 == true)
	{
		if (CHECK_HELL == true)
		{
			New_Player1.NEWGAME(1);
			New_Player2.NEWGAME(2);
			CHECK_HELL = false;

		}
		//END_ROUND = false;
		//New_Map.MapLoad2();
		if (END_ROUND == true)															//aCTUAL TWO PLAYER GAME
		{
			for (int i = 0; i < 3; i++)
			{
				New_Map.Map_Load[i] = false;
			}
			New_Map.Map_Load[y] = true;
			END_ROUND = false;

		}
		if (New_Map.Map_Load[0] == true)
		{
			New_Map.MapLoad1();
		}
		if (New_Map.Map_Load[1] == true)
		{
			New_Map.MapLoad2();
		}
		if (New_Map.Map_Load[2] == true)
		{
			New_Map.MapLoad3();
		}
		//DrawSquare(New_Map.Map_Obstacles[1].x_coor, New_Map.Map_Obstacles[1].y_coor, 10, colors[RED]);

		DrawString(50, 800, to_string(New_Player1.score), colors[MISTY_ROSE]);
		DrawString(100, 800, New_Player1.name, colors[WHITE]);
		DrawString(900, 800, to_string(New_Player2.score), colors[MISTY_ROSE]);
		DrawString(800, 800, New_Player2.name, colors[WHITE]);
		//New_Player2.Died = true;
		AI.Died = true;
		if (First_PowerUp.Display == true)
		{
			First_PowerUp.DRAWPOWERUP();
		}
		if (Second_PowerUp.Display == true)
		{
			Second_PowerUp.DRAWPOWERUP();
		}
		if (New_Player1.PowerUp == true)
		{
			if (New_Player1.PowerUpType == 1)
			{
				DrawCircle(50, 770, 15, colors[MAGENTA]);
			}
			else if (New_Player1.PowerUpType == 2)
			{
				DrawCircle(50, 770, 15, colors[BLUE]);
			}
		}
		if (New_Player2.PowerUp == true)
		{
			if (New_Player2.PowerUpType == 1)
			{
				DrawCircle(900, 770, 15, colors[MAGENTA]);
			}
			else if (New_Player2.PowerUpType == 2)
			{
				DrawCircle(900, 770, 15, colors[BLUE]);
			}
		}
		if (New_Player1.Died == false)
		{
			New_Player1.DrawTank();
		}
		if (New_Player2.Died == false)
		{
			New_Player2.DrawTank();
		}

		if (New_Player1.bullet == true && New_Player1.Died == false && (New_Player2.Died == false || AI.Died == false))
		{
			DrawCircle(New_Player1.GetX() + 8, New_Player1.GetY() + 8, 5, colors[GREEN]);				//shows bullet
		}
		if (New_Player2.bullet == true && New_Player2.Died == false && New_Player1.Died == false)
		{
			DrawCircle(New_Player2.GetX() + 8, New_Player2.GetY() + 8, 5, colors[BLUE]);				//shows bullet
		}


	}


	glutSwapBuffers(); // do not modify this line..
}


void CHECKFORPOWERUP1()				//Checking for powerups for player 1
{

	if (New_Player1.movement == 40 && First_PowerUp.Display == false && Second_PowerUp.Display == false && New_Player1.PowerUp == false)    //Randomnly spanws the powerup
	{
		int l = rand() % 2;
		if (l == 0)
		{
			First_PowerUp.Display = true;
		}
		else if (l == 1)
		{
			Second_PowerUp.Display = true;
		}
		New_Player1.movement = 0;
		New_Player2.movement = 0;
	}
	if (First_PowerUp.Display == true)						//Checks if Player 1 has picked up the power 1
	{
		if (New_Player1.x_coord >= First_PowerUp.x_coord - 10 && New_Player1.x_coord <= First_PowerUp.x_coord + 10)
		{
			if (New_Player1.y_coord >= First_PowerUp.y_coord - 10 && New_Player1.y_coord <= First_PowerUp.y_coord + 10)
			{
				New_Player1.Speed = First_PowerUp.speed;
				New_Player1.max_dis = First_PowerUp.Distance;
				New_Player1.PowerUp = true;
				New_Player1.PowerUpType = First_PowerUp.Type;
				First_PowerUp.Display = false;
			}
		}
	}
	if (Second_PowerUp.Display == true)						//Checks if Player 1 has picked up the power 2
	{
		if (New_Player1.x_coord >= Second_PowerUp.x_coord - 10 && New_Player1.x_coord <= Second_PowerUp.x_coord + 10)
		{
			if (New_Player1.y_coord >= Second_PowerUp.y_coord - 10 && New_Player1.y_coord <= Second_PowerUp.y_coord + 10)
			{
				New_Player1.Speed = Second_PowerUp.speed;
				New_Player1.max_dis = Second_PowerUp.Distance;
				New_Player1.PowerUp = true;
				New_Player1.PowerUpType = Second_PowerUp.Type;
				Second_PowerUp.Display = false;
			}
		}
	}
	glutPostRedisplay();
}

void CHECKPOWERUP2()					//chcek for power ups for player 2
{
	if (New_Player2.movement == 40 && First_PowerUp.Display == false && Second_PowerUp.Display == false && New_Player2.PowerUp == false)   //Spawns the Powerup on the map
	{
		int l = rand() % 2;
		if (l == 0)
		{
			First_PowerUp.Display = true;
		}
		else if (l == 1)
		{
			Second_PowerUp.Display = true;
		}
		New_Player1.movement = 0;
		New_Player2.movement = 0;
	}
	if (First_PowerUp.Display == true)					//Checks if Player2 has picked up the powerup 1
	{
		if (New_Player2.x_coord >= First_PowerUp.x_coord - 10 && New_Player2.x_coord <= First_PowerUp.x_coord + 10)
		{
			if (New_Player2.y_coord >= First_PowerUp.y_coord - 10 && New_Player2.y_coord <= First_PowerUp.y_coord + 10)
			{
				New_Player2.Speed = First_PowerUp.speed;
				New_Player2.max_dis = First_PowerUp.Distance;
				New_Player2.PowerUp = true;
				New_Player2.PowerUpType = First_PowerUp.Type;
				First_PowerUp.Display = false;
				First_PowerUp.RESET();
			}
		}
	}
	if (Second_PowerUp.Display == true)							//Checks if Player2 has picked up the powerup 2
	{
		if (New_Player2.x_coord >= Second_PowerUp.x_coord - 10 && New_Player2.x_coord <= Second_PowerUp.x_coord + 10)
		{
			if (New_Player2.y_coord >= Second_PowerUp.y_coord - 10 && New_Player2.y_coord <= Second_PowerUp.y_coord + 10)
			{
				New_Player2.Speed = Second_PowerUp.speed;
				New_Player2.max_dis = Second_PowerUp.Distance;
				New_Player2.PowerUp = true;
				New_Player2.PowerUpType = Second_PowerUp.Type;
				Second_PowerUp.Display = false;
				Second_PowerUp.RESET();
			}
		}
	}
	glutPostRedisplay();
}

void NonPrintableKeys(int key, int x, int y) {          //this simply contains the makeshift menu options and theri funtions
	if (Game_Menu.RESUME == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.RESUME = false;
			if (Game_Menu.Type == 1)
			{
				Game_Menu.PLAYER1 = true;
			}
			else if (Game_Menu.Type == 2)
			{
				Game_Menu.PLAYER2 = true;
			}
			Game_Menu.KILLME = true;
			glutPostRedisplay();
		}
		if (key == GLUT_KEY_F2)
		{
			Game_Menu.MENU = true;
			Game_Menu.RESUME = false;
			if (Game_Menu.Type == 1)
			{
				AI.SavetoFile();
				New_Player1.SaveToFile();
			}
			Game_Menu.PLAYER1 = false;
			Game_Menu.PLAYER2 = false;
			glutPostRedisplay();
		}
		if (key == GLUT_KEY_F4)
		{
			if (Game_Menu.Type == 1)
			{
				WriteTOFile();
				AI.SavetoFile();
				New_Player1.SaveToFile();
			}
			exit(1);
		}
	}
	else if (Game_Menu.Player1Name == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.Player1Name = false;
			Game_Menu.Player2Name = true;
			glutPostRedisplay();
		}
	}
	else if (Game_Menu.Player2Name == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.MENU = true;
			Game_Menu.Player2Name = false;
			glutPostRedisplay();
		}
	}
	else if (Game_Menu.GamePlayerEnd == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.GamePlayerEnd = false;
			AI.wins = 0;
			New_Player1.wins = 0;
			WriteTOFile();
			New_Player1.score = 0;
			Game_Menu.level = 1;
			Game_Menu.MENU = true;
			glutPostRedisplay();
		}
	}
	else if (Game_Menu.Player1End == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.Player1End = false;
			AI.wins = 0;
			New_Player1.wins = 0;
			WriteTOFile();
			Game_Menu.level = 1;
			Game_Menu.MENU = true;
			glutPostRedisplay();
		}
	}
	else if (Game_Menu.LEADER == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.LEADER = false;					//Opens the Learder Board
			Game_Menu.MENU = true;
			glutPostRedisplay();
		}
	}
	else if (Game_Menu.GAMEEND == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.GAMEEND = false;
			Game_Menu.MENU = true;						//Ends the Game
			New_Player1.score = 0;
			New_Player2.score = 0;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F2)
		{
			Game_Menu.MENU = false;
			Game_Menu.PLAYER2 = true;
			Game_Menu.Type = 2;
			Game_Menu.PLAYER1 = false;
			New_Player1.score = 0;
			New_Player2.score = 0;
			Game_Menu.GAMEEND = false;
			Game_Menu.KILLME = false;
			CHECK_HELL = true;
			New_Player1.NEWGAME(1);
			New_Player2.NEWGAME(2);
			glutPostRedisplay();
		}
	}

	else if (Game_Menu.SUBMenu == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.PLAYER1= true;
			New_Player1.NEWGAME(1);
			AI.NEWGAME();
			AI.wins = 0;
			New_Player1.wins = 0;							//Starts the new game 
			Game_Menu.level = 1;
			Game_Menu.SUBMenu= false;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F2)
		{
			New_Player1.NEWGAME(1);
			AI.NEWGAME();
			AI.wins = 0;									//Opens the User level selection part of the game	
			New_Player1.wins = 0;
			Game_Menu.SelectLevel = true;
			Game_Menu.SUBMenu = false;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F3)
		{
			AI.ContinueLastSave();
			New_Player1.ContinueGame();
			if (AI.x_coord == 0 && New_Player1.x_coord==0)
			{
				New_Player1.NEWGAME(1);
				AI.NEWGAME();
				Game_Menu.level = 1;
				AI.wins = 0;						//if the data does not exist then loads the new games features
				New_Player1.wins = 0;
				CHECK_HELL = true;
			}
			else
			{
				AI.Died = false;
				New_Player1.Died = false;
				New_Player1.Speed = 20;
				CHECK_HELL = false;					//Loads the Previos save data of player vs bot
				New_Player1.check_player = true;
			}
			Game_Menu.PLAYER1 = true;
			Game_Menu.SUBMenu = false;
			glutPostRedisplay();
		}
		
	}

	else if (Game_Menu.SelectLevel == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.PLAYER1 = true;
			Game_Menu.level = 1;
			Game_Menu.SelectLevel = false;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F2)
		{
			Game_Menu.SelectLevel = false;
			Game_Menu.level = 2;
			Game_Menu.PLAYER1 = true;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F3)
		{
			Game_Menu.SelectLevel = false;
			Game_Menu.level = 3;
			Game_Menu.PLAYER1 = true;
			glutPostRedisplay();
		}
	}

	else if (Game_Menu.HOW == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.HOW = false;
			Game_Menu.MENU = true;
			glutPostRedisplay();
		}
	}

	else if (Game_Menu.MENU == true)
	{
		if (key == GLUT_KEY_F1)
		{
			Game_Menu.MENU = false;
			Game_Menu.PLAYER1 = false;
			Game_Menu.SUBMenu = true;
			Game_Menu.PLAYER2 = false;
			Game_Menu.Type = 1;
			CHECK_HELL = true;
			Game_Menu.KILLME = true;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F2)
		{
			Game_Menu.MENU = false;
			Game_Menu.PLAYER2 = true;
			Game_Menu.Type = 2;
			Game_Menu.PLAYER1 = false;
			New_Player1.score = 0;
			New_Player2.score = 0;
			Game_Menu.KILLME = false;
			CHECK_HELL = true;

			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F3)
		{
			Game_Menu.MENU = false;
			Game_Menu.LEADER = true;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F4)
		{
			Game_Menu.MENU = false;
			Game_Menu.HOW = true;
			glutPostRedisplay();
		}
		else if (key == GLUT_KEY_F5)
		{
			exit(1);
		}
	}

	if (!New_Player1.Died && Game_Menu.PLAYER1 == true || Game_Menu.PLAYER2 == true)          //This is Taking inputs for moving player 1 tank
	{

		if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
			// what to do when left key is pressed...
			//xI -= 10;
			New_Player1.x_coord -= 10;
			New_Player1.bottom = false;
			New_Player1.Top = false;
			New_Player1.right = false;
			New_Player1.left = true;
			if (New_Player1.PowerUp == false)
			{
				New_Player1.movement++;
				CHECKFORPOWERUP1();
			}
			if (New_Map.No_Obstacles == false)
			{
				New_Player1.PathDetection();
			}

			if (New_Player1.x_coord - 10 <= 5)
			{
				New_Player1.x_coord += 10;
				/*New_Player1.bottom = false;
				New_Player1.Top = false;
				New_Player1.right = true;
				New_Player1.left = false;*/
			}
			return;
		}
		else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
			//xI += 10;
			New_Player1.x_coord += 10;
			New_Player1.bottom = false;
			New_Player1.Top = false;
			New_Player1.right = true;
			New_Player1.left = false;
			if (New_Player1.PowerUp == false)
			{
				New_Player1.movement++;
				CHECKFORPOWERUP1();
			}
			if (New_Map.No_Obstacles == false)
			{
				New_Player1.PathDetection();
			}

			if (New_Player1.x_coord + 10 >= 995)
			{
				New_Player1.x_coord -= 10;

			}
			return;
		}
		else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
			//yI += 10;
			New_Player1.y_coord += 10;
			New_Player1.bottom = false;
			New_Player1.Top = true;
			New_Player1.right = false;
			New_Player1.left = false;
			if (New_Player1.PowerUp == false)
			{
				New_Player1.movement++;
				CHECKFORPOWERUP1();
			}
			if (New_Map.No_Obstacles == false)
			{
				New_Player1.PathDetection();
			}

			if (New_Player1.y_coord + 10 >= 725)
			{
				New_Player1.y_coord -= 10;

			}
			return;
		}

		else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
			//yI -= 10;
			New_Player1.y_coord -= 10;
			New_Player1.bottom = true;
			New_Player1.Top = false;
			New_Player1.right = false;
			New_Player1.left = false;
			if (New_Player1.PowerUp == false)
			{
				New_Player1.movement++;
				CHECKFORPOWERUP1();
			}
			if (New_Map.No_Obstacles == false)
			{
				New_Player1.PathDetection();
			}

			if (New_Player1.y_coord - 10 <= 5)
			{
				New_Player1.y_coord += 10;
			}
			return;
		}
		else if (key == GLUT_KEY_SHIFT_R && New_Player1.bullet == false)
		{

			New_Player1.bullet = true;
			if (New_Player1.bottom == true)
			{
				New_Player1.i = 2;
			}
			else if (New_Player1.Top == true)
			{
				New_Player1.i = 1;
			}
			else if (New_Player1.left == true)
			{
				New_Player1.i = 3;
			}
			else if (New_Player1.right == true)
			{
				New_Player1.i = 4;
			}
			if (New_Player1.PowerUp == true)
			{
				New_Player1.ammo++;
			}
			if (New_Player1.ammo == 3)
			{
				New_Player1.Speed = 20;
				New_Player1.max_dis = 40;
				New_Player1.PowerUp = false;
				New_Player1.PowerUpType = 0;
				New_Player1.ammo = 0;
				if (First_PowerUp.Display == true)
				{
					First_PowerUp.Display = false;
					First_PowerUp.RESET();
				}
				else if (Second_PowerUp.Display == true)
				{
					Second_PowerUp.Display = false;
					Second_PowerUp.RESET();
				}
				New_Player1.movement = 0;
				New_Player2.movement = 0;
				Second_PowerUp.RESET();
				First_PowerUp.RESET();
			}
			New_Player1.ResetBullet();
			glutTimerFunc(New_Player1.Speed, moveBullet1, 0);
		}

		/* This function ca1lls the Display function to redo the drawing. Whenever you need to redraw just call
		 * this function*/

		glutPostRedisplay();
	}

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {                       //has the movement as well sas shooting funtion of player 2
	if (Game_Menu.PLAYER1 == true || Game_Menu.PLAYER2 == true)
	{
		if (key == 27/* Escape key ASCII*/) {
			Game_Menu.PLAYER1 = false;
			Game_Menu.PLAYER2 = false;
			Game_Menu.MENU = false;
			Game_Menu.RESUME = true;
			glutPostRedisplay();
		}
	}
	if (Game_Menu.Player1Name == true)
	{
		New_Player1.name += key;
		glutPostRedisplay();
	}
	if (Game_Menu.Player2Name == true)
	{
		New_Player2.name += key;
		glutPostRedisplay();
	}
	//exit(1); // exit the program when escape key is pressed.
	if (!New_Player2.Died)
	{
		if (key == 'w' || key == 'W') //Going UP Player2
		{
			New_Player2.y_coord += 10;
			New_Player2.bottom = false;
			New_Player2.Top = true;
			New_Player2.right = false;
			New_Player2.left = false;
			if (New_Player2.PowerUp == false)
			{
				New_Player2.movement++;
				CHECKPOWERUP2();
			}
			if (New_Map.No_Obstacles == false)
			{
				New_Player2.PathDetection();
			}

			if (New_Player2.y_coord + 10 >= 725)
			{
				New_Player2.y_coord -= 10;

			}

		}
		else if (key == 's' || key == 'S')
		{
			New_Player2.y_coord -= 10;
			New_Player2.bottom = true;
			New_Player2.Top = false;
			New_Player2.right = false;
			New_Player2.left = false;
			if (New_Player2.PowerUp == false)
			{
				New_Player2.movement++;
				CHECKPOWERUP2();
			}
			if (New_Map.No_Obstacles == false)
			{
				New_Player2.PathDetection();
			}

			if (New_Player2.y_coord - 10 <= 5)
			{
				New_Player2.y_coord += 10;
			}
		}
		else if (key == 'd' || key == 'D')
		{
			New_Player2.x_coord += 10;
			New_Player2.bottom = false;
			New_Player2.Top = false;
			New_Player2.right = true;
			New_Player2.left = false;
			if (New_Player2.PowerUp == false)
			{
				New_Player2.movement++;
				CHECKPOWERUP2();
			}
			if (New_Map.No_Obstacles == false)
			{
				New_Player2.PathDetection();
			}

			if (New_Player2.x_coord + 10 >= 995)
			{
				New_Player2.x_coord -= 10;

			}
		}
		else if (key == 'a' || key == 'A')
		{
			New_Player2.x_coord -= 10;
			New_Player2.bottom = false;
			New_Player2.Top = false;
			New_Player2.right = false;
			New_Player2.left = true;
			if (New_Player2.PowerUp == false)
			{
				New_Player2.movement++;
				CHECKPOWERUP2();
			}
			if (New_Map.No_Obstacles == false)
			{
				New_Player2.PathDetection();
			}

			if (New_Player2.x_coord - 10 <= 5)
			{
				New_Player2.x_coord += 10;
				/*New_Player1.bottom = false;
				New_Player1.Top = false;
				New_Player1.right = true;
				New_Player1.left = false;*/
			}
		}

		else if ((key == 'r' || key == 'R') && New_Player2.bullet == false)
		{

			New_Player2.bullet = true;
			if (New_Player2.bottom == true)
			{
				New_Player2.i = 2;
			}
			else if (New_Player2.Top == true)
			{
				New_Player2.i = 1;
			}
			else if (New_Player2.left == true)
			{
				New_Player2.i = 3;
			}
			else if (New_Player2.right == true)
			{
				New_Player2.i = 4;
			}
			if (New_Player2.PowerUp == true)
			{
				New_Player2.ammo++;
			}
			if (New_Player2.ammo == 3)
			{
				New_Player2.Speed = 20;
				New_Player2.max_dis = 40;
				New_Player2.PowerUp = false;
				New_Player2.PowerUpType = 0;
				New_Player2.ammo = 0;
				if (First_PowerUp.Display == true)
				{
					First_PowerUp.Display = false;
					First_PowerUp.RESET();
				}
				else if (Second_PowerUp.Display == true)
				{
					Second_PowerUp.Display = false;
					Second_PowerUp.RESET();
				}
				New_Player1.movement = 0;
				New_Player2.movement = 0;
			}
			New_Player2.ResetBullet();
			glutTimerFunc(New_Player2.Speed, moveBullet2, 0);
		}
		glutPostRedisplay();
	}
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */


 /*This function is called (automatically) whenever your mouse moves witin inside the game window
  *
  * You will have to add the necessary code here for finding the direction of shooting
  *
  * This function has two arguments: x & y that tells the coordinate of current position of move mouse
  *
  * */
void MousePressedAndMoved(int x, int y) {             //useless
	//glutTimerFunc(100, New_Player1.MoveBulletWithSpeed, 0);
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {							//useless
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {										//useless

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		cout << "Right Button Pressed" << endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char* argv[]) {


	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	/*/cout << "Enter Player 1 Name:";
	cin >> New_Player1.name;
	cout << "Enter Player 2 Name:";
	cin >> New_Player2.name;*/

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Naveed Ahmad"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	srand(time(NULL));



	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(GameDisplay);
	// tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	//glutTimerFunc(100.0, Timer, 0);

	//glutTimerFunc(100.0, New_Player1.MoveBulletWithSpeed, 0);



	//glutMouseFunc(MouseClicked);
	//glutPassiveMotionFunc(MouseMoved); // Mouse
	//glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();



	return 1;
}
#endif /* RushHour_CPP_ */
