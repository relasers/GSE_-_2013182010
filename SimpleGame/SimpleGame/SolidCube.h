#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"

class CSolidCube :public CGameObject {
private:

public:
	CSolidCube();
	CSolidCube(Renderer* Renderer);
	~CSolidCube();

	virtual bool Render();
	virtual bool Update(float fTimeElapsed);
};