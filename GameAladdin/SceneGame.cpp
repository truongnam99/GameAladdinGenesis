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
	pointReset = NULL;
	aladdin->LoadResource();
	dyc = 0;

	// load resource cho foreground
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_RESOURCE_MAP1A);
	sprites->Add(51056, 208, 13, 248, 357, texture);
	sprites->Add(51057, 528, 13, 560, 173, texture);
	sprites->Add(51058, 848, 13, 880, 748, texture);
	sprites->Add(51059, 977, 210, 1009, 402, texture);
	sprites->Add(51060, 1068, 210, 1146, 418, texture);
	sprites->Add(51064, 220, 316, 739, 572, texture);

	foreground = new Foreground();
	foreground->list_foregroundObject.push_back(new ForegroundObject(51056, 177, 762));
	foreground->list_foregroundObject.push_back(new ForegroundObject(51057, 498, 957));
	foreground->list_foregroundObject.push_back(new ForegroundObject(51058, 817, 373));
	foreground->list_foregroundObject.push_back(new ForegroundObject(51059, 1169, 925));
	foreground->list_foregroundObject.push_back(new ForegroundObject(51060, 2193, 69));
	
	foregroundx = new ForegroundObject(51064, 0, 0, 519, 256);
}

void SceneGame::Update(DWORD dt)
{
	grid->Update(dt);
	grid->GetObjects(obj);
	
	for (auto x : obj)
	{
		if (x->GetType() == ENEMYBAT)
		{
			EnemyBat * e = (EnemyBat *)x;
			float ax, ay;
			aladdin->GetPosition(ax, ay);
			e->aladdinPosition.x = ax;
			e->aladdinPosition.y = ay;
		}
		if (x->GetType() == ENEMYSKELETON)
		{
			EnemySkeleton * e = (EnemySkeleton *)x;
			float ax, ay;
			float ex, ey;
			aladdin->GetPosition(ax, ay);
			e->GetPosition(ex, ey);
			e->aladdinPoint.x = ax;
			e->aladdinPoint.y = ay;
			if (ax < ex)
				e->SetNx(-1);
			else
				e->SetNx(1);
		}
		x->Update(dt, &obj);
		if (x->GetType() == ENEMYFAT)
		{
			EnemyFat * e = (EnemyFat *)x;
			float x, y;
			aladdin->GetPosition(x, y);
			if (x < e->LeftMargin)
				e->SetNx(-1);
			if (x > e->RightMargin)
				e->SetNx(1);
		}
		if (x->GetType() == ENEMYTHIN)
		{
			EnemyThin * e = (EnemyThin *)x;
			float ax, ay;
			aladdin->GetPosition(ax, ay);
			if (ax < e->LeftMargin)
				e->SetNx(-1);
			if (ax > e->RightMargin)
				e->SetNx(1);
		}
		
	}
	// update aladdin
	aladdin->Update(dt, &obj);
	float x;
	float y;
	aladdin->GetPosition(x, y);

	// tạo hiệu ứng chuyển động của cam
	if (aladdin->GetCurrentState() == ALADDIN_IDLE_LOOK_UP)
	{
		if (dyc > -80)
			dyc-=4;
	}
	else if (aladdin->isSitting)
	{
		if (dyc < 80)
			dyc+=4;
	}
	else
		if (dyc > 0)
			dyc-=4;
		else if (dyc < 0)
			dyc+=4;
	camera->SetPosition(x - 140, y - 110 + dyc);

	if (aladdin->isCollsionWithRestartPoint)
	{
		if (pointReset == NULL)
			pointReset = new PointReset();

		vector<LPGAMEOBJECT> gridObject;
		grid->GetAllObject(gridObject);
		pointReset->SetPointReset(gridObject, aladdin);

		aladdin->isCollsionWithRestartPoint = false;
	}
	 
	if (aladdin->GetHealth() <= 0)
	{
		aladdin->SetHeart(aladdin->GetHeart() - 1);
		
		if (aladdin->GetHeart() <= 0)
		{
			// isGameOver = true;
			Aladdin * a = aladdin;
			delete a;
			aladdin = new Aladdin();
			aladdin->LoadResource();
			grid->ResetState();
		} 
		else if (pointReset == NULL)
		{
			Aladdin * a = aladdin;
			delete a;
			aladdin = new Aladdin();
			aladdin->LoadResource();
			grid->ResetState();
			aladdin->SetHealth(9);
			
		}
		else
		{
			vector<LPGAMEOBJECT> gridObject;
			grid->GetAllObject(gridObject);
			pointReset->ResetState(gridObject, aladdin);
			aladdin->SetHealth(9);
		}
	}
	Board::GetInstance()->Update(dt, aladdin->GetHealth(), aladdin->GetHeart(), aladdin->GetScore(), aladdin->GetRedJewelCount(), aladdin->GetApplesCount());
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

	int oCount=0;
	//for (int i = 0; i < grid->cellShowing.size(); i++)
	//{
	//	int id = grid->cellShowing[i];
	//	int oC = grid->GetCell(id)->object.size();
	//	for (int j = 0; j < oC; j++)
	//	{
	//		grid->GetCell(id)->object[j]->RenderBoundingBox(); // Vẽ renderBouding để debug
	//	}
	//}

	// render lop tren cung
	for (int i = 0; i < foreground->list_foregroundObject.size(); i++)
		foreground->list_foregroundObject[i]->Render();
	
	if (foregroundx->x > Camera::GetInstance()->GetXCam() + Camera::GetInstance()->GetWidth())
		foregroundx->x -= foregroundx->width;
	if (foregroundx->x + foregroundx->width < Camera::GetInstance()->GetXCam())
		foregroundx->x += foregroundx->width;
	if (foregroundx->y > Camera::GetInstance()->GetYCam() + Camera::GetInstance()->GetHeight())
		foregroundx->y -= foregroundx->height;
	if (foregroundx->y + foregroundx->height < Camera::GetInstance()->GetYCam())
		foregroundx->y += foregroundx->height;

	float a = foregroundx->x;
	float b = foregroundx->y;
	int w = foregroundx->width;
	int h = foregroundx->height;

	foregroundx->RenderWithEffect(a, b- h);
	foregroundx->RenderWithEffect();
	foregroundx->RenderWithEffect(a, b + h);
	foregroundx->RenderWithEffect(a, b + 2*h);

	foregroundx->RenderWithEffect(a+w, b - h);
	foregroundx->RenderWithEffect(a+w, b);
	foregroundx->RenderWithEffect(a+w, b + h);
	foregroundx->RenderWithEffect(a + w, b + 2*h);

	foregroundx->RenderWithEffect(a - w, b - h);
	foregroundx->RenderWithEffect(a-w, b);
	foregroundx->RenderWithEffect(a-w, b + h);
	foregroundx->RenderWithEffect(a - w, b + 2*h);
	Board::GetInstance()->Render();
}

SceneGame::SceneGame()
{
	textures = Textures::GetInstance();
	camera = Camera::GetInstance();
	map = Map::GetInstance();
	LoadResources();
	isGameOver = false;
}

SceneGame::~SceneGame()
{
	delete aladdin;
	delete pointReset;
	delete foreground;
}