#include "Cargol.h"

Cargol::Cargol()
{
	s_gameObjectID = "Cargol";
}

void Cargol::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 4));

	if (posicio.getX() >= 535){
		m_final = false;

	}
	else if (posicio.getX() <= 390){
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

void Cargol::clean()
{

}