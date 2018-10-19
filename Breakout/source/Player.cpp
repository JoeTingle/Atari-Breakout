//includes to allow use of the UG Framework
#include "UGFW.h"
#include "UG_Defines.h"
#include "include/Globals.h"
#include "./include/Player.h"
#include <iostream>

void Player::UpdateMousePos()
{
	//Function to update the position of the mouse for the player object
	int mousex;
	int mousey;
	UG::GetMousePos(mousex, mousey);
	v2MousePos.SetX(mousex);
	v2MousePos.SetY(mousey);
}

Player::Player()
{
	//Creating collision information
	maxX = spriteWidth;
	maxY = spriteHeight;
	minX = 0;
	minY = 0;
	//Creating inital sprite and setting inital position
	sprite = UG::CreateSprite("./build/images/Paddle.png", spriteWidth, spriteHeight,true, UG::SColour(255, 255, 255, 255));
	vPosition.SetY(10);
	vPosition.SetX(v2MousePos.GetX());
}
Player::~Player()
{
}

void Player::Update()
{
	//Updating collision to match the position
	maxX = spriteWidth + vPosition.GetX();
	maxY = spriteHeight + vPosition.GetY();
	minX = 0 + vPosition.GetX();
	minY = 0 + vPosition.GetY();

	//Drawing sprite and updating position
	UpdateMousePos();
	UG::DrawSprite(sprite);
	vPosition.SetX(v2MousePos.GetX());
	UG::SetSpritePosition(sprite, vPosition.GetX(), vPosition.GetY());
}


