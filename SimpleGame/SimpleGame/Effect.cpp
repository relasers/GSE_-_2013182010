#include "stdafx.h"
#include "Effect.h"

CEffect::CEffect()
{
}

CEffect::CEffect(Renderer * Renderer)
{
	m_Renderer = Renderer;

	m_life = 1;
	m_lifetime = 5000;
	m_maxlife = 1;
	m_Size = 64;

	m_frametick = 0;
	m_maxframe = 16;
	m_RenderingLevel = 0.1;
}

CEffect::~CEffect()
{
}

bool CEffect::Render()
{
	m_Renderer->DrawTexturedRectSeq
	(m_Position.x, m_Position.y, m_Position.z,
		m_Size,1, 1, 1, 1, m_texCharacter,
		(int)m_frametick, 0, (int)m_maxframe, 1, m_RenderingLevel);


	return false;
}

bool CEffect::Update(float fTimeElapsed)
{
	m_frametick += fTimeElapsed * 20.3f;
	if (m_frametick > m_maxframe) m_life = 0;

	return true;
}
