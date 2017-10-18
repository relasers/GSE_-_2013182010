#pragma once
#include "stdafx.h"
#include "SolidCube.h"


class CSceneMgr
{
private:
	vector<CSolidCube*> Cube;
	Renderer *g_Renderer = NULL;
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

