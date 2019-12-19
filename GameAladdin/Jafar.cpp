#include "Jafar.h"

bool Jafar::isLoadedSprite = false;

void Jafar::LoadSprite()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_BOSS);
	sprites->Add(41937, 8, 9, 72, 80, texture, 10);
	sprites->Add(41938, 80, 10, 137, 80, texture, 11);
	sprites->Add(41939, 144, 11, 199, 80, texture, 12);
	sprites->Add(41940, 208, 12, 259, 80, texture, 13);
	sprites->Add(41941, 272, 11, 336, 80, texture, 12);
	sprites->Add(41942, 344, 11, 426, 80, texture, 12);
	sprites->Add(41943, 440, 11, 525, 80, texture, 12);
	sprites->Add(41944, 536, 11, 604, 80, texture, 12);
	sprites->Add(41946, 11, 93, 65, 161, texture, 13);
	sprites->Add(41947, 82, 91, 140, 161, texture, 11);
	sprites->Add(41948, 146, 91, 204, 161, texture, 11);
	sprites->Add(41949, 211, 96, 275, 161, texture, 16);
	sprites->Add(41950, 283, 104, 344, 162, texture, 23);
	sprites->Add(41951, 351, 102, 410, 162, texture, 21);
	sprites->Add(41952, 416, 96, 475, 161, texture, 16);
	sprites->Add(41954, 1, 242, 41, 261, texture, 62);
	sprites->Add(41955, 60, 221, 103, 261, texture, 41);
	sprites->Add(41956, 123, 206, 171, 261, texture, 26);
	sprites->Add(41957, 187, 191, 250, 261, texture, 11);
	sprites->Add(41958, 259, 188, 324, 261, texture, 8);
	sprites->Add(41959, 344, 182, 410, 261, texture, 2);
	sprites->Add(41960, 426, 179, 494, 261, texture, -1);
	sprites->Add(41961, 504, 177, 575, 261, texture, -3);
	sprites->Add(41962, 588, 175, 661, 261, texture, -5);
	sprites->Add(41963, 672, 174, 747, 261, texture, -6);
	sprites->Add(41964, 776, 175, 849, 261, texture, -5);
	sprites->Add(41965, 8, 317, 78, 375, texture, 23);
	sprites->Add(41966, 88, 311, 152, 375, texture, 17);
	sprites->Add(41967, 160, 303, 227, 375, texture, 9);
	sprites->Add(41968, 240, 303, 311, 375, texture, 9);
	sprites->Add(41969, 320, 291, 389, 375, texture, -3);
	sprites->Add(41970, 400, 292, 469, 375, texture, -2);
	sprites->Add(41971, 480, 293, 550, 375, texture, -1);
	sprites->Add(41972, 560, 293, 630, 375, texture, -1);
	sprites->Add(41973, 644, 292, 708, 376, texture, -3);
	sprites->Add(41974, 716, 294, 780, 376, texture, -1);
	sprites->Add(41975, 788, 315, 859, 376, texture, 20);
	sprites->Add(41977, 14, 392, 38, 439, texture, 34);
	sprites->Add(41978, 46, 386, 68, 439, texture, 28);
	sprites->Add(41979, 78, 392, 102, 439, texture, 34);
	sprites->Add(41980, 110, 389, 137, 439, texture, 31);
	sprites->Add(41981, 150, 393, 185, 439, texture, 35);
	sprites->Add(41983, 198, 425, 226, 439, texture, 67);
	sprites->Add(41984, 238, 423, 262, 439, texture, 65);
	sprites->Add(41985, 270, 424, 296, 439, texture, 66);
	sprites->Add(41987, 310, 426, 324, 439, texture, 68);
	sprites->Add(41988, 334, 425, 355, 439, texture, 67);
	sprites->Add(41989, 382, 418, 397, 439, texture, 60);
	sprites->Add(41991, 8, 485, 83, 535, texture, 31);
	sprites->Add(41992, 96, 487, 175, 535, texture, 33);
	sprites->Add(41993, 184, 493, 277, 535, texture, 39);
	sprites->Add(41994, 296, 494, 386, 535, texture, 40);
	sprites->Add(41995, 400, 506, 477, 535, texture, 52);
	sprites->Add(41996, 488, 504, 561, 535, texture, 50);
	sprites->Add(41997, 568, 492, 632, 535, texture, 38);
	sprites->Add(41998, 645, 484, 709, 535, texture, 30);


}

void Jafar::LoadResource()
{
	if (!isLoadedSprite)
		LoadSprite();
	
	Animation * ani = new Animation(90, 0);
	ani->Add(41937, 2000);
	ani->Add(41938);
	ani->Add(41939);
	ani->Add(41940);
	ani->Add(41941);
	ani->Add(41942);
	ani->Add(41943);
	ani->Add(41944);
	this->animations[JAFAR_ATTACK] = ani;
	
	ani = new Animation(90, 0);
	ani->Add(41946);
	ani->Add(41947);
	ani->Add(41948);
	ani->Add(41949);
	ani->Add(41950);
	ani->Add(41951);
	ani->Add(41952);
	this->animations[JAFAR_THROW_SNAKE] = ani;

	ani = new Animation(90);
	ani->Add(41954);
	ani->Add(41955);
	ani->Add(41956);
	ani->Add(41957);
	ani->Add(41958);
	ani->Add(41959);
	ani->Add(41960);
	ani->Add(41961);
	ani->Add(41962);
	ani->Add(41963);
	ani->Add(41964);
	ani->Add(41965);
	ani->Add(41966);
	ani->Add(41967);
	ani->Add(41968);
	ani->Add(41969);
	ani->Add(41970);
	ani->Add(41971);
	ani->Add(41972);
	ani->Add(41973);
	ani->Add(41974);
	ani->Add(41975);
	this->animations[SNAKE_APPEAR] = ani;

	ani = new Animation(90);
	ani->Add(41977);
	ani->Add(41978);
	ani->Add(41979);
	ani->Add(41980);
	ani->Add(41981);
	this->animations[FIRER] = ani;

	ani = new Animation(90);
	ani->Add(41991);
	ani->Add(41992);
	ani->Add(41993);
	ani->Add(41994);
	ani->Add(41995);
	ani->Add(41996);
	ani->Add(41997);
	ani->Add(41998);
	this->animations[FIRER_OF_SNAKE] = ani;
}

Jafar::Jafar()
{
	health = 30;
	x = 448;
	y = 300;
	width = 37;
	height = 50;
	vx = 0;
	vy = 0;
	isSnake = false;
	isDeath = false;
}


Jafar::~Jafar()
{
}

void Jafar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}

void Jafar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	dtime += dt;
	if (health == 15)
	{
		SetCurrentState(JAFAR_THROW_SNAKE);
		isSnake = true;
		return;
	}
	if (!isSnake)
	{
		if (animations[JAFAR_ATTACK]->GetCurrentFrame() > 4 && dtime > 50)
		{
			
		}
	}
	else
	{

	}
}

void Jafar::Render(int flip)
{

}

void Jafar::SetCurrentState(int currentState)
{
}
