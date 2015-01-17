#include "Cranc.h"

Cranc::Cranc()
{
	s_gameObjectID = "Cranc";
}

void Cranc::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 3));

	if (posicio.getX() >= 610){
		m_final = false;

	}
	else if (posicio.getX() <= 570){
		m_final = true;
	}
	if (m_final){
		posicio.setX(posicio.getX() + velocitat.getX());
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (m_final == false){
		posicio.setX(posicio.getX() - velocitat.getX());
		flip = SDL_FLIP_NONE;
	}
	// Actualizar Rect
	m_pBoundingBox.x = posicio.getX();
	m_pBoundingBox.y = posicio.getY();
	m_pBoundingBox.h = m_height;
	m_pBoundingBox.w = m_width;
}
void Cranc::clean()
{

}
