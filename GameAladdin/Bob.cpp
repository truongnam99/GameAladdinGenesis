#include "Bob.h"

bool Bob::isLoadedResource = false;

void Bob::LoadResources()
{
	isLoadedResource = true;
	Sprites * sprites = Sprites::GetInstance();
	Animations * anim = Animations::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_RESOURCE_MAP1);
	sprites->Add(51001, 258, 639, 272, 684, texture);
	sprites->Add(51002, 277, 639, 292, 686, texture);
	sprites->Add(51003, 297, 639, 312, 689, texture);
	sprites->Add(51004, 317, 639, 332, 691, texture);
	sprites->Add(51005, 337, 639, 353, 695, texture);
	sprites->Add(51006, 358, 639, 374, 699, texture);
	sprites->Add(51007, 379, 639, 397, 704, texture);
	sprites->Add(51008, 402, 639, 423, 706, texture);
	sprites->Add(51009, 428, 639, 454, 704, texture);
	sprites->Add(51010, 459, 639, 487, 702, texture);
	sprites->Add(51011, 492, 639, 522, 698, texture);
	sprites->Add(51012, 527, 639, 558, 696, texture);
	sprites->Add(51013, 563, 639, 595, 695, texture);
	sprites->Add(51014, 600, 639, 633, 692, texture);
	sprites->Add(51015, 638, 639, 671, 691, texture);
	Animation * ani = new Animation(120);
	ani->Add(51001, 200);
	ani->Add(51002);
	ani->Add(51003);
	ani->Add(51004);
	ani->Add(51005);
	ani->Add(51006);
	ani->Add(51007);
	ani->Add(51008);
	ani->Add(51009);
	ani->Add(51010);
	ani->Add(51011);
	ani->Add(51012);
	ani->Add(51013);
	ani->Add(51014);
	ani->Add(51015, 200);

	anim->Add(51001, ani);
	this->animations[STATE1] = ani;
}

Bob::Bob(int id, float x, float y, int width, int height, oType type)
{
	GameObject::GameObject();
	type = BOB;
	this->id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
	nx = 0;
	if (!isLoadedResource)
		LoadResources();
	this->animations[STATE1] = Animations::GetInstance()->Get(51001);
	currentState = STATE1;
}


Bob::~Bob()
{
}

void Bob::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (animations[STATE1]->GetCurrentFrame() > 11 && animations[STATE1]->GetCurrentFrame() < 15)
	{
		left = (float)x+10;
		top = (float)y+25;
		right = left + (float)width-10;
		bottom = top + (float)height-30;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

}

void Bob::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void Bob::Render(int flip)
{
	animations[STATE1]->RenderReverse(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
	RenderBoundingBox();
}
