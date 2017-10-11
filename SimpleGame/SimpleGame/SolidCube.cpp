#include "stdafx.h"
#include "SolidCube.h"

CSolidCube::CSolidCube()
{
}


CSolidCube::CSolidCube(Renderer * Renderer) : CGameObject(Renderer)
{
}

CSolidCube::CSolidCube(Renderer * Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color) 
	: CGameObject(Renderer,position,direction,speed,size,color)
{
}

CSolidCube::~CSolidCube()
{
}

bool CSolidCube::Render()
{

	m_Renderer->DrawSolidRect(m_Position.x, m_Position.y, m_Position.z, m_Size, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	return true;
}

bool CSolidCube::Update(float fTimeElapsed)
{
	m_Position += m_Direction*m_Speed*fTimeElapsed;

	if (m_Position.x < -CLIENT_WIDTH/2) 
		{ 
		m_Direction.x *= -1; 
		m_Position.x = -CLIENT_WIDTH / 2;
	}
	if (m_Position.x > CLIENT_WIDTH/2) 
		{ 
		m_Direction.x *= -1; 
		m_Position.x = CLIENT_WIDTH/2;
	}
	if (m_Position.y < -CLIENT_HEIGHT / 2)
		{ 
		m_Direction.y *= -1; 
		m_Position.y = -CLIENT_HEIGHT / 2;
	}
	if (m_Position.y > CLIENT_HEIGHT/2) 
		{ 
		m_Direction.y *= -1; 
		m_Position.y = CLIENT_HEIGHT / 2;
	}
	return true;
}
