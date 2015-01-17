#pragma once

#include <iostream>
#include <vector>
#include "Layer.h"
#include "TileLayer.h"
#include "tileset.h"
#include "ObjectLayer.h"
#include "FelipPuig.h"
#include "CollisionManager.h"

using namespace std;

class Level
{
public:
	~Level() {}
	void update();
	void render(); 
	vector<Tileset>* getTilesets(){return &m_tilesets;}
	vector<Layer*>* getLayers(){return &m_layers;}
	vector<string>* getTextureIDList() { return &m_textureIDList; }
	vector<TileLayer*>* getCollisionLayers(){ return &m_CollisionLayers; }	vector<ObjectLayer*>* getObjectLayers(){ return &m_ObjectLayers; }

	FelipPuig* getPlayer() { return m_pPlayer; }
	void setPlayer(FelipPuig* pPlayer);

private:
	friend class LevelParser;
	FelipPuig* m_pPlayer;
	Level(){};

	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
	std::vector<std::string> m_textureIDList;

	std::vector<TileLayer*> m_CollisionLayers;
	std::vector<ObjectLayer*> m_ObjectLayers;
	CollisionManager* m_CollisionManager;
};