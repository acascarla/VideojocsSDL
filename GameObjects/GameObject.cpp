#include "GameObject.h"

GameObject::GameObject()
{
	m_currentRow = 1;
	m_isCollider = false;
	s_gameObjectID = "GameObject";
}
GameObject::~GameObject()
{

}
void GameObject::load(LoaderParams *loadParams)
{
	m_textureID = loadParams->getTextureID();
	m_callbackID = loadParams->getCallbackID();
	m_width = loadParams->getWidth();
	m_height = loadParams->getHeight();
	posicio.setX(loadParams->getX());
	posicio.setY(loadParams->getY());
	m_numFrames = loadParams->getNumFrames();
	velocitat.setX(loadParams->getVelocitat());
	m_currentFrame = 0;
	m_currentRow = 1;
	m_final = true;
	if (loadParams->getCollisionLayers())
	{
		m_pCollisionLayers = loadParams->getCollisionLayers();
	}
	m_pBoundingBox.x = loadParams->getX();
	m_pBoundingBox.y = loadParams->getY();
	m_pBoundingBox.w = loadParams->getWidth();
	m_pBoundingBox.h = loadParams->getHeight();
}
void GameObject::update()
{
	
}
void GameObject::draw(SDL_Renderer* pRender)
{
}
void GameObject::clean()
{

}