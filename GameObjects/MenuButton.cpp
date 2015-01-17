#include "MenuButton.h"
#include "Game.h"


MenuButton::MenuButton(void(*callback)()) :m_callback(callback)
{
	m_currentRow = 1;
	s_gameObjectID = "MenuButton";
}

MenuButton::MenuButton(){
	m_currentRow = 1;
	s_gameObjectID = "MenuButton";
}

void MenuButton::load(LoaderParams *loadParams){
	GameObject::load(loadParams);
	m_currentRow = 1;
	m_final = true;
}

void MenuButton::draw(){
	TextureManager::Instance()->drawFrame(m_textureID, posicio.getX(), posicio.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), flip);
}
void MenuButton::update(){
	Vector2D* posicioMouseActual = InputHandler::Instance()->getMousePosition();
	
	if (posicioMouseActual->getX() < (posicio.getX() + m_width) && posicioMouseActual->getX() > posicio.getX() && posicioMouseActual->getY() < (posicio.getY() + m_height) && posicioMouseActual->getY() > posicio.getY())
	{
		if (InputHandler::Instance()->getMouseButtonState(LEFT)
			&& m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_callback();
			m_bReleased = false;
		}
		else if (!InputHandler::Instance()
			->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
};
void MenuButton::clean(){};



