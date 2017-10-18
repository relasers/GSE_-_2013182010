#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"

class CSolidCube :public CGameObject {
private:
	BoundingBox m_boundingbox{ 0 };
	bool isCollisioned{ false };
public:
	CSolidCube();
	CSolidCube(Renderer* Renderer);
	CSolidCube(Renderer *Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color);
	~CSolidCube();

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);

	BoundingBox GetBoundingBox() const { return m_boundingbox; };

	void SetColor(Color color) { m_Color = color; }
	void SetCollisioned(bool collisioned) { isCollisioned = collisioned; }
};