#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"

enum class OBJECT_TYPE;
class GameObject;

class CSolidCube :public CGameObject {
private:
	BoundingBox m_boundingbox{ 0 };
	bool isCollisioned{ false };
public:
	CSolidCube();
	CSolidCube(Renderer* Renderer);
	CSolidCube(Renderer *Renderer, Vector3f position, Vector3f direction, OBJECT_TYPE type);
	CSolidCube(Renderer *Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color, OBJECT_TYPE type);
	~CSolidCube();

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);

	BoundingBox GetBoundingBox() const { return m_boundingbox; };

	void SetColor(Color color) { m_Color = color; }
	void SetCollisioned(bool collisioned) { isCollisioned = collisioned; }
	
	void SetPartTexturePtr(GLuint texture) { m_texParticle = texture; }
};