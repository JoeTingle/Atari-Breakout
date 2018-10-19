//includes to allow use of the UG Framework
#include "UGFW.h"
#include "UG_Defines.h"
#include "include/Ball.h"
#include <iostream>

//Class variables
const float g_fIMPULSE = 100.0f;
const Vector2 g_vRIGHT(1.0f, 0.0f);
const Vector2 g_vLEFT(-1.0f, 0.0f);
const Vector2 g_vUP(0.0f, 1.0f);
const Vector2 g_vDOWN(0.0f, -1.0f);
Vector2 oZero(0.0f, 0.0f);

//Function to update position with velocity over time
Vector2 Ball::CalculateNewPosition(Vector2 &a_oInitialPosition, Vector2 &a_oVelocity, float a_fDeltaTime) const //Updating position accouting for velocity
{
	return Vector2(a_oInitialPosition.GetX() + (a_oVelocity.GetX() * a_fDeltaTime), a_oInitialPosition.GetY() + (a_oVelocity.GetY() * a_fDeltaTime));
}

Ball::Ball()
{
	//Collision information
	maxX = spriteWidth;
	maxY = spriteHeight;
	minX = 0;
	minY = 0;
	//Creating sprite information and setting position
	sprite = UG::CreateSprite("./build/images/ball.png", spriteWidth, spriteHeight, true, UG::SColour(255, 255, 255, 255));
	vPosition.SetY(768/2);
	vPosition.SetX(1024/2);
	vVelocity = Vector2(0.0f, 0.0f);
	//Create random velocity
	vVelocity = g_vDOWN * g_fIMPULSE; //Adding an impulse to the player velocity to project them upwards
}
Ball::~Ball()
{

}

void Ball::Update()
{
	//Updating collision information with the position
	maxX = spriteWidth + vPosition.GetX();
	maxY = spriteHeight + vPosition.GetY();
	minX = 0 + vPosition.GetX();
	minY = 0 + vPosition.GetY();

	//Drawing and setting sprite position
	UG::DrawSprite(sprite);
	UG::SetSpritePosition(sprite, vPosition.GetX(), vPosition.GetY());
	fDeltaTime = UG::GetDeltaTime();




	//Updating position every frame, calculating new position with the velocity
	vPosition = CalculateNewPosition(vPosition, vVelocity, fDeltaTime);

	UG::SetSpritePosition(sprite, vPosition.GetX(), vPosition.GetY());
}

