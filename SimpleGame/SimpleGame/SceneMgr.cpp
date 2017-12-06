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

	m_pSound = new Sound();

	m_Sound_BGM = m_pSound->CreateSound("Sounds/MF-W-90.XM");
	m_Sound_Explosion = m_pSound->CreateSound("Sounds/explosion.wav");
	m_pSound->PlaySound(m_Sound_BGM, true, 0.2f);
	

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
	
	m_pBackGround = new CBackGround(g_Renderer, Vector3f{ 0,0,0 }, (float)CLIENT_WIDTH, (float)CLIENT_HEIGHT, Color{0.7f,0.7f,0.7f,1});
	m_pBackGround->SetTexture("Textures/BackGround.png");
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

	m_ShakeFactor -= TimeElapsed;
	if (m_ShakeFactor < 0) m_ShakeFactor = 0;

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
	


	/////////////// < 건물 업데이트 > ////////////////



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

	//////////////////////////////////////////////////



	for (auto& elem : Character) { 
		elem->Update( TimeElapsed ); 
		
		// 각자의 쿨타임으로 판단한다.
		if (elem->GetShootTimer() > 1.f)
		{
			elem->SetShootTimer(0);

			// 상대팀 건물이 있다면?
			bool EnemyBuilding_exist = false;
			for (auto&elem2 : Building)
			{
				if (elem->GetTeam() != elem2->GetTeam())
					EnemyBuilding_exist = true;
			}

			// 상대팀 건물이 있으면 
			if (EnemyBuilding_exist)
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
	
	for (auto& elem : Bullet) { elem->Update(TimeElapsed); }
	for (auto& elem : Arrow) { elem->Update(TimeElapsed); }

	///////////////////////////////////////////////////////////////////////////////

	for (auto& elem : Character) {

		elem->SetCollisioned(false);

		// 1, Character <---> Building 데미지

		for (auto& elem_2 : Building) {
			
			// 팀이 다르다면 상호작용
			if(elem->GetTeam() != elem_2->GetTeam())
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem_2->SetLife(elem_2->GetLife() - elem->GetLife());
				elem->SetLife(elem->GetLife() - 100);
			}
		}


		// 2. Character <---> Bullet 데미지

		for (auto& elem_2 : Bullet) {

			// 팀이 다르다면 상호작용
			if (elem->GetTeam() != elem_2->GetTeam())
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem->SetLife(elem->GetLife() - elem_2->GetLife());
				elem_2->SetLife(elem_2->GetLife() - 100);
			}
		}

		// 3. Character <---> Arrow 데미지

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

		// 4. Building <---> Arrow 데미지

		for (auto& elem_2 : Arrow) {

			// 팀이 다르다면 상호작용
			if (elem->GetTeam() != elem_2->GetTeam())
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem->SetLife(elem->GetLife() - elem_2->GetLife());
				elem_2->SetLife(elem_2->GetLife() - 100);
			}
		}

		// 5. Building <---> Bullet 데미지

		for (auto& elem_2 : Bullet) {

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
			m_ShakeFactor = 1.f;
			m_pSound->PlaySound(m_Sound_Explosion, false, 0.3f);
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
	Vector3f direction = { -500 + rand() % 1000 ,-500 + rand() % 1000 , 0 };
	direction = Normalize(direction);
	g_Renderer->SetSceneTransform(direction.x * m_ShakeFactor * 12, direction.y * m_ShakeFactor * 12 , 1, 1);

	m_pBackGround->Render();

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
