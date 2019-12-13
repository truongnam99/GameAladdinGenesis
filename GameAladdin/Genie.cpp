#include "Genie.h"

bool Genie::isLoadedResource = false;

void Genie::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);

	sprites->Add(41840, 328, 3440, 366, 3490, texture);
	sprites->Add(41841, 376, 3438, 419, 3490, texture);
	sprites->Add(41842, 429, 3446, 472, 3490, texture);
	sprites->Add(41843, 482, 3446, 527, 3490, texture);
	Animation * ani = new Animation(300);
	ani->Add(41840);
	ani->Add(41841);
	ani->Add(41842);
	ani->Add(41843);
	anim->Add(41840, ani);
	this->animations[GENIE_STATE_1] = ani;

	sprites->Add(41845, 523, 1500, 552, 1522, texture);
	sprites->Add(41846, 562, 1497, 593, 1522, texture);
	sprites->Add(41847, 603, 1495, 633, 1522, texture);
	ani = new Animation(300);
	ani->Add(41845);
	ani->Add(41846);
	ani->Add(41847);
	anim->Add(41845, ani);
	this->animations[GENIE_STATE_2] = ani;
}

Genie::Genie(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = oType::GENIE;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[GENIE_STATE_1] = Animations::GetInstance()->Get(41840);
	this->animations[GENIE_STATE_2] = Animations::GetInstance()->Get(41845);
	SetCurrentState(GENIE_STATE_1);
}


Genie::~Genie()
{
}

void Genie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == GENIE_STATE_1) {
		left = (float)x;
		top = (float)y;
		right = left + (float)width;
		bottom = top + (float)height;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Genie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Genie::Render(int flip)
{
	if (currentState == GENIE_STATE_2 && animations[currentState]->GetCurrentFrame() == animations[currentState]->GetCountFrame() - 1)
		return;
	animations[currentState]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	//RenderBoundingBox();
}
