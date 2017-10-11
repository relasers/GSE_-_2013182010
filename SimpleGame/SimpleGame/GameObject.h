#include "stdafx.h"
#include "Renderer.h"
#include "PhysicVector.h"


class CGameObject
{
protected:
	Renderer *m_Renderer = nullptr;
	Vector3f m_Position{0,0,0};
	Vector3f m_Direction{ 0,0,0 };
	float m_Speed{ 0 };
	float m_Size{0};
	Color m_Color{0,0,0,1};

public:
	CGameObject();
	CGameObject(Renderer *Renderer);
	CGameObject(Renderer *Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color);
	~CGameObject();

	void SetPosition(Vector3f position) { m_Position = position; };
	void SetColor(Color color) { m_Color = color; };
	void SetSize(float size) { m_Size = size; }

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);
};