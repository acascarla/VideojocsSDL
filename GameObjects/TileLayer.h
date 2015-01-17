#pragma once

#include "Layer.h"
#include "Vector2D.h"
#include <vector>
#include <iostream>
#include "tileset.h"

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, const std::vector<Tileset> &tilesets);
	virtual void update();
	virtual void render();

	void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data;}
	void setTileSize(int tileSize){m_tileSize = tileSize;}
	Tileset getTilesetByID(int tileID);
	std::vector<std::vector<int>> getTilesVector(){ return m_tileIDs; }

	void setIsCollider(bool isCollider){ m_isCollider = isCollider; }
	bool IsCollider() { return m_isCollider; }

	int m_numColumns;
	int m_numRows;
	int m_tileSize;
	std::vector<std::vector<int>> m_tileIDs;

private:

	Vector2D m_position;

	const std::vector<Tileset> &m_tilesets;

	bool m_isCollider;
};