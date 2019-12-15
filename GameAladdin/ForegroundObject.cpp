#include "ForegroundObject.h"



void ForegroundObject::Render()
{
	Sprites::GetInstance()->Get(idSprite)->Draw(x - Camera::GetInstance()->GetXCam(), y - Camera::GetInstance()->GetYCam());
}

void ForegroundObject::RenderWithEffect(float a, float b)
{
	Sprites::GetInstance()->Get(idSprite)->Draw(a - Camera::GetInstance()->GetXCam()*1.2, b - Camera::GetInstance()->GetYCam()*1.2);
}

void ForegroundObject::RenderWithEffect()
{
	Sprites::GetInstance()->Get(idSprite)->Draw(x - Camera::GetInstance()->GetXCam()*1.2, y - Camera::GetInstance()->GetYCam()*1.2);
}

ForegroundObject::ForegroundObject(int idSprite, float x, float y, int width, int height)
{
	this->idSprite = idSprite;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


ForegroundObject::~ForegroundObject()
{
}
