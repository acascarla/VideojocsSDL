#pragma once

#include "GameObject.h"
#include "ObjectLayer.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	void checkCollision(GameObject* gameObject, const std::vector<ObjectLayer*>* objectLayers);

private:
	static const int s_buffer = 15;
	static bool RectRect(SDL_Rect A, SDL_Rect B);
};