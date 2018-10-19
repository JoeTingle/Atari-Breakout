//\===========================================================================================================================================
//\ Filename: main.cpp
//\ Author  : Joe Tingle
//\ Date    : 09/07/2018
//\ Brief   : Main Entry Point For The Game Breakout 
//\===========================================================================================================================================

//includes to allow use of the UG Framework
#include "UGFW.h"
#include "UG_Defines.h"

//My Includes
#include "include/Player.h"
#include "include/Ball.h"
#include "include/Brick.h"
#include <iostream>
#include <math.h>
#include <time.h>

//Forward Declerations of functions
void SetupFonts();
void SetupMapBoundaries();
void SpawnBricks();
void CheckCollisions(Player &player, Ball &ball);
Vector2 GenerateRandomVelocity();
void UpdateScoreText(Player &player);

//Class Variables
Vector2 mapTopLeft;
Vector2 mapTopRight;
Vector2 mapBottomLeft;
Vector2 mapBottomRight;
float deltaTime = 0;
float countdown = 0.5f;
float collisionDeadTime = 0.5f;
const int bricksToGenerate = 90;
Brick* brickArray[100];

//\===========================================================================================================================================
//\ Main entry point into our application 
//\  argv - this is the number of command line arguments that are present when we open our application 
//\			if we open this exe by clicking on it with a mouse this number is 1. 
//\  argc - this is a varadic string argument, the number of items in the array is defined by the value in argv
//\===========================================================================================================================================
int main(int argv, char* argc[])
{
	// If statement used to create an instance of the framework
	// If this returns 0 the framework could not be created and
	// the application will terminate with an error state
	if(!UG::Create(1024, 768, false, "Breakout (1976)", 100, 100)) return 1;

	//UG function call to set the background color for the applications render window
	//SColour is a structure that defines a colour with a hex code - in this case to teal.
	UG::SetBackgroundColor(UG::SColour(0x00, 0x00, 0x00, 0xFF));

	//Creating instances of objects (the player and the ball)
	Player player;
	Ball ball;

	//Various startup functions to setup fonts for text and to spawn the objects in the game
	SetupFonts();
	SpawnBricks();

	// This is the start of our main game loop, we are using a do while loop (these loops are covered in a lecture!)
	do 
	{
		UG::ClearScreen();

		// Quit our application when escape is pressed
		if (UG::IsKeyDown(UG::KEY_ESCAPE))
			UG::Close();

		//Getting delta time value for independent movement
		deltaTime = UG::GetDeltaTime();

		//Updating All Objects
		player.Update();
		if (player.lives > 0)
		{
			ball.Update();
		}

		//Setting up map boundary collisions
		SetupMapBoundaries();

		//Updating Text
		UpdateScoreText(player);

		//Itterating through brick array and updating each one
		for (int i = 0; i < 90; i++)
		{
			brickArray[i]->Update();
		}

		//Checking for end game if player runs out of lives
		if (player.lives <= 0)
		{
			std::cout << "END GAME" << std::endl;
			UG::DrawString("GAME OVER, PRESS ESC TO EXIT !", 1024 / 2, 768/2, 1, UG::SColour(0xff, 0xff, 0xff, 0xFF));
		}
		//Temporary Win Value
		if (player.score >= 250)
		{
			std::cout << "GAME WON !" << std::endl;
			UG::DrawString("GAME OVER, PRESS ESC TO EXIT !", 1024 / 2, 768 / 2, 1, UG::SColour(0xff, 0xff, 0xff, 0xFF));
		}
		
		//Debug Console Text To Track Velocity
		//std::cout << ball.vVelocity.GetX() << " , " << ball.vVelocity.GetY() << std::endl;
		//std::cout << "Lives: " << player.lives << std::endl;

		//Check collisions on all objects
		CheckCollisions(player, ball);

	} while (UG::Process());

	//Close down the framework by calling dispose.
	UG::Dispose();

	return 0;
}

Vector2 GenerateRandomVelocity()
{
	//Seeds the random number generation with the current time to ensure it is truely random
	srand(time(NULL));
	//Both a positive and negative vector to give some variety
	Vector2 positiveVector = Vector2(rand() % 100, 0);
	Vector2 negativeVector = Vector2(rand() % -100, 0);
	//So it will either return a random positive or negative vector to be added to current velocity
	if ((rand() % 2) == 1)
	{
		return negativeVector;
	}
	else
	{
		return positiveVector;
	}

}

void SpawnBricks()
{
	//Creates an intial brick object to base position  of other brick off of.
	brickArray[0] = new Brick();
	//Setting position to near top of the screen
	brickArray[0]->vPosition = Vector2(0, 700);

	//Each for loop counts as a row of bricks
	//Will loop through and spawn 15 bricks each time setting the position to +80 each time so they tile nicely
	for (int i = 1; i < 15; i++)
	{
		brickArray[i] = new Brick();
		brickArray[i]->vPosition.SetX(brickArray[i-1]->vPosition.GetX()+80);
		brickArray[i]->vPosition.SetY(700);

	}

	for (int j = 15; j < 30; j++)
	{
		brickArray[j] = new Brick();
		brickArray[j]->vPosition.SetX(brickArray[j - 15]->vPosition.GetX());
		brickArray[j]->vPosition.SetY(660);

	}

	for (int k = 30; k < 45; k++)
	{
		brickArray[k] = new Brick();
		brickArray[k]->vPosition.SetX(brickArray[k - 30]->vPosition.GetX());
		brickArray[k]->vPosition.SetY(620);

	}

	for (int l = 45; l < 60; l++)
	{
		brickArray[l] = new Brick();
		brickArray[l]->vPosition.SetX(brickArray[l - 45]->vPosition.GetX());
		brickArray[l]->vPosition.SetY(580);

	}

	for (int m = 60; m < 75; m++)
	{
		brickArray[m] = new Brick();
		brickArray[m]->vPosition.SetX(brickArray[m - 60]->vPosition.GetX());
		brickArray[m]->vPosition.SetY(540);

	}

	for (int n = 75; n < 90; n++)
	{
		brickArray[n] = new Brick();
		brickArray[n]->vPosition.SetX(brickArray[n - 75]->vPosition.GetX());
		brickArray[n]->vPosition.SetY(500);

	}
}

void CheckCollisions(Player &player, Ball &ball)
{
	//There is a collision dead zone to stop it from constantly bouncing between objects and getting stuck
	if (collisionDeadTime <= 0)
	{
		//Checks if there is a collision by using AABB collision detection with min and max values
		if (player.minX < ball.maxX && player.maxX > ball.minX && player.minY < ball.maxY && player.maxY > ball.minY)
		{
			std::cout << "COLIISION" << std::endl;
			//Inverts the velocity to make it seem as though it bounces off the object
			-ball.vVelocity;
			//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
			//Then adds in the random velocity
			ball.vVelocity = ball.vVelocity + GenerateRandomVelocity();
		}
		if (ball.vPosition.GetY() < player.vPosition.GetY())
		{
			//End Game or take life away
			player.lives--;
		}

		//Map collision
		if (mapBottomLeft.GetX() < ball.maxX && mapBottomRight.GetX() > ball.minX && mapBottomRight.GetY() < ball.maxY && mapTopRight.GetY() > ball.minY) {}
		else
		{
			std::cout << "OUT OF BOUNDS" << std::endl;
			-ball.vVelocity;
			//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV				
			ball.vVelocity = ball.vVelocity - GenerateRandomVelocity();
		}

		//Itterates through all bricks and checks collision
		for (int i = 0; i < 90; i++)
		{
			if (brickArray[i]->minX < ball.maxX && brickArray[i]->maxX > ball.minX && brickArray[i]->minY < ball.maxY && brickArray[i]->maxY > ball.minY && brickArray[i]->alive)
			{
				std::cout << "HIT" << std::endl;
				-ball.vVelocity;
				//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV				
				ball.vVelocity = ball.vVelocity + GenerateRandomVelocity();
				//Calls the hit function which adds score and removes the brick
				brickArray[i]->Hit(player);
			}
		}
		collisionDeadTime = 0.5f;
	}
	collisionDeadTime = collisionDeadTime - deltaTime;

}

void SetupFonts()
{
	//Adding main font to the game for all text UI elements
	int mainFont = UG::AddFont("./build/fonts/Roboto-Medium.ttf", 25);
	UG::SetFont(mainFont);
}

void SetupMapBoundaries()
{
	//Creating map collision boundaries
	mapTopLeft = Vector2(10, 764);
	mapTopRight = Vector2(1000, 764);
	mapBottomLeft = Vector2(10, 10);
	mapBottomRight = Vector2(1000, 10);

	//UG::DrawLine(mapTopRight.GetX(), mapTopRight.GetY(), mapTopLeft.GetX(), mapTopLeft.GetY(), 2.0f, 1, UG::SColour(255, 0, 0, 255));
	//UG::DrawLine(mapTopRight.GetX(), mapTopRight.GetY(), mapBottomRight.GetX(), mapBottomRight.GetY(), 2.0f, 1, UG::SColour(255, 0, 0, 255));
	//UG::DrawLine(mapBottomRight.GetX(), mapBottomRight.GetY(), mapBottomLeft.GetX(), mapBottomLeft.GetY(), 2.0f, 1, UG::SColour(255, 0, 0, 255));
	//UG::DrawLine(mapBottomLeft.GetX(), mapBottomLeft.GetY(), mapTopLeft.GetX(), mapTopLeft.GetY(), 2.0f, 1, UG::SColour(255, 0, 0, 255));
}

void UpdateScoreText(Player &player)
{
	//Score Text
	char integer_string[32];
	int integer = player.score;
	char scorestring[64] = "Score : ";
	sprintf(integer_string, "%d", integer);
	strcat(scorestring, integer_string);
	UG::DrawString(scorestring, 1024 / 2, 768 - 20, 1, UG::SColour(0xff, 0xff, 0xff, 0xFF));
	//

	//Lives Text
	char int_string[32];
	int livesint = player.lives;
	char livesstring[64] = "Lives : ";
	sprintf(int_string, "%d", livesint);
	strcat(livesstring, int_string);
	UG::DrawString(livesstring, 1024 / 2, 768 - 40, 1, UG::SColour(0xff, 0xff, 0xff, 0xFF));
	//
}

