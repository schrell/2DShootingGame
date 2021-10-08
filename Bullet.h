#pragma once

class Actor;
class CSP;

class Bullet
{
private:
	float mX = 0.0f;
	float mY = 0.0f;
	float mDirX = 0.0f;
	float mDirY = 0.0f;
	float mRadius = 0.0f;
	float mMoveSpeed = 0.0f;
	bool mIsAlive = false;
public:
	float GetmX();
	void SetmX(float tX);
	float GetmY();
	void SetmY(float tY);
	float GetmDirX();
	void SetmDirX(float tDirX);
	float GetmDirY();
	void SetmDirY(float tDirY);
	bool GetAlive();
	void SetAlive(bool mIsAlive);
	float GetmRadius();
	void SetmRadius(float tRadius);
	float GetmMoveSpeed();
	void SetmMoveSpeed(float tMoveSpeed);

public:
	void Setup(Actor *tActor);
	void UpdateMove(float fElapsedTime);
	void DisplayBullet(CSP *tShooter);
};
