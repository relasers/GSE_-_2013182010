#pragma once
#include "stdafx.h"
#include "SolidCube.h"



class CSolidCube;

class CSceneMgr
{
private:
	vector<CSolidCube*> Character;
	vector<CSolidCube*> Building;
	vector<CSolidCube*> Bullet;
	vector<CSolidCube*> Arrow;

	Renderer *g_Renderer = NULL;

	float placement_tick = 0; // À¯´Ö ¹èÄ¡ ´ë±â Æ½
	float tick = 0;
	float counter = 0;
public:
	CSceneMgr();
	~CSceneMgr();

	void Initialize();
	void BuildObjects();
	void ReleaseObjects();

	void Update(const double TimeElapsed);
	void Render();

	void Input_Key(unsigned char key, int x, int y);
	void Input_SpecialKey(int key, int x, int y);
	void Input_MouseButton(int button, int state, int x, int y);
};

