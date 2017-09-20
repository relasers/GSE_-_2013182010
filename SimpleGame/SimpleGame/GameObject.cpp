#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
{
}

CGameObject::CGameObject(Renderer * Renderer)
{
	m_Renderer = Renderer;
}

CGameObject::~CGameObject()
{
}

bool CGameObject::Render()
{
	return false;
}

bool CGameObject::Update(float fTimeElapsed)
{
	return false;
}
