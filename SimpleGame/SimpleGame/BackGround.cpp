#include "stdafx.h"
#include "BackGround.h"

CBackGround::CBackGround()
{
}

CBackGround::CBackGround(Renderer * Renderer)
{
	m_Renderer = Renderer;

	m_life = 1;
	m_maxlife = 1;

	m_RenderingLevel = 0.0;
}

CBackGround::CBackGround(Renderer * Renderer, Vector3f position, float width, float height, Color color)
{
	m_Renderer = Renderer;
	m_Position = position;
	m_Color = color;

	m_Size.x = width;
	m_Size.y = height;

	m_life = 1;
	m_maxlife = 1;

	m_RenderingLevel = 0.9;
}

CBackGround::~CBackGround()
{
}

bool CBackGround::Render()
{
	// 일단 긴 세로를 이용하여 그리자.
	m_Renderer->DrawTexturedRect(m_Position.x, m_Position.y, m_Position.z,
		m_Size.y, m_Color.r, m_Color.g, m_Color.b, m_Color.a, m_texCharacter, m_RenderingLevel);

	return true;
}

bool CBackGround::Update(float fTimeElapsed)
{
	return false;
}

CClimate::CClimate()
{
}

CClimate::CClimate(Renderer * Renderer)
{
	m_Renderer = Renderer;

	m_life = 1;
	m_maxlife = 1;

	m_RenderingLevel = 0.1;
}

CClimate::CClimate(Renderer * Renderer, Vector3f position, float size,  Color color)
{
	m_Renderer = Renderer;
	m_Position = position;
	m_Color = color;

	m_Size = size;

	m_life = 1;
	m_maxlife = 1;

	m_RenderingLevel = 0.1;
}

CClimate::~CClimate()
{
}

bool CClimate::Render()
{

	m_Renderer->DrawParticleClimate(m_Position.x, m_Position.y, m_Position.z,
		m_Size, m_Color.r, m_Color.g, m_Color.b, m_Color.a, 0, -1, m_texCharacter, m_climatetick,m_RenderingLevel);
	return true;
}

bool CClimate::Update(float fTimeElapsed)
{
	m_climatetick += fTimeElapsed;
	return true;
}
