#include "EnemyBullet.h"
#include "enemy.h"
#include "CSP.h"

 float EnemyBullet::GetmX()
{
	return mX;
}
void EnemyBullet::SetmX(float tX)
{
	mX = tX;
}
float EnemyBullet::GetmY()
{
	return mY;
}
void EnemyBullet::SetmY(float tY)
{
	mY = tY;
}
bool EnemyBullet::GetAlive()
{
	return mIsAlive;
}
void EnemyBullet::SetAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}
float EnemyBullet::GetmDirX()
{
	return mDirX;
}
void EnemyBullet::SetmDirX(float tDirX)
{
	mDirX = tDirX;
}
float EnemyBullet::GetmDirY()
{
	return mDirY;
}
void EnemyBullet::SetmDirY(float tDirY)
{
	mDirY = tDirY;
}
float EnemyBullet::GetmRadius()
{
	return mRadius;
}
void EnemyBullet::SetmRadius(float tRadius)
{
	mRadius = tRadius;
}

void EnemyBullet::Setup(Enemy* tEnemy)
{
	SetmX(tEnemy->GetmX());
	SetmY(tEnemy->GetmY());
	mRadius = 5;
	mIsAlive = false;
}
void EnemyBullet::EBulletMove(float fElapsedTime)
{
	if (mIsAlive)
	{
		mY = mY + mDirY * 30.0f * fElapsedTime;
	}
}
void EnemyBullet::DisplayEBullet(CSP* tEnemy)
{
	if (GetAlive())
	{
		tEnemy->DrawCircleEquation(GetmX(), GetmY(), mRadius, olc::GREEN);
	}
}