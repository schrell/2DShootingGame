#pragma once
#include "olcPixelGameEngine.h"
#include "Scene.h"

#define SCREEN_HEIGHTS 500
#define SCREEN_WIDTH 400
#define BULLET_HEIGHTS 14
#define BULLET_WIDTHS 5

class Actor;
class Bullet;
class Enemy;
class EnemyBullet;

class CSP:public olc::PixelGameEngine
{
private:

	SCENE mSceneState = SCENE::TITLE;

	Actor* mActor = nullptr;
	
	Bullet* mBullet;

	Enemy* mEnemyCrab[2];
	Enemy* mEnemyOcto[2];
	Enemy* mEnemyUFO;

	EnemyBullet* mEBullet;
	EnemyBullet* mEBullet1;
	EnemyBullet* mEBullet2;
	EnemyBullet* mEBullet3;

	
public:
	CSP();


public:
	bool aabb(float tX1, float tY1, float tX2, float tY2, int tW1, int tW2, int tH1, int tH2)
	{
		return tX1 + tW1 >= tX2 && tX2 + tW2 >= tX1 && tY1 + tH1 >= tY2 && tY2 + tH2 >= tY1;
	}
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	bool OnUserPlayGame(float FElsapedTime);
	void DrawCircleEquation(int tXCenter, int tYCenter, int tRadius, olc::Pixel tColor);
	void OnUserSetup();
	bool OnUserDestroy();
	void BulletStrikeEnemy(Bullet* tBullet, Enemy* tEnemy);
	void EBulletStrikeActor(EnemyBullet* EBullet, Actor* tActor);

public:
	olc::Sprite* mpSpriteOcto[1] = { nullptr };
	olc::Sprite* mpSpriteCrab[1] = { nullptr };
	olc::Sprite* mpSpritePlayer[1] = { nullptr };


};

