#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
{
}

CGameObject::CGameObject(Renderer * Renderer)
{
	m_Renderer = Renderer;
}

CGameObject::CGameObject(Renderer * Renderer, Vector3f position, Vector3f direction, OBJECT_TYPE type)
{
	m_Renderer = Renderer;
	m_Position = position;
	m_Direction = direction;
	m_Type = type;
	m_lifetime = 5000;

	switch (m_Type)
	{
	case OBJECT_TYPE::OBJECT_CHARACTER:
		m_life = LIFE_CHARACTER;
		m_Size = SIZE_CHARACTER;
		m_Speed = SPEED_CHARACTER;
		m_Color = COLOR_CHARACTER;
		break;
	case OBJECT_TYPE::OBJECT_BUILDING:
		m_life = LIFE_BUILDING;
		m_Size = SIZE_BUILDING;
		m_Speed = SPEED_BUILDING;
		m_Color = COLOR_BUILDING;
		m_texCharacter = m_Renderer->CreatePngTexture("Textures/Building.png");
		break;
	case OBJECT_TYPE::OBJECT_ARROW:
		m_life = LIFE_ARROW;
		m_Size = SIZE_ARROW;
		m_Speed = SPEED_ARROW;
		m_Color = COLOR_ARROW;
		break;
	case OBJECT_TYPE::OBJECT_BULLET:
		m_life = LIFE_BULLET;
		m_Size = SIZE_BULLET;
		m_Speed = SPEED_BULLET;
		m_Color = COLOR_BULLET;
		break;
	}
}

CGameObject::CGameObject(Renderer * Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color, OBJECT_TYPE type)
{
	m_Renderer = Renderer;
	m_Position = position;
	m_Direction = direction;
	m_Speed = speed;
	m_Size = size;
	m_Color = color;

	m_life = 500;
	m_lifetime = 5000;
}

CGameObject::~CGameObject()
{
}

bool CGameObject::LifeCheck()
{
	
	if (m_Type == OBJECT_TYPE::OBJECT_ARROW)
	{
		if (!m_parent) return true;
	}

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
