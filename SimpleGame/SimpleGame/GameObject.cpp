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

	m_life = 1;
	m_lifetime = 500;
}

CGameObject::~CGameObject()
{
}

bool CGameObject::LifeCheck()
{
	if (m_life <= 0) return true;
	if (m_lifetime <= 0) return true;
	return false;
}

bool CGameObject::Render()
{
	return false;
}

bool CGameObject::Update(float fTimeElapsed)
{
	return false;
}
