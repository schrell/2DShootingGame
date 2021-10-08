#pragma once
#include "CSP.h"

class Actor
{
private:
	CSP* mp = nullptr;
	float mX = 0.0f;
	float mY = 0.0f;
	float mRadius = 0.0f;
	float mMoveSpeed = 0.0f;
	bool mAlive = false;
	int mLife = 0;
	int mScore = 0;
public:
	int mCurIndexBullet = 0;
	void SetChr(CSP* ptr);
	void Setup(float tX, float tY, float tRadius, float tMoveSpeed);
	float GetmX();
	float GetmY();
	float GetmRadius();
	float GetmMoveSpeed();
	bool GetAlive();
	void SetAlive(bool tAlive);
	int GetLife();
	void SetLife(int tLife);
	int GetScore();
	void SetScore(int tScore);
public:
	void DoMoveLeft(float fElapsedTime);
	void DoMoveRight(float fElapsedTime);
	void DoMoveUp(float fElapsedTime);
	void DoMoveDown(float fElapsedTime);
	void DisplayChr(CSP* tShooter);
	void DoFire(Bullet* tBullet);
};

