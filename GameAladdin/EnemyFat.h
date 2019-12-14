#ifndef _ENEMY_FAT_
#define _ENEMY_FAT_
#include "GameObject.h"

#define ENEMY_WALK_SPEED 0.12f

#define ENEMY_DEFIANT 1 //enemy béo khiêu khích
#define ENEMY_WALK 2 //enemy béo đi qa đi lại
#define ENEMY_ATTACKING 3 //enemy béo đánh
#define ENEMY_DEATH 4 //enemy béo bị thương

#include <cstdlib>
#include <ctime>
class EnemyFat :public GameObject
{
private:
	int ny;
	static bool isLoadedSprite;
	void LoadSprite();

	int LeftMargin;
	int RightMargin;
	bool isOnlyStay;
public:
	EnemyFat(int id, float x, float y, int width, int height, oType type, int leftMargin = -1, int rightMargin=-1);
	~EnemyFat();

	void LoadResource();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(int flip = 1);
	void SetCurrentState(int currentState);
};

#endif //!_ENEMY_FAT
