#include "CSP.h"
#include "Actor.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Scene.h"
#include "olcPixelGameEngine.h"
#include <iostream>
#include <algorithm>

using namespace std;

float mTimer = 0.0f;
float mTimerBoss = 0.0f;
float mTimerActor = 0.0f;

CSP::CSP()
{
	sAppName = "holyyyyyyyyyy";
}

bool CSP::OnUserCreate()
{
	OnUserSetup();

	return true;
}

void CSP::OnUserSetup()
{
	mActor = new Actor;
	mActor->SetChr(this);
	mActor->Setup(SCREEN_WIDTH / 2, SCREEN_HEIGHTS - 20, 10.0f, 300.0f);

	mBullet = new Bullet[10];
	for (int ti = 0; ti < 10; ti++)
	{
		(mBullet + ti)->Setup(mActor);
	}

	mEnemyUFO = new Enemy;
	mEnemyUFO->Setup(0, 30, 10,0);

	for (int ti = 0; ti < 2; ti++)
	{
		mEnemyCrab[ti] = new Enemy[11];
		mEnemyOcto[ti] = new Enemy[11];
	}

	for (int ti = 0; ti < 2; ti++)
	{
		for (int tii = 0; tii < 11; tii++)
		{
			(mEnemyCrab[ti] + tii)->Setup(50 + tii * 30, 100 + 50 * ti, 5, 20);
			(mEnemyOcto[ti] + tii)->Setup(50 + tii * 30, 200 + 50 * ti, 5, 10);
		}
	}

	mEBullet = new EnemyBullet[11];
	mEBullet1 = new EnemyBullet[11];
	mEBullet2 = new EnemyBullet[11];
	mEBullet3 = new EnemyBullet[11];
	for (int ti = 0; ti < 11; ti++)
	{
		(mEBullet + ti)->Setup(mEnemyCrab[0]+ti);
		(mEBullet1 + ti)->Setup(mEnemyCrab[1] + ti);
		(mEBullet2 + ti)->Setup(mEnemyOcto[0] + ti);
		(mEBullet3 + ti)->Setup(mEnemyOcto[1] + ti);

	}


	mpSpriteCrab[1] = new olc::Sprite("resources/Crab.png");
	mpSpritePlayer[1] = new olc::Sprite("resources/Player.png");
	mpSpriteOcto[1] = new olc::Sprite("resources/Octo.png");

}

bool CSP::OnUserUpdate(float fElapsedTime)
{

	switch (mSceneState)
	{
	case SCENE::TITLE:
	{
		Clear(olc::VERY_DARK_BLUE);

		DrawString(160, 120, "Shooting");
		DrawString(160, 150, "PRESS Z TO START");
		if (GetKey(olc::Key::Z).bReleased)
		{
			mSceneState = SCENE::READY_PLAYGAME;
		}
	}break;
	case SCENE::READY_PLAYGAME:
	{

		OnUserSetup();
	
		mSceneState = SCENE::PLAYGAME;
	}break;

	case SCENE::PLAYGAME:
	{
		OnUserPlayGame(fElapsedTime);

		if (mActor->GetLife() <= 0)
		{
			mSceneState = SCENE::GAMEOVER;
		}
		if (mActor->GetScore() >= 660)
		{
			mSceneState = SCENE::ENDING;
		}
	}break;
	case SCENE::GAMEOVER:
	{
		OnUserDestroy();
		Clear(olc::BLACK);
		DrawString(160, 120, "GAME OVER");
		DrawString(160, 150, "PRESS Z TO RETURN TITLE");
		if (GetKey(olc::Key::Z).bReleased)
		{
			mSceneState = SCENE::TITLE;
		}
	}break;
	case SCENE::ENDING:
	{
		OnUserDestroy();
		Clear(olc::BLACK);
		DrawString(160, 120, "CLEAR!");
		DrawString(160, 150, "PRESS Z TO RETURN TITLE");
		if (GetKey(olc::Key::Z).bReleased)
		{
			mSceneState = SCENE::TITLE;
		}
	}break;

	}

	return true;
}

bool CSP::OnUserPlayGame(float fElapsedTime)
{


	srand((unsigned int)time(nullptr));

	if (mActor->GetAlive())
	{
		if (GetKey(olc::Key::LEFT).bHeld)
		{
			mActor->DoMoveLeft(fElapsedTime);
		}
		if (GetKey(olc::Key::RIGHT).bHeld)
		{
			mActor->DoMoveRight(fElapsedTime);
		}
		if (GetKey(olc::Key::Z).bReleased)
		{
			cout << "Fire" << endl;
			mActor->DoFire(mBullet);
		}
	}

	for (int ti = 0; ti < 10; ti++)
	{
		(mBullet + ti)->UpdateMove(fElapsedTime);
	}

	mEnemyUFO->SetAlive(false);
	mTimerBoss += 1.0f * fElapsedTime;
	if (mTimerBoss >= 5.0f)
	{
		mEnemyUFO->SetAlive(true);
	}

	if (true==mEnemyUFO->GetAlive())
	{
		mEnemyUFO->DisplayEnemy(this);
		mEnemyUFO->UpdateUFOMove(fElapsedTime);
		mTimerBoss = 0.0f;
	}

	Clear(olc::BLACK);
	DrawString(10, 10, "SCORE: "+ std::to_string(mActor->GetScore()),olc::WHITE,1);
	DrawString(SCREEN_WIDTH - 150, 10, "LIFE REMAINING: " + std::to_string(mActor->GetLife()), olc::WHITE, 1);

	mActor->DisplayChr(this);

	for (int ti = 0; ti < 10; ti++)
	{
		(mBullet + ti)->DisplayBullet(this);
	}

	for (int ti = 0; ti < 11; ti++)
	{
		(mEBullet + ti)->DisplayEBullet(this);
		(mEBullet1 + ti)->DisplayEBullet(this);
		(mEBullet2 + ti)->DisplayEBullet(this);
		(mEBullet3 + ti)->DisplayEBullet(this);
	}
	
	

	for (int ti = 0; ti < 2; ti++)
	{
		for (int tii = 0; tii < 11; tii++)
		{
			(mEnemyOcto[ti] + tii)->DisplayEnemy(this);
			(mEnemyCrab[ti] + tii)->DisplayEnemy(this);

			(mEnemyOcto[ti] + tii)->UpdateAIWall(this);
			(mEnemyCrab[ti] + tii)->UpdateAIWall(this);

			(mEnemyOcto[ti] + tii)->UpdateAIMove(fElapsedTime);
			(mEnemyCrab[ti] + tii)->UpdateAIMove(fElapsedTime);
		}
	}

	int RDNumber = rand() % 10 + 1;
	if (mTimer >= 1.5f)
	{
			if ((mEnemyOcto[1] + RDNumber)->GetAlive())
			{
				(mEnemyOcto[1] + RDNumber)->DoFire(mEBullet3 + RDNumber);
			}
			else if ((mEnemyOcto[0] + RDNumber)->GetAlive())
			{
				(mEnemyOcto[0] + RDNumber)->DoFire(mEBullet2 + RDNumber);
			}
			else if ((mEnemyCrab[1] + RDNumber)->GetAlive())
			{
				(mEnemyCrab[1] + RDNumber)->DoFire(mEBullet1 + RDNumber);
			}
			else if ((mEnemyCrab[0] + RDNumber)->GetAlive())
			{
				(mEnemyCrab[0] + RDNumber)->DoFire(mEBullet + RDNumber);
			}
		mTimer = 0.0f;
	}
	else
	{
		mTimer = mTimer + 1.0f * fElapsedTime;
	}

	for (int ti = 0; ti < 11; ti++)
	{
		(mEBullet+ti)->EBulletMove(fElapsedTime);
		(mEBullet1 + ti)->EBulletMove(fElapsedTime);

		(mEBullet2 + ti)->EBulletMove(fElapsedTime);

		(mEBullet3 + ti)->EBulletMove(fElapsedTime);

	}

	SetPixelMode(olc::Pixel::MASK);
	if (mActor->GetAlive())
	{
		DrawSprite(mActor->GetmX() - 13, mActor->GetmY() - 9, mpSpritePlayer[1]);
	}
	for (int ti = 0; ti < 2; ti++)
	{
		for (int tii = 0; tii < 11; tii++)
		{
			if ((mEnemyOcto[ti]+tii)->GetAlive())
			{
				DrawSprite((mEnemyOcto[ti]+tii)->GetmX() - 7, (mEnemyOcto[ti] + tii)->GetmY() - 8, mpSpriteOcto[1]);
			}

			if ((mEnemyCrab[ti]+tii)->GetAlive())
			{
				DrawSprite((mEnemyCrab[ti]+tii)->GetmX() - 7, (mEnemyCrab[ti] + tii)->GetmY() - 8, mpSpriteCrab[1]);
			}
		}
	}

	SetPixelMode(olc::Pixel::NORMAL);

	for (int ti = 0; ti < 2; ti++)
	{
		for (int tii = 0; tii < 11; tii++)
		{
			for (int tiii = 0; tiii < 10; tiii++)
			{
				BulletStrikeEnemy((mBullet + tiii), (mEnemyOcto[ti] + tii));
				BulletStrikeEnemy((mBullet + tiii), (mEnemyCrab[ti] + tii));
			}
		}
	}

	for (int ti = 0; ti < 11; ti++)
	{
		EBulletStrikeActor((mEBullet + ti), mActor);
		EBulletStrikeActor((mEBullet1 + ti), mActor);
		EBulletStrikeActor((mEBullet2 + ti), mActor);
		EBulletStrikeActor((mEBullet3 + ti), mActor);
	}

	if (false==mActor->GetAlive())
	{
		if (mActor->GetLife() > 0)
		{
			mTimerActor = mTimerActor + fElapsedTime;
			if (mTimerActor >= 3.0f)
			{
				mActor->SetAlive(true);
				mActor->SetLife(mActor->GetLife() - 1);
				mTimerActor = 0.0f;
			}
		}
	}

	return true;
}

bool CSP::OnUserDestroy()
{
	if (nullptr != mActor)
	{
		delete mActor;
		mActor = nullptr;
	}

	if (nullptr != mBullet)
	{
		delete[] mBullet;
		mBullet = nullptr;
	}

	for (int ti = 0; ti < 2; ti++)
	{
		if (nullptr != mEnemyOcto[ti])
		{
			delete[] mEnemyOcto[ti];
			mEnemyOcto[ti] = nullptr;
		}
	}

	for (int ti = 0; ti < 2; ti++)
	{
		if (nullptr != mEnemyCrab[ti])
		{
			delete[] mEnemyCrab[ti];
			mEnemyCrab[ti] = nullptr;
		}
	}

	if (nullptr != mEnemyUFO)
	{
		delete mEnemyUFO;
		mEnemyUFO = nullptr;
	}
	
	if (nullptr != mEBullet)
	{
		delete[] mEBullet;
		mEBullet = nullptr;
	}

	if (nullptr != mEBullet1)
	{
		delete[] mEBullet1;
		mEBullet1 = nullptr;
	}

	if (nullptr != mEBullet2)
	{
		delete[] mEBullet2;
		mEBullet2 = nullptr;
	}

	if (nullptr != mEBullet3)
	{
		delete[] mEBullet3;
		mEBullet3 = nullptr;
	}

	for (int ti = 0; ti < 1; ti++)
	{
		if (nullptr != mpSpriteOcto[ti])
		{
			delete mpSpriteOcto[ti];
			mpSpriteOcto[ti] = nullptr;
		}
	}
	for (int ti = 0; ti < 1; ti++)
	{
		if (nullptr != mpSpriteCrab[ti])
		{
			delete mpSpriteCrab[ti];
			mpSpriteCrab[ti] = nullptr;
		}
	}
	for (int ti = 0; ti < 1; ti++)
	{
		if (nullptr != mpSpritePlayer[ti])
		{
			delete mpSpritePlayer[ti];
			mpSpritePlayer[ti] = nullptr;
		}
	}

	return true;
}

void CSP::BulletStrikeEnemy(Bullet* tBullet, Enemy* tEnemy)
{
	if (tEnemy->GetAlive())
		{
			if (true == tBullet->GetAlive())
			{
				if (aabb(tEnemy->GetmX(), tEnemy->GetmY(), tBullet->GetmX(), tBullet->GetmY(), tEnemy->GetmRadius(), BULLET_WIDTHS,tEnemy->GetmRadius(), BULLET_HEIGHTS))
				{
					std::cout << "Collision" << std::endl;
					tBullet->SetAlive(false);
					tEnemy->SetAlive(false);
					mActor->SetScore(mActor->GetScore()+tEnemy->GetmScore());
				}
			}
		}
	//아군탄맞추기용도. aabb 충돌 알고리즘을 사용했다
}

void CSP::EBulletStrikeActor(EnemyBullet* tEBullet, Actor* tActor)
{
	for (int ti = 0; ti < 10; ti++)
	{
		if (tActor->GetAlive())
		{
			if (true == (tEBullet + ti)->GetAlive())
			{
				float tAdd = ((tEBullet + ti)->GetmRadius() + tActor->GetmRadius()) * ((tEBullet + ti)->GetmRadius() + tActor->GetmRadius());
				float tDistance = ((tEBullet + ti)->GetmX() - tActor->GetmX()) * ((tEBullet + ti)->GetmX() - tActor->GetmX()) + ((tEBullet + ti)->GetmY() - tActor->GetmY()) * ((tEBullet + ti)->GetmY() - tActor->GetmY());
				if (tDistance <= tAdd)
				{
					std::cout << "Collision" << std::endl;
					std::cout << "ActorHit" << endl;
					(tEBullet + ti)->SetAlive(false);
					tActor->SetAlive(false);
					break;
				}
			}
		}
	} //적탄맞추기용도
}

void CSP::DrawCircleEquation(int tXCenter, int tYCenter, int tRadius, olc::Pixel tColor)
{
	int tX = 0;
	int tY = 0;
	tX = 0;
	tY = tRadius;

	while (tY >= tX)
	{
		Draw(tX + tXCenter, tY + tYCenter, tColor);
		Draw(tY + tXCenter, tX + tYCenter, tColor);
		Draw(tY + tXCenter, -tX + tYCenter, tColor);
		Draw(tX + tXCenter, -tY + tYCenter, tColor);
		Draw(-tY + tXCenter, tX + tYCenter, tColor);
		Draw(-tX + tXCenter, tY + tYCenter, tColor);
		Draw(-tX + tXCenter, -tY + tYCenter, tColor);
		Draw(-tY + tXCenter, -tX + tYCenter, tColor);
		tX++;
		tY = std::sqrtf(tRadius * tRadius - tX * tX) + 0.5f;
	}
}