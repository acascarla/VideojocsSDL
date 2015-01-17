#pragma once

#include "PlataformerObject.h"
class Cargol : public PlataformerObject
{
public:
	Cargol();
	void update();
	void clean();
	static GameObject * Create() { return new Cargol(); }
	virtual string type() { return s_gameObjectID; }
	virtual void onCollision(GameObject* other) {};
};

