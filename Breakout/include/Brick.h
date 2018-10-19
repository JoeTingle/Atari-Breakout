#ifndef __BRICK_H__
#define __BRICK_H__
#include "Vector2.h"
#include "Player.h"
class Brick
{
public:
	Brick();
	~Brick();


	//Update functions
	void Update();
	void Hit(Player &player);
	void ChooseColour();

	//Sprite colours
	UG::SColour spriteColour;

	UG::SColour sColRed = UG::SColour(255, 0, 0, 255);
	UG::SColour sColGreen = UG::SColour(0, 255, 0, 255);
	UG::SColour sColPink = UG::SColour(255, 0, 127, 255);

	//Current position stored in vector2 x and y
	Vector2 vPosition;
	int sprite;

	//Current sprite width and height
	int spriteWidth = 80;
	int spriteHeight = 40;

	bool alive = true;

#pragma region Collider
	int minX = 0;
	int minY = 0;
	int maxX = 0;
	int maxY = 0;
#pragma endregion

private:

};

#endif // !__BRICK_H__

