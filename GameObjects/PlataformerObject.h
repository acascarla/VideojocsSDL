#pragma once

#include "GameObject.h"
#include "TileLayer.h"

class PlataformerObject : public GameObject
{
public:
	PlataformerObject();
	virtual ~PlataformerObject();
	virtual void load(LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual string type() { return s_gameObjectID; }
	virtual void onCollision(GameObject* other) {};
protected:
	bool checkCollideTile(Vector2D newPos);
	int m_marginCollision;
	int m_gravity;
	bool loadCollideTiles;
};