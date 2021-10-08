#include "enemy.h"
#include "Bullet.h"
#include "actor.h"
#include "EnemyBullet.h"
#include "olcPixelGameEngine.h"
#include "CSP.h"


float Enemy::GetmX()
{
	return mX;
}
void Enemy::SetmX(float tX)
{
	mX = tX;
}
float Enemy::GetmY()
{
	return mY;
}
void Enemy::SetmY(float tY)
{
	mY = tY;
}
bool Enemy::GetAlive()
{
	return mIsAlive;
}
void Enemy::SetAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}
float Enemy::GetmDirX()
{
	return mDirX;
}
void Enemy::SetmDirX(float tDirX)
{
	mDirX = tDirX;
}
float Enemy::GetmDirY()
{
	return mDirY;
}
void Enemy::SetmDirY(float tDirY)
{
	mDirY = tDirY;
}
float Enemy::GetmRadius()
{
	return mRadius;
}
void Enemy::SetmRadius(float tRadius)
{
	mRadius = tRadius;
}
float Enemy::GetmMoveSpeed()
{
	return mMoveSpeed;
}
void Enemy::SetmMoveSpeed(float tMoveSpeed)
{
	mMoveSpeed = tMoveSpeed;
}
float Enemy::GetmTimeTick()
{
	return mTimeTick;
}
void Enemy::SetmTimeTick(float tTimeTick)
{
	mTimeTick = tTimeTick;
}

bool Enemy::GetWallCheckL()
{
	return mWallCheckL;
}
bool Enemy::GetWallCheckR()
{
	return mWallCheckR;
}
void Enemy::SetWallCheckL(bool tCheckL)
{
	mWallCheckL = tCheckL;
}
void Enemy::SetWallCheckR(bool tCheckR)
{
	mWallCheckR = tCheckR;
}


void Enemy::Setup(float tX, float tY, float tRadius, int tScore)
{
	mX = tX;
	mY = tY;
	mRadius = tRadius;
	mScore = tScore;
	mIsAlive = true;
}

void Enemy::UpdateAIWall(CSP* tEnemy)
{
	if (mIsAlive)
	{
		if (mX > SCREEN_WIDTH)
		{
			mWallCheckR = true;
		}
		else if (mX < 0)
		{
			mWallCheckL = true;
		}
	}
}


void Enemy::UpdateAIMove(float fElapsedTime)
{

	if (mWallCheckR)
	{
		mTimeTick = mTimeTick + fElapsedTime;
		if (mTimeTick <= 0.5f)
		{
			mDirX = 0.0f;
			mDirY = 1.0f;
		}
		else
		{
			mDirX = -1.0f;
			mDirY = 0.0f;
			mTimeTick = 0.0f;
		}
		mWallCheckR = false;
	}

	if (mWallCheckL)
	{
		mTimeTick = mTimeTick + fElapsedTime;
		if (mTimeTick <= 0.5f)
		{
			mDirX = 0.0f;
			mDirY = 1.0f;
		}
		else
		{
			mDirX = 1.0f;
			mDirY = 0.0f;
			mTimeTick = 0.0f;
		}
		mWallCheckL = false;
	}

	mX = mX + mDirX * 30.0f * fElapsedTime;
	mY = mY + mDirY * 30.0f * fElapsedTime;
}

void Enemy::UpdateUFOMove(float fElapsedTime)
{
	mX = mX + 1 * 50.0f * fElapsedTime;
}

void Enemy::DisplayEnemy(CSP* tEnemy)
{
	if (mIsAlive)
	{
		tEnemy->DrawCircleEquation(mX, mY, mRadius, olc::WHITE);
	}
}

void Enemy::DoFire(EnemyBullet* tEBullet)
{

	(tEBullet + mCurIndexBullet)->SetmX(mX);
	(tEBullet + mCurIndexBullet)->SetmY(mY);
	(tEBullet + mCurIndexBullet)->SetmDirY(10);

	if (mIsAlive)
	{
		(tEBullet + mCurIndexBullet)->SetAlive(true);
	}
	if (mCurIndexBullet < 10 - 1)
	{
		mCurIndexBullet++;
	}
	else
	{
		mCurIndexBullet = 0;
	}
}

void Enemy::DoFireAimed(EnemyBullet* tEBullet, Actor* tpTargetUnit)
{
	(tEBullet + mCurIndexBullet)->SetmX(mX);
	(tEBullet + mCurIndexBullet)->SetmY(mY);
	(tEBullet + mCurIndexBullet)->SetmDirX(tpTargetUnit->GetmX() - mX);
	(tEBullet + mCurIndexBullet)->SetmDirY(tpTargetUnit->GetmY() - mY);

	float tDistance = sqrtf((tpTargetUnit->GetmX() - mX) * (tpTargetUnit->GetmX() - mX) + (tpTargetUnit->GetmY() - mY) * (tpTargetUnit->GetmY() - mY));

	(tEBullet + mCurIndexBullet)->SetmDirX((tEBullet + mCurIndexBullet)->GetmDirX() / tDistance);
	(tEBullet + mCurIndexBullet)->SetmDirY((tEBullet + mCurIndexBullet)->GetmDirY() / tDistance);

	if (mIsAlive)
	{
		(tEBullet + mCurIndexBullet)->SetAlive(true);
	}

	if (mCurIndexBullet < 10 - 1)
	{
		mCurIndexBullet++;
	}
	else
	{
		mCurIndexBullet = 0;
	}
}



