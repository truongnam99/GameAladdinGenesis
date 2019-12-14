#include "Apple.h"

bool Apple::isLoadedResource = false;

void Apple::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);

	sprites->Add(41802, 422, 1501, 429, 1508, texture);
	Animation * ani = new Animation(300);
	ani->Add(41802);
	anim->Add(41802, ani);
	this->animations[APPLE_STATE_1] = ani;

	sprites->Add(41804, 476, 1512, 483, 1522, texture);
	sprites->Add(41805, 493, 1504, 513, 1522, texture);
	sprites->Add(41806, 523, 1500, 552, 1522, texture);
	sprites->Add(41807, 562, 1497, 593, 1522, texture);
	sprites->Add(41808, 603, 1495, 633, 1522, texture);
	ani = new Animation(120);
	ani->Add(41804, 60);
	ani->Add(41805, 60);
	ani->Add(41806, 60);
	ani->Add(41807, 60);
	ani->Add(41808, 60);
	anim->Add(41804, ani);
	this->animations[APPLE_STATE_2] = ani;
}

Apple::Apple()
{
	GameObject::GameObject();
	type = APPLE;
}

Apple::Apple(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = APPLE;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[APPLE_STATE_1] = Animations::GetInstance()->Get(41802);
	this->animations[APPLE_STATE_2] = Animations::GetInstance()->Get(41804);
	SetCurrentState(APPLE_STATE_1);
}


Apple::~Apple()
{
}

void Apple::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (currentState == APPLE_STATE_1) {
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

void Apple::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Apple::Render(int flip)
{
	if (currentState == APPLE_STATE_2 && animations[currentState]->GetCurrentFrame() == animations[currentState]->GetCountFrame() - 1)
		return;
	animations[currentState]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	//RenderBoundingBox();
}
