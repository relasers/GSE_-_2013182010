#pragma once
#include "stdafx.h"
#include "Renderer.h"
#include "PhysicVector.h"

#define LIFE_CHARACTER 10
#define LIFE_BUILDING 500
#define LIFE_BULLET 20
#define LIFE_ARROW 10

#define SPEED_CHARACTER 100
#define SPEED_BUILDING 0
#define SPEED_BULLET 300
#define SPEED_ARROW 100

#define SIZE_CHARACTER 10
#define SIZE_BUILDING 50
#define SIZE_BULLET 5
#define SIZE_ARROW 5

#define COLOR_CHARACTER {1,1,1,1}
#define COLOR_BUILDING {1,0.6942f,0.3978f,1}
#define COLOR_BULLET {1,0,0,1}
#define COLOR_ARROW {1,0,1,1}

enum class OBJECT_TYPE;

class CGameObject
{
protected:
	Renderer *m_Renderer = nullptr;
	Vector3f m_Position{0,0,0};
	Vector3f m_Direction{ 0,0,0 };

	float m_Speed{ 0 };
	float m_Size{0};
	Color m_Color{0,0,0,1};
	OBJECT_TYPE m_Type;

	float m_life{ 0 };
	float m_lifetime{ 0 };
public:
	CGameObject();
	CGameObject(Renderer *Renderer);
	CGameObject(Renderer *Renderer, Vector3f position, Vector3f direction, OBJECT_TYPE type);
	CGameObject(Renderer *Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color, OBJECT_TYPE type);
	~CGameObject();

	void SetPosition(Vector3f position) { m_Position = position; };
	void SetColor(Color color) { m_Color = color; };
	void SetSize(float size) { m_Size = size; }

	void SetLife(float life) { m_life = life; }
	float GetLife() const { return m_life; }
	Vector3f GetPosition() const { return m_Position; }
	bool LifeCheck();

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);
};