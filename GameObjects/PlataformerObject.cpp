#include "PlataformerObject.h"

PlataformerObject::PlataformerObject() {
	loadCollideTiles = false;
	m_gravity = 10;
	GameObject::setIsCollider(true);
	s_gameObjectID = "PlataformerObject";
}
PlataformerObject::~PlataformerObject(){

}
void PlataformerObject::load(LoaderParams* pParams){

}
void PlataformerObject::draw(){

}
void PlataformerObject::update(){
	/*Vector2D pedro;
	pedro.setX(2);
	pedro.setY(2);
	checkCollideTile(pedro);*/
}
void PlataformerObject::clean(){

}

bool PlataformerObject::checkCollideTile(Vector2D newPos)
{
	// Carregar els tiles de collisió només 1 cop
	if (!loadCollideTiles)
	{
		TileLayer* tileLayer;
		// 1. Comprobar alt i ample maxim dels tilelayers
		int max_width = 0;
		int max_height = 0;
		
		for (int i = 0; i < m_pCollisionLayers->size(); i++)
		{
			tileLayer = m_pCollisionLayers->at(i);
			if (tileLayer->m_numColumns > max_width) max_width = tileLayer->m_numColumns;
			if (tileLayer->m_numRows > max_height) max_height = tileLayer->m_numRows;
		}

		// 2. Omplir vector de tiles amb espais buits	
		vector<int> layerRow(max_width);
		for (int j = 0; j < max_height; j++)
		{
			vectorCollisionTiles.push_back(layerRow);
		}

		// 3. Igualar valors de TileIDs de les layers amb el vector de collisionTiles d'aqui
		for (int i = 0; i < m_pCollisionLayers->size(); i++)
		{
			tileLayer = m_pCollisionLayers->at(i);
			for (int rows = 0; rows < max_height; rows++)
			{
				for (int cols = 0; cols < max_width; cols++)
				{
					vectorCollisionTiles[rows][cols] = tileLayer->m_tileIDs[rows][cols];
				}
			}
		}
		loadCollideTiles = true;
	}
	// 1. Detecció del recuadre del personatge amb els marges (vec min i max format pixels)
	Vector2D pos_min;
	Vector2D pos_max;
	Vector2D vec_min;
	Vector2D vec_max;
	vec_min.setX(m_marginCollision);
	vec_min.setY(0);
	vec_max.setX(m_width-m_marginCollision);
	vec_max.setY(m_height);

	pos_min.setX(newPos.getX() + vec_min.getX());
	pos_min.setY(newPos.getY() + vec_min.getY());
	pos_max.setX(newPos.getX() + vec_max.getX());
	pos_max.setY(newPos.getY() + vec_max.getY());	// 2. Pasar vector anterior a vector amb les posicions dels tiles (format tiled, no pixel)
	int TileSize = 32;	Vector2D tileMin;	Vector2D tileMax;	int minX = pos_min.getX() / TileSize;	int minY = pos_min.getY() / TileSize;	int maxX = pos_max.getX() / TileSize;	int maxY = pos_max.getY() / TileSize;	tileMin.setX(minX);	tileMin.setY(minY);	tileMax.setX(maxX);	tileMax.setY(maxY);

	// 3. Doble bucle que recorre els tiles que esta tocant i mira si hi ha colisió
	for (int y = minY; y <= maxY; y++)
	{
		for (int x = minX; x <= maxX; x++)
		{
			if (vectorCollisionTiles[y][x] != 0)
			{
				return true;
			}
		}
	}
	// si no pilla colisió retorna false
	return false;
}