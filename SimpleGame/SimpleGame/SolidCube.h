#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"

class CSolidCube :public CGameObject {
private:

public:
	CSolidCube();
	CSolidCube(Renderer* Renderer);
	CSolidCube(Renderer *Renderer, Vector3f position, Vector3f direction, float speed, float size, Color color);
	~CSolidCube();

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);
};