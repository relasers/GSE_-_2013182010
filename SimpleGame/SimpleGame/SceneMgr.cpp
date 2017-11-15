#include "stdafx.h"
#include "SceneMgr.h"


CSceneMgr::CSceneMgr()
{
	g_Renderer = new Renderer(CLIENT_WIDTH, CLIENT_HEIGHT);

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initialize()
{
	// Initialize Renderer
	if(!g_Renderer) g_Renderer = new Renderer(CLIENT_WIDTH, CLIENT_HEIGHT);

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	BuildObjects();
}

void CSceneMgr::BuildObjects()
{
	// 6채의 건물 배치
	for (int i = 0; i < 6; ++i)
	{
		CSolidCube* building = new CSolidCube(g_Renderer, Position_Building[i], { 0,0,0 }, OBJECT_TYPE::OBJECT_BUILDING);
		
		// 붉은 팀, 푸른 팀 구분
		if(i<3)
			building->SetTeam((TEAM_TYPE)0);
		else
			building->SetTeam((TEAM_TYPE)1);


		Building.push_back(building);
	}
	


	//for (int i = 0; i < MAXOBJECT; ++i)
	//{
	//	Vector3f position = {-CLIENT_WIDTH/2 + rand()%CLIENT_WIDTH,-CLIENT_WIDTH / 2 + rand() % CLIENT_WIDTH ,0};
	//	Vector3f direction = {-50 + rand()%100 ,-50 + rand() % 100 , 0};
	//	direction = Normalize(direction);
	//	Cube.push_back(new CSolidCube(g_Renderer, position, direction, OBJECT_TYPE::OBJECT_CHARACTER));
	//}

	


}

void CSceneMgr::ReleaseObjects()
{
	delete g_Renderer;
}

void CSceneMgr::Update(const double TimeElapsed)
{
	
	placement_tick += TimeElapsed;
	spawn_tick += TimeElapsed;


	// 붉은 캐릭터 1초당 랜덤한 위치에 생성하기
	if (spawn_tick > 1.f)
	{
		spawn_tick = 0;

		Vector3f direction = { -500 + rand() % 1000 ,-500 + rand() % 1000 , 0 };
		direction = Normalize(direction);

		// 화면 상단 랜덤한 위치에서 생성
		CSolidCube* character = new CSolidCube(g_Renderer,
		{ (float) (rand() % (CLIENT_WIDTH) - CLIENT_WIDTH*0.5) ,
			(float) (rand() % CLIENT_HEIGHT*0.5) ,
			0 },
			direction, OBJECT_TYPE::OBJECT_CHARACTER);

		character->SetTeam(TEAM_TYPE::TEAM_RED);

		Character.push_back(character);
	}
	








	for (auto& elem : Character) { 
		elem->Update( TimeElapsed ); 
		
		// 각자의 쿨타임으로 판단한다.
		if (elem->GetShootTimer() > 1.f)
		{
			elem->SetShootTimer(0);
			// 상대팀 건물이 있으면 
			if (!Building.empty())
			{
				int target_idx = -1; // 목표 타겟
				int idx = -1;		// 탐색용 인덱스
				for (auto& d : Building)
				{
					idx++;
					if (d->GetTeam() != elem->GetTeam())
					{
						target_idx = idx;
						break;
					}
				}

				if (target_idx == -1) continue;

				Vector3f direction = Building[target_idx]->GetPosition() - elem->GetPosition();
				direction = Normalize(direction);

				CSolidCube* arrow = new CSolidCube(g_Renderer,
					elem->GetPosition() + direction*SIZE_CHARACTER, direction, OBJECT_TYPE::OBJECT_ARROW);
				
				arrow->SetParentPointer( (&elem) );
				arrow->SetTeam(elem->GetTeam());
				Arrow.push_back(arrow);
			}
			else {
				// 건물일 없으면 랜덤 방향 발사
				Vector3f direction = { -500 + rand() % 1000 ,-500 + rand() % 1000 , 0 };
				direction = Normalize(direction);

				CSolidCube* arrow = new CSolidCube(g_Renderer,
					elem->GetPosition() + direction*SIZE_CHARACTER, direction, OBJECT_TYPE::OBJECT_ARROW);

				arrow->SetParentPointer((&elem));
				arrow->SetTeam(elem->GetTeam());
				Arrow.push_back(arrow);
			
			}
			
		}
	
	
	
	}
	for (auto& elem : Building) { 
		elem->Update(TimeElapsed);
	
		// 건물의 쿨타임으로 판단한다.
		if (elem->GetShootTimer() > 1.f)
		{
			elem->SetShootTimer(0);
			Vector3f direction = { -500 + rand() % 1000 ,-500 + rand() % 1000 , 0 };
			direction = Normalize(direction);
			CSolidCube* bullet = new CSolidCube(g_Renderer,
				elem->GetPosition(), direction, OBJECT_TYPE::OBJECT_BULLET);
			bullet->SetTeam(elem->GetTeam());


			Bullet.push_back(bullet);

		}
	
	}
	for (auto& elem : Bullet) { elem->Update(TimeElapsed); }
	for (auto& elem : Arrow) { elem->Update(TimeElapsed); }

	for (auto& elem : Character) {

		elem->SetCollisioned(false);

		for (auto& elem_2 : Building) {
			
			// 팀이 다르다면 상호작용
			if(elem->GetTeam() != elem_2->GetTeam())
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem_2->SetLife(elem_2->GetLife() - elem->GetLife());
				elem->SetLife(elem->GetLife() - 100);
			}
		}

		for (auto& elem_2 : Bullet) {

			// 팀이 다르다면 상호작용
			if (elem->GetTeam() != elem_2->GetTeam())
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem->SetLife(elem->GetLife() - elem_2->GetLife());
				elem_2->SetLife(elem_2->GetLife() - 100);
			}
		}

		for (auto& elem_2 : Arrow) {
			
			// 팀이 다르다면 상호작용
			if (elem->GetTeam() != elem_2->GetTeam())
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem->SetLife(elem->GetLife() - elem_2->GetLife());
				elem_2->SetLife(elem_2->GetLife() - 100);
			}
		}


	}

	/////////////////////////////////////////////////////////////////////////////

	for (auto& elem : Building) {
		elem->SetCollisioned(false);


		for (auto& elem_2 : Arrow) {

			// 팀이 다르다면 상호작용
			if (elem->GetTeam() != elem_2->GetTeam())
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem->SetLife(elem->GetLife() - elem_2->GetLife());
				elem_2->SetLife(elem_2->GetLife() - 100);
			}
		}
	}

	
	for (std::vector<CSolidCube*>::iterator iter = Building.begin(); iter != Building.end(); ) {
		if ((*iter)->LifeCheck())
		{
			delete * iter;
			*iter = NULL;
			iter = Building.erase(iter);
		}
		else
			++iter;
	}

	for (std::vector<CSolidCube*>::iterator iter = Character.begin(); iter != Character.end(); ) {
		if ((*iter)->LifeCheck())
		{
			delete * iter;
			*iter = NULL;
			iter = Character.erase(iter);
		}
		else
			++iter;
	}

	for (std::vector<CSolidCube*>::iterator iter = Bullet.begin(); iter != Bullet.end(); ) {
		if ((*iter)->LifeCheck())
		{
			delete * iter;
			*iter = NULL;
			iter = Bullet.erase(iter);
		}
		else
			++iter;
	}

	for (std::vector<CSolidCube*>::iterator iter = Arrow.begin(); iter != Arrow.end(); ) {
		if ((*iter)->LifeCheck())
		{
			delete * iter;
			*iter = NULL;

			iter = Arrow.erase(iter);
		}
		else
			++iter;
	}

}

void CSceneMgr::Render()
{
	for (auto& elem : Building) {	elem->Render(); }

	for (auto& elem : Character) {	elem->Render(); }

	for (auto& elem : Bullet) { elem->Render(); }

	for (auto& elem : Arrow) { elem->Render(); }
}

void CSceneMgr::Input_Key(unsigned char key, int x, int y)
{
}

void CSceneMgr::Input_SpecialKey(int key, int x, int y)
{
}

void CSceneMgr::Input_MouseButton(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			// 유닛 배치 틱이 음수일 떄 배치 가능하도록 한다.
			// 화면 절반 아래에서만 배치할 수 있도록 한다.
			if (placement_tick > 2.f  && ( CLIENT_HEIGHT / 2 - y) < 0 && Character.size() < MAXOBJECT)
			{
				Vector3f direction = { -500 + rand() % 1000 ,-500 + rand() % 1000 , 0 };
				direction = Normalize(direction);

				CSolidCube* character = new CSolidCube(g_Renderer,
				{ x - CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2 - y,0 },
					direction, OBJECT_TYPE::OBJECT_CHARACTER);
				
				character->SetTeam(TEAM_TYPE::TEAM_BLUE);

				Character.push_back(character);
				placement_tick = 0; // 2초의 쿨타임을 할당한다.
				
			}
			
		}

	}
}
