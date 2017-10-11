#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
{
}

CGameObject::CGameObject(Renderer * Renderer)
{
	m_Renderer = Renderer;
}

CGameObject::CGameObject(Renderer * Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color)
{
	m_Renderer = Renderer;
	m_Position = position;
	m_Direction = direction;
	m_Speed = speed;
	m_Size = size;
	m_Color = color;
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
