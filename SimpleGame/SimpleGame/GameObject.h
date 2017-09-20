#include "stdafx.h"
#include "Renderer.h"
#include "PhysicVector.h"


class CGameObject
{
protected:
	Renderer *m_Renderer = nullptr;
	Vector3f m_Position{0,0,0};

	float m_Size{0};
	Color m_Color{1,0,0,0};

public:
	CGameObject();
	CGameObject(Renderer *Renderer);
	~CGameObject();

	void SetPosition(Vector3f position) { m_Position = position; };
	void SetColor(Color color) { m_Color = color; };
	void SetSize(float size) { m_Size = size; }

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);
};