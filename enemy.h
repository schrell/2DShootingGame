#pragma once

class CSP;
class EnemyBullet;
class Actor;

class Enemy
{
private:
	float mX = 0.0f;
	float mY = 0.0f;
	bool mIsAlive = false;
	float mDirX = 1.0f;
	float mDirY = 0.0f;
	float mRadius = 0.0f;
	float mMoveSpeed = 0.0f;
	float mTimeTick = 0.0f;
	int mScore = 0;
	bool mWallCheckL = false;
	bool mWallCheckR = false;
public:
	int mCurIndexBullet = 0;
	float GetmX();
	void SetmX(float tX);
	float GetmY();
	void SetmY(float tY);
	bool GetAlive();
	void SetAlive(bool tIsAlive);
	float GetmDirX();
	void SetmDirX(float tDirX);
	float GetmDirY();
	void SetmDirY(float tDirY);
	float GetmRadius();
	void SetmRadius(float tRadius);
	float GetmMoveSpeed();
	void SetmMoveSpeed(float tMoveSpeed);
	float GetmTimeTick();
	void SetmTimeTick(float tTimeTick);
	bool GetWallCheckL();
	bool GetWallCheckR();
	void SetWallCheckL(bool tCheckL);
	void SetWallCheckR(bool tCheckR);
	int GetmScore() { return mScore; };

public:
	void Setup(float tX, float tY, float tRadius, int tScore);
	void DisplayEnemy(CSP* tEnemy);
	void UpdateAIWall(CSP* tEnemy);
	void UpdateAIMove(float fElapsedTime);
	void UpdateUFOMove(float fElapsedTime);
	void DoFire(EnemyBullet* tEBullet);
	void DoFireAimed(EnemyBullet* tEBullet, Actor* tpTargetUnit);
};

