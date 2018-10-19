#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Vector2.h"
class Player
{
public:
	Player();
	~Player();

	//Update functions
	void Update();
	void UpdateMousePos();

	//Current position stored in vector2 x and y
	Vector2 vPosition;
	//Sprite info
	int sprite;
	//Current score, default 0
	int score = 0;

	//Current sprite width and height
	int spriteWidth = 100;
	int spriteHeight = 50;
	//Current lives
	int lives = 3;

	#pragma region Collider
	int minX = 0;
	int minY = 0;
	int maxX = 0;
	int maxY = 0;
	#pragma endregion

private:

};

#endif // !__PLAYER_H__
