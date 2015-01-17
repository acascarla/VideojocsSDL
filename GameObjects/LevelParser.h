#pragma once

#include "Level.h"
#include "tinyxml.h"
#include <vector>
#include <iostream>

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);
private:
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, std::vector<TileLayer*> *pCollisionLayers, const std::vector<Tileset>* pTilesets);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, std::vector<ObjectLayer*> *pObjectLayers, std::vector<TileLayer*> *pCollisionLayers, Level* pLevel);
	int m_tileSize;
	int m_width;
	int m_height;
};
