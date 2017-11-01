#include "stdafx.h"
#include "SceneMgr.h"


CSceneMgr::CSceneMgr()
{
	g_Renderer = new Renderer(500, 500);

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
	if(!g_Renderer) g_Renderer = new Renderer(500, 500);

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	BuildObjects();
}

void CSceneMgr::BuildObjects()
{
	
	Building.push_back(new CSolidCube(g_Renderer, { 0,0,0 }, {0,0,0}, OBJECT_TYPE::OBJECT_BUILDING));


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
	tick++;

	for (auto& elem : Character) { elem->Update( TimeElapsed ); }
	for (auto& elem : Building) { 
		elem->Update(TimeElapsed);
	
		if (tick % 30 == 0)
		{
			Vector3f direction = { -500 + rand() % 1000 ,-500 + rand() % 1000 , 0 };
			direction = Normalize(direction);

			Bullet.push_back(new CSolidCube(g_Renderer,
			elem->GetPosition(), direction, OBJECT_TYPE::OBJECT_BULLET));
		}
	
	}
	for (auto& elem : Bullet) { elem->Update(TimeElapsed); }
	

	for (auto& elem : Character) {

		elem->SetCollisioned(false);

		for (auto& elem_2 : Building) {
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem->SetLife(elem->GetLife() - elem_2->GetLife());
				elem_2->SetLife(elem_2->GetLife() - elem->GetLife());
			}
		}

		for (auto& elem_2 : Bullet) {
			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem->SetLife(elem->GetLife() - elem_2->GetLife());
				elem_2->SetLife(elem_2->GetLife() - 100);
			}
		}





	}

	
	for (std::vector<CSolidCube*>::iterator iter = Building.begin(); iter != Building.end(); ) {
		if ((*iter)->LifeCheck())
			iter = Building.erase(iter);
		else
			++iter;
	}

	for (std::vector<CSolidCube*>::iterator iter = Character.begin(); iter != Character.end(); ) {
		if ((*iter)->LifeCheck())
			iter = Character.erase(iter);
		else
			++iter;
	}

	for (std::vector<CSolidCube*>::iterator iter = Bullet.begin(); iter != Bullet.end(); ) {
		if ((*iter)->LifeCheck())
			iter = Bullet.erase(iter);
		else
			++iter;
	}

}

void CSceneMgr::Render()
{
	for (auto& elem : Character) {	elem->Render(); }

	for (auto& elem : Building) {	elem->Render(); }

	for (auto& elem : Bullet) { elem->Render(); }
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
			if (Character.size() < MAXOBJECT)
			{
				Vector3f direction = { -500 + rand() % 1000 ,-500 + rand() % 1000 , 0 };
				direction = Normalize(direction);

				Character.push_back(new CSolidCube(g_Renderer,
				{ x - CLIENT_WIDTH / 2,CLIENT_HEIGHT / 2 - y,0 },
					direction, OBJECT_TYPE::OBJECT_CHARACTER));

				
			}
			
		}

	}
}
