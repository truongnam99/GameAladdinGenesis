#include "Magic.h"



void Magic::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = (float)x;
	top = (float)y;
	right = left + (float)width;
	bottom = top + (float)height;
}

void Magic::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (currentState == DRAG_NON_COLLISION)
	{
		float d = v * dt;
		float dtemp = Goal.distance(x, y);
		dx = (Goal.x - x) * d / dtemp;
		dy = (Goal.y - y) * d / dtemp;
		x += dx;
		y += dy;
	}
	else
	{
		if (animations[DRAG_COLLISION]->GetCurrentFrame() == animations[DRAG_NON_COLLISION]->GetCountFrame() - 1)
			isDeath = true;
	}
}

void Magic::Render(int flip)
{
	if (isDeath)
		return;
	animations[currentState]->Render(x, y);
}

void Magic::SetCurrentState(int currentState)
{
	this->currentState = currentState;
}

Magic::Magic(float x, float y, int width, int height)
{
	Animation * ani;
	ani = new Animation(90, 0);
	ani->Add(41983);
	ani->Add(41984);
	ani->Add(41985);
	this->animations[DRAG_NON_COLLISION] = ani;

	ani = new Animation(90);
	ani->Add(41987);
	ani->Add(41988);
	ani->Add(41989);
	this->animations[DRAG_COLLISION] = ani;

	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = oType::MAGIC;
	v = 0.015;
	currentState = DRAG_NON_COLLISION;
	isDeath = false;
}


Magic::~Magic()
{
}
