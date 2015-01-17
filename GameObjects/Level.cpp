#include "Level.h"
#include "TileLayer.h"
#include "CollisionManager.h"

void Level::render()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}
void Level::update()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update();
	}
	m_CollisionManager->checkCollision(getPlayer(), getObjectLayers());
}

void Level::setPlayer(FelipPuig* pPlayer)
{
	m_pPlayer = pPlayer;
}

