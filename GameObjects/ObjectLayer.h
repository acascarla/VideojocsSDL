#pragma once
#include "Layer.h"
#include "GameObject.h"
#include <vector>

class ObjectLayer : public Layer
{
public:
	ObjectLayer();
	virtual void update();
	virtual void render();
	std::vector<GameObject*>* getGameObjects()
	{
		return &m_gameObjects;
	}
private:
	std::vector<GameObject*> m_gameObjects;
};