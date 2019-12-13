#include "RedJewel.h"

bool RedJewel::isLoadedResource = false;

void RedJewel::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);

	sprites->Add(41829, 49, 3435, 66, 3451, texture);
	sprites->Add(41830, 76, 3435, 93, 3451, texture);
	sprites->Add(41831, 103, 3435, 120, 3451, texture);
	sprites->Add(41832, 130, 3435, 147, 3451, texture);
	sprites->Add(41833, 157, 3434, 174, 3451, texture);
	sprites->Add(41835, 226, 3433, 249, 3451, texture);
	sprites->Add(41836, 258, 3435, 275, 3451, texture);
	sprites->Add(41837, 285, 3435, 302, 3451, texture);
	Animation * ani = new Animation(120);
	ani->Add(41829);
	ani->Add(41830);
	ani->Add(41831);
	ani->Add(41832);
	ani->Add(41833);
	ani->Add(41835);
	ani->Add(41836);
	ani->Add(41837);
	anim->Add(41829, ani);
	this->animations[REDJEWEL_STATE_1] = ani;

	sprites->Add(41838, 476, 1512, 483, 1522, texture);
	ani = new Animation(300);
	ani->Add(41838);
	anim->Add(41838, ani);
	this->animations[REDJEWEL_STATE_2] = ani;
}

RedJewel::RedJewel()
{
	GameObject::GameObject();
	type = REDJEWEL;
}

RedJewel::RedJewel(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = REDJEWEL;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[REDJEWEL_STATE_1] = Animations::GetInstance()->Get(41829);
	this->animations[REDJEWEL_STATE_2] = Animations::GetInstance()->Get(41838);
	SetCurrentState(REDJEWEL_STATE_1);
}


RedJewel::~RedJewel()
{
}

void RedJewel::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == REDJEWEL_STATE_1) {
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

void RedJewel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void RedJewel::Render(int flip)
{
	if (currentState == REDJEWEL_STATE_2 && animations[currentState]->GetCurrentFrame() == animations[currentState]->GetCountFrame() - 1)
		return;
	animations[currentState]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	//RenderBoundingBox();
}
