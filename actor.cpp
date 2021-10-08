#include "Actor.h"
#include "CSP.h"
#include "Bullet.h"

void Actor::SetChr(CSP* ptr)
{
	mp = ptr;
}
float Actor::GetmX()
{
	return mX;
}
float Actor::GetmY()
{
	return mY;
}
float Actor::GetmRadius()
{
	return mRadius;
}
float Actor::GetmMoveSpeed()
{
	return mMoveSpeed;
}
bool Actor::GetAlive()
{
	return mAlive;
}
void Actor::SetAlive(bool tAlive)
{
	mAlive = tAlive;
}
int Actor::GetLife()
{
	return mLife;
}
void Actor::SetLife(int tLife)
{
	mLife = tLife;
}

int Actor::GetScore()
{
	return mScore;
}

void Actor::SetScore(int tScore)
{
	mScore = tScore;
}

void Actor::Setup(float tX, float tY, float tRadius, float tMoveSpeed)
{
	mX = tX;
	mY = tY;
	mRadius = tRadius;
	mMoveSpeed = tMoveSpeed;
	mAlive = true;
	mLife = 3;
}

void Actor::DoMoveLeft(float fElapsedTime)
{
	if (mX - mRadius > 0)
	{
		mX = mX - 80.0f * fElapsedTime;
	}
}
void Actor::DoMoveRight(float fElapsedTime)
{
	if (mX + mRadius < SCREEN_WIDTH)
	{
		mX = mX + 80.0f * fElapsedTime;
	}
}
void Actor::DoMoveUp(float fElapsedTime)
{
	if (mY - mRadius > 0)
	{
		mY = mY - 80.0f * fElapsedTime;
	}
}
void Actor::DoMoveDown(float fElapsedTime)
{
	if (mY + mRadius < SCREEN_HEIGHTS)
	{
		mY = mY + 80.0f * fElapsedTime;
	}
}

void Actor::DisplayChr(CSP* tShooter)
{
	tShooter->DrawCircleEquation((int)mX, (int)mY, (int)mRadius, olc::YELLOW);
}

void Actor::DoFire(Bullet* tBullet)
{
	(tBullet + mCurIndexBullet)->SetmX(mX);
	(tBullet + mCurIndexBullet)->SetmY(mY);
	(tBullet + mCurIndexBullet)->SetAlive(true);

	if (mCurIndexBullet < 10 - 1)
	{
		mCurIndexBullet++;
	}
	else
	{
		mCurIndexBullet = 0;
	}

	if (tBullet->GetmY() <= 0)
	{
		tBullet->SetAlive(false);
	}
}