#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"


class CEffect :public CGameObject {

public:
	CEffect();
	CEffect(Renderer* Renderer);
	~CEffect();

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);

};