#pragma once

class Enemy;
class CSP;
class Actor;

class EnemyBullet
{
private:
	float mX = 0.0f;
	float mY = 0.0f;
	bool mIsAlive = false;
	float mDirX = 0.0f;//πÊ«‚∫§≈Õ¿« X
	float mDirY = 0.0f;//πÊ«‚∫§≈Õ¿« Y
	float mRadius = 0.0f;
public:
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
public:
	void Setup(Enemy* tEnemy);
	void EBulletMove(float fElapsedTime);
	void DisplayEBullet(CSP* tEnemy);
};

