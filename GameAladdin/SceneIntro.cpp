#include "SceneIntro.h"
#include "SceneManager.h"
#include "Animations.h"
#include "Textures.h"

void SceneIntro::KeyState(BYTE * state)
{
}

void SceneIntro::OnKeyDown(int KeyCode)
{
}

void SceneIntro::OnKeyUp(int KeyCode)
{
}

void SceneIntro::LoadResources()
{
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	if (Sprites::GetInstance()->Get(80202) != nullptr)
		return;
	sprites->Add(80202, 9, 12, 252, 102, texture);
}

void SceneIntro::Update(DWORD dt)
{
	dTime += dt;
	if (dTime> 5000)
		SceneManager::GetInstance()->SetScene(SceneManager::GetInstance()->sceneGame);
	a += 1;
	if (a > 255)
		a = 255;
}

void SceneIntro::Render()
{
	Sprites::GetInstance()->Get(80202)->Draw(10, 40, a);
}

SceneIntro::SceneIntro()
{
	dTime = 0;
	LoadResources();
	a = 0;
	flag = 0;
}


SceneIntro::~SceneIntro()
{
}
