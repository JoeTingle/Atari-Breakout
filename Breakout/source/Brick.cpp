//includes to allow use of the UG Framework
#include "UGFW.h"
#include "UG_Defines.h"
#include "include/Brick.h"
#include <iostream>
#include <math.h>

Brick::Brick()
{
	//Creating collision information and setting intial sprite colour
	maxX = spriteWidth;
	maxY = spriteHeight;
	minX = 0;
	minY = 0;
	ChooseColour();
	//Creating sprite and setting position
	sprite = UG::CreateSprite("./build/images/Paddle.png", (float)spriteWidth, (float)spriteHeight, true, spriteColour);
	vPosition.SetY(760);
	vPosition.SetX(0);
}

void Brick::Update()
{
	//Updating collision informaiton with the current position
	maxX = spriteWidth + (int)vPosition.GetX();
	maxY = spriteHeight + (int)vPosition.GetY();
	minX = 0 + (int)vPosition.GetX();
	minY = 0 + (int)vPosition.GetY();

	//Checking if the brick is alive
	if (alive)
	{
		UG::DrawSprite(sprite);
		UG::SetSpritePosition(sprite, vPosition.GetX(), vPosition.GetY());
	}
}

void Brick::Hit(Player &player)
{
	//Adds socre and destroys the sprite when function is called
	player.score += 10;
	alive = false;
	UG::DestroySprite(sprite);
}

void Brick::ChooseColour()
{
	//Chooses a random colour
	int random = rand() % 3;
	if (random == 1)
	{
		spriteColour = sColRed;
	}
	if (random == 2)
	{
		spriteColour = sColGreen;
	}
	if (random == 3)
	{
		spriteColour = sColPink;
	}
}

Brick::~Brick()
{
}