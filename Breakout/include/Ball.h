#ifndef __BALL_H__
#define __BALL_H__
#include "Vector2.h"
class Ball
{
public:
	Ball();
	~Ball();

	//Update functions
	void Update();
	Vector2 CalculateNewPosition(Vector2 &a_oInitialPosition, Vector2 &a_oVelocity, float a_fDeltaTime) const;

	//Current position stored in vector2 x and y
	Vector2 vPosition;
	Vector2 vVelocity;
	//Sprite info
	int sprite;

	//Physics information
	float fMaxSpeed;
	float fPlayerAcceleration;
	float fDragAmount = 10.0f;

	float fDeltaTime;

	//Current sprite width and height
	int spriteWidth = 20;
	int spriteHeight = 20;
	#pragma region Collider
	int minX = 0;
	int minY = 0;
	int maxX = 0;
	int maxY = 0;
	#pragma endregion


private:

};
#endif // !__BALL_H__

