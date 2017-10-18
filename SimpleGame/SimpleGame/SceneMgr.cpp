#include "stdafx.h"
#include "SceneMgr.h"


CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Initialize()
{
	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	BuildObjects();
}

void CSceneMgr::BuildObjects()
{
	

	for (int i = 0; i < 1000; ++i)
	{
		Vector3f position = {-CLIENT_WIDTH/2 + rand()%CLIENT_WIDTH,-CLIENT_WIDTH / 2 + rand() % CLIENT_WIDTH ,0};
		Vector3f direction = {-50 + rand()%100 ,-50 + rand() % 100 , 0};
		direction = Normalize(direction);
		Cube.push_back(new CSolidCube(g_Renderer, position, direction, 100, 10, { 1,1,1,1 }));
	}

	


}

void CSceneMgr::ReleaseObjects()
{
	delete g_Renderer;
}

void CSceneMgr::Update(const double TimeElapsed)
{
	for (auto& elem : Cube) {
		
		elem->Update( TimeElapsed );
	}

	for (auto& elem : Cube) {

		elem->SetCollisioned(false);

		for (auto& elem_2 : Cube) {

			if (&elem == &elem_2)continue;

			if (elem->GetBoundingBox().isCollision(elem_2->GetBoundingBox()))
			{
				elem->SetCollisioned(true);
			}


		}

	}
}

void CSceneMgr::Render()
{
	for (auto& elem : Cube) {
		elem->Render();
	}
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
			Vector3f direction = { -50 + rand() % 100 ,-50 + rand() % 100 , 0 };
			direction = Normalize(direction);

			Cube.push_back(new CSolidCube(g_Renderer,
			{ x - CLIENT_WIDTH / 2,CLIENT_HEIGHT / 2 - y,0 },
			direction,
				150,
				10,
				{ 1,1,1,1 }));
		}

	}
}
