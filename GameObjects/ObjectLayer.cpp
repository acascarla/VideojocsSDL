#include "ObjectLayer.h"
#include "Game.h"

ObjectLayer::ObjectLayer(){}
/*
ObjectLayer::ObjectLayer(const std::vector<std::string> &textureIDList) : m_textureIDList(textureIDList) {

}*/

void ObjectLayer::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void ObjectLayer::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw(Game::Instance()->getRenderer());
	}
}