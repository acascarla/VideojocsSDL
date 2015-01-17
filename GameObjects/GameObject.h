#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "SDL.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Vector2D.h"
#include <iostream>
#include "LoaderParams.h"

using namespace std;

class GameObject {
public:
	void load(LoaderParams* loadParams);
	void clean();	void draw(SDL_Renderer* pRender);
	virtual void update();

	std::string m_textureID;
	int m_callbackID;
	int m_width;
	int m_height;
	int m_currentFrame;
	int m_currentRow;
	int m_final;
	int m_numFrames;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	Vector2D posicio;
	Vector2D velocitat;
	Vector2D acceleracio;

	SDL_Rect m_pBoundingBox;
	bool m_isCollider;	string s_gameObjectID;	std::vector< TileLayer* >* m_pCollisionLayers;
	vector <vector<int>> vectorCollisionTiles;
	SDL_Rect getBoundingBox() { return m_pBoundingBox; }
	bool isCollider();
	void setIsCollider(bool isCollider) { m_isCollider = isCollider; }
	virtual void onCollision(GameObject* other) {};
	virtual string type() { return s_gameObjectID; }
protected:
	GameObject();
	virtual ~GameObject();
};

#endif