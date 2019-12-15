#ifndef __FOREGROUNDOBJECT__
#define __FOREGROUNDOBJECT__

#include "Sprites.h"
#include "Camera.h"
class ForegroundObject
{
public:
	float x; 
	float y;
	int width;
	int height;
	int  idSprite;
	void Render();
	void RenderWithEffect(float a, float b);
	void RenderWithEffect();

	ForegroundObject(int idSprite, float x, float y, int width = 0, int height = 0);
	~ForegroundObject();
};



#endif // !__FOREGROUNDOBJECT__


