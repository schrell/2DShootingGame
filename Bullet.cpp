#include "Bullet.h"
#include "actor.h"
#include "CSP.h"

float Bullet::GetmX()
{
	return mX;
}
void Bullet::SetmX(float tX)
{
	mX = tX;
}
float Bullet::GetmY()
{
	return mY;
}
void Bullet::SetmY(float tY)
{
	mY = tY;
}
float Bullet::GetmDirX()
{
	return mDirX;
}
void Bullet::SetmDirX(float tDirX)
{
	mDirX = tDirX;
}
float Bullet::GetmDirY()
{
	return mDirY;
}
void Bullet::SetmDirY(float tDirY)
{
	mDirY = tDirY;
}
bool Bullet::GetAlive()
{
	return mIsAlive;
}
void Bullet::SetAlive(bool tIsAlive)
{
	mIsAlive = tIsAlive;
}
float Bullet::GetmRadius()
{
	return mRadius;
}
void Bullet::SetmRadius(float tRadius)
{
	mRadius = tRadius;
}
float Bullet::GetmMoveSpeed()
{
	return mMoveSpeed;
}
void Bullet::SetmMoveSpeed(float tMoveSpeed)
{
	mMoveSpeed = tMoveSpeed;
}
void Bullet::Setup(Actor* tActor)
{
	mX = tActor->GetmX();
	mY = tActor->GetmY();
	mRadius = 3;
	mMoveSpeed = 300.0f;
	mIsAlive = false;
}
void Bullet::UpdateMove(float fElapsedTime)
{
	if (mIsAlive)
	{
		mY = mY - mMoveSpeed *fElapsedTime;
	}
}
void Bullet::DisplayBullet(CSP *tShooter)
{
	if (mIsAlive)
	{
		tShooter->DrawRect(GetmX(), GetmY(), BULLET_WIDTHS, BULLET_HEIGHTS, olc::RED);
	}
}
