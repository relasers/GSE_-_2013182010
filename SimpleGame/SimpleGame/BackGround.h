#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"

class CBackGround :public CGameObject {


private:

	Vector2f m_Size;

public:
	CBackGround();
	CBackGround(Renderer* Renderer);
	CBackGround(Renderer *Renderer, Vector3f position, float width,float height, Color color);
	~CBackGround();

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);

};