#pragma once
enum SCENE
{
	TITLE = 0,
	READY_PLAYGAME, //playgame 상태로 전이되기 전에, 데이터 설정을 위한 상태.
	PLAYGAME,
	GAMEOVER,
	ENDING
};