#include "stdafx.h"
#include "SolidCube.h"

CSolidCube::CSolidCube()
{
}


CSolidCube::CSolidCube(Renderer * Renderer) : CGameObject(Renderer)
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
	return true;
}
