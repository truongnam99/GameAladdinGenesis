#include "SceneGame.h"
#include <cstdlib>
#include <ctime>
void SceneGame::KeyState(BYTE * state)
{
	float vx;
	float vy;
	aladdin->GetSpeed(vx, vy);
	float x, y;
	aladdin->GetPosition(x, y);
	if (Game::GetInstance()->IsKeyDown(DIK_A))
		aladdin->SetPosition(x, y - 100);

	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT) || Game::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
			aladdin->SetNx(1);
		else
			aladdin->SetNx(-1);
		if (!aladdin->isClimbing)
			aladdin->SetSpeed(ALADDIN_WARK_SPEED, vy);
		aladdin->isRunning = true;
		if (!aladdin->isAttacking)
		{
			if (!aladdin->isClimbing)
				if (!aladdin->isJumping)
					if (!Game::GetInstance()->IsKeyDown(DIK_C))
					{
						if (!aladdin->isCollisionWithWall) {
							aladdin->SetCurrentState(ALADDIN_RUNNING1);
						}
						else
						{
							aladdin->SetCurrentState(ALADDIN_PUSHING);
						}

					}
					else
					{
						aladdin->isJumping = true;
						aladdin->SetCurrentState(ALADDIN_JUMPING_FOWARD);
					}
		}
	}
	else
	{
		if (!aladdin->isClimbing)
			aladdin->SetSpeed(0, vy);
		else
			aladdin->SetSpeed(0, 0);
		aladdin->isRunning = false;
		if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
		{
			if (!aladdin->isClimbing)
			{
				if (!aladdin->isJumping && !(aladdin->isSitting &&aladdin->isAttacking))
				{
					aladdin->isSitting = true;
					aladdin->SetCurrentState(ALADDIN_IDLE_SIT);
				}

			}
			else
			{
				aladdin->SetSpeed(0, ALADDIN_CLIMB_SPEED);
				aladdin->SetCurrentState(ALADDIN_CLIMBING);
			}
		}
		else if (Game::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (aladdin->isClimbing)
			{
				aladdin->SetSpeed(0, -ALADDIN_CLIMB_SPEED);
				aladdin->SetCurrentState(ALADDIN_CLIMBING);
			}
			else if (!aladdin->isJumping && !aladdin->isSitting && !aladdin->isAttacking)
			{
				aladdin->SetCurrentState(ALADDIN_IDLE_LOOK_UP);
			}
		}
		else if (Game::GetInstance()->IsKeyDown(DIK_C))
		{
			if (!aladdin->isJumping)
			{
				aladdin->isJumping = true;
				aladdin->SetCurrentState(ALADDIN_JUMPING);
			}
		}
		else
		{
			int curState = aladdin->GetCurrentState();
			if (curState == ALADDIN_IDLE1 || curState == ALADDIN_IDLE2 || curState == ALADDIN_IDLE3)
			{
				int tolFrame = aladdin->GetAnimations(curState)->GetCountFrame();
				int curFrame = aladdin->GetAnimations(curState)->GetCurrentFrame();
				if (curFrame == tolFrame - 1)
				{
					srand(time(NULL));
					int result = rand() % 3 + 1;
					switch (result)
					{
					case 1:
						aladdin->SetCurrentState(ALADDIN_IDLE1);
						break;
					case 2:
						aladdin->SetCurrentState(ALADDIN_IDLE2);
						break;
					case 3:
						aladdin->SetCurrentState(ALADDIN_IDLE3);
						break;
					}
				}
				else
					aladdin->SetCurrentState(curState);
			}
			else
			{
				aladdin->SetCurrentState(ALADDIN_IDLE1);
			}
		}
	}
}

void SceneGame::OnKeyDown(int KeyCode)
{
	// DebugOut((wchar_t*)L"down:%d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_X:
		aladdin->isAttacking = true;
		if (aladdin->isJumping)
			aladdin->SetCurrentState(ALADDIN_JUMPING_ATTACKING);
		else if (aladdin->isClimbing)
			aladdin->SetCurrentState(ALADDIN_CLIMBING_ATTACKING);
		else if (aladdin->isRunning)
			aladdin->SetCurrentState(ALADDIN_RUNING_ATTACKING);
		else if (aladdin->isSitting)
			aladdin->SetCurrentState(ALADDIN_SITTING_ATTACKING);
		else if (aladdin->GetCurrentState() == ALADDIN_IDLE_LOOK_UP)
			aladdin->SetCurrentState(ALADDIN_STAYING_COMBO_ATTACKING);
		else aladdin->SetCurrentState(ALADDIN_STAYING_ATTACKING);
		break;
	case DIK_Z:
		aladdin->isAttacking = true;
		if (aladdin->isJumping)
			aladdin->SetCurrentState(ALADDIN_JUMPING_ATTACKING_BY_APPLE);
		else if (aladdin->isClimbing)
			aladdin->SetCurrentState(ALADDIN_CLIMBING_ATTACKING_BY_APPLE);
		else if (aladdin->isRunning)
			aladdin->SetCurrentState(ALADDIN_RUNNING_ATTACKING_BY_APPLE);
		else if (aladdin->isSitting)
			aladdin->SetCurrentState(ALADDIN_SITTING_ATACKING_BY_APPLE);
		else aladdin->SetCurrentState(ALADDIN_STAYING_ATTACKING_BY_APPLE);
		break;
	}
}

void SceneGame::OnKeyUp(int KeyCode)
{
	
}

void SceneGame::LoadResources()
{
	textures->LoadResources();
	map->SetMap(MAP1);
	map->LoadMap();
	camera->SetMap(map->GetMapWidth(), map->GetMapHeight());
	camera->SetPosition(0.0f, 0.0f);
	grid = Grid::GetInstance();
	grid->LoadGrid(MAP1);
	
	aladdin = new Aladdin();
	aladdin->LoadResource();
	dyc = 0;
}

void SceneGame::Update(DWORD dt)
{
	grid->Update(dt);
	grid->GetObjects(obj);
	
	for (auto x : obj)
	{
		x->Update(dt, &obj);
	}
	// update aladdin
	aladdin->Update(dt, &obj);
	float x;
	float y;
	aladdin->GetPosition(x, y);

	// tạo hiệu ứng chuyển động của cam
	if (aladdin->GetCurrentState() == ALADDIN_IDLE_LOOK_UP)
	{
		if (dyc > -30)
			dyc-=4;
	}
	else if (aladdin->isSitting)
	{
		if (dyc < 30)
			dyc+=4;
	}
	else
		if (dyc > 0)
			dyc-=4;
		else if (dyc < 0)
			dyc+=4;
	camera->SetPosition(x - 140, y - 110 + dyc);
}

void SceneGame::Render()
{
	map->DrawMap();
	
	// vẽ object trong grid
	for (int i = 0; i < obj.size(); i++)
	{
		obj[i]->Render();
	}
	aladdin->Render();

	//int oCount=0;
	//for (int i = 0; i < grid->cellShowing.size(); i++)
	//{
	//	int id = grid->cellShowing[i];
	//	int oC = grid->GetCell(id)->object.size();
	//	for (int j = 0; j < oC; j++)
	//	{
	//		grid->GetCell(id)->object[j]->RenderBoundingBox(); // Vẽ renderBouding để debug
	//	}
	//}
}

SceneGame::SceneGame()
{
	textures = Textures::GetInstance();
	camera = Camera::GetInstance();
	map = Map::GetInstance();
	LoadResources();
}

SceneGame::~SceneGame()
{
	delete aladdin;
}