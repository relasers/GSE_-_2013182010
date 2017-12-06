#include "stdafx.h"
#include "SolidCube.h"

CSolidCube::CSolidCube() : CGameObject()
{
}


CSolidCube::CSolidCube(Renderer * Renderer) : CGameObject(Renderer)
{
}

CSolidCube::CSolidCube(Renderer * Renderer, Vector3f position, Vector3f direction, OBJECT_TYPE type)
	: CGameObject(Renderer, position, direction, type)
{

	
}

CSolidCube::CSolidCube(Renderer * Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color, OBJECT_TYPE type)
	: CGameObject(Renderer, position, direction, speed, size, color, type)
{
}

CSolidCube::~CSolidCube()
{
}

bool CSolidCube::Render()
{

	//if (isCollisioned) SetColor({1,0,0,0});
	//else SetColor({1,1,1,1});
	if (m_Type == OBJECT_TYPE::OBJECT_BUILDING || m_Type == OBJECT_TYPE::OBJECT_CHARACTER )
	{
		// 체력과 최대 체력사이 범위를 0과 1 사이로 정규화
		// m_Position.y + m_Size*1.2 -> 캐릭터 상단에 체력바가 위치할 수 있도록
		float guage = (m_life) / (m_maxlife);
		m_Renderer->DrawSolidRectGauge(m_Position.x, m_Position.y + m_Size, m_Position.z, 
			m_Size*1.2, 5, m_Color.r, m_Color.g, m_Color.b, m_Color.a, guage, m_RenderingLevel);

		string remain_guage = to_string((int)m_life);

		m_Renderer->DrawSolidText(m_Position.x, m_Position.y + m_Size, GLUT_BITMAP_9_BY_15,
			1,1,1, (char*)remain_guage.c_str());

		//m_Renderer->DrawSolidText(m_Position.x, m_Position.y + m_Size, GLUT_BITMAP_HELVETICA_10,
		//	1,1,1, "100");

	}

	if (m_Type == OBJECT_TYPE::OBJECT_BULLET)
	{
		m_Renderer->DrawParticle(m_Position.x, m_Position.y, m_Position.z, 
			m_Size, m_Color.r, m_Color.g, m_Color.b, m_Color.a
			, -m_Direction.x, -m_Direction.y, m_texParticle, m_particletick);

	}
	

	if (m_Type == OBJECT_TYPE::OBJECT_BUILDING || m_Type == OBJECT_TYPE::OBJECT_CHARACTER)
	{
		//m_Renderer->DrawTexturedRect(m_Position.x, m_Position.y, m_Position.z, 
		//	m_Size, m_Color.r, m_Color.g, m_Color.b, m_Color.a, m_texCharacter, m_RenderingLevel);

		m_Renderer->DrawTexturedRectSeq(m_Position.x, m_Position.y, m_Position.z,
			m_Size, m_Color.r, m_Color.g, m_Color.b, m_Color.a, m_texCharacter,(int)m_frametick,0, (int)m_maxframe,1, m_RenderingLevel);
		
	}
	else
	m_Renderer->DrawSolidRect(m_Position.x, m_Position.y, m_Position.z, m_Size, m_Color.r, m_Color.g, m_Color.b, m_Color.a, m_RenderingLevel);
	return true;
}

bool CSolidCube::Update(float fTimeElapsed)
{
	//m_life -= 1.f;
	//m_lifetime -= 1.f;
	
	m_frametick += fTimeElapsed*10.3f;
	if (m_frametick > m_maxframe) m_frametick - m_maxframe;

	m_particletick += fTimeElapsed;

	m_shootTimer += fTimeElapsed;
	m_Position += m_Direction*m_Speed*fTimeElapsed;

	// 오브젝트 타입이 화살이거나, 총알이면 화면 밖에 닿으면 라이프를 제로로 만들어
	// 화면 밖을 나가서 사라지는 것처럼 보이도록
	if (m_Type == OBJECT_TYPE::OBJECT_ARROW || m_Type == OBJECT_TYPE::OBJECT_BULLET)
	{
		if (m_Position.x < -CLIENT_WIDTH / 2) m_life = 0;
		if (m_Position.x > CLIENT_WIDTH / 2) m_life = 0;
		if (m_Position.y < -CLIENT_HEIGHT / 2) m_life = 0;
		if (m_Position.y > CLIENT_HEIGHT / 2) m_life = 0;
	}
	// 아니면 화면 안에 계속 있을 수 있도록 반사
	else 
	{
		if (m_Position.x < -CLIENT_WIDTH / 2)
		{
			m_Direction.x *= -1;
			m_Position.x = -CLIENT_WIDTH / 2;
		}
		if (m_Position.x > CLIENT_WIDTH / 2)
		{
			m_Direction.x *= -1;
			m_Position.x = CLIENT_WIDTH / 2;
		}
		if (m_Position.y < -CLIENT_HEIGHT / 2)
		{
			m_Direction.y *= -1;
			m_Position.y = -CLIENT_HEIGHT / 2;
		}
		if (m_Position.y > CLIENT_HEIGHT / 2)
		{
			m_Direction.y *= -1;
			m_Position.y = CLIENT_HEIGHT / 2;
		}
	}
	

	m_boundingbox.left = m_Position.x - m_Size*0.5;
	m_boundingbox.right = m_Position.x + m_Size*0.5;
	m_boundingbox.top = m_Position.y + m_Size*0.5;
	m_boundingbox.bottom = m_Position.y - m_Size*0.5;

	return true;
}
