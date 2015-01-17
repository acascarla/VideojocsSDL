#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler()
{
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
	m_mousePosition = new Vector2D(0, 0);
}

InputHandler::~InputHandler() 
{
	
}
void InputHandler::update()
{
	// Captura l'estat del teclat
	state = SDL_GetKeyboardState(NULL);
	// Captura els events de ratolí
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			Game::Instance()->gameStop();
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			SDL_MouseButtonEvent mouse_event = event.button;
			if (mouse_event.button == SDL_BUTTON_LEFT){
				// AIXO SE QUE ES POT OPTIMITZAR 1 BILIO DE VEGADES MILLOR
				// PERO NO MACLARO AMB ELS PUNTERS, EL TEMA MEMORIA, ACCEDIRHI
				// Y SOBRETOT...NO ENTENC ELS ERRORS QUE DONA....AIXI FUNCIONA XD
				m_mouseButtonStates.clear();
				m_mouseButtonStates.push_back(true);
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(false);
			}
			if (mouse_event.button == SDL_BUTTON_MIDDLE){
				m_mouseButtonStates.clear();
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(true);
				m_mouseButtonStates.push_back(false);
			}
			if (mouse_event.button == SDL_BUTTON_RIGHT){
				m_mouseButtonStates.clear();
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(true);
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			SDL_MouseButtonEvent mouse_event = event.button;
			if (mouse_event.button == SDL_BUTTON_LEFT){
				m_mouseButtonStates.clear();
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(false);
			}
			if (mouse_event.button == SDL_BUTTON_MIDDLE){
				m_mouseButtonStates.clear();
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(false);
			}
			if (mouse_event.button == SDL_BUTTON_RIGHT){
				m_mouseButtonStates.clear();
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(false);
				m_mouseButtonStates.push_back(false);
			}
		}
		if (event.type == SDL_MOUSEMOTION) {
			m_mousePosition->setX(event.motion.x);
			m_mousePosition->setY(event.motion.y);
		}
	}
}
void InputHandler::clean()
{
	
}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (state[key]) {
		return true;
	}
	else{
		return false;
	}
}

bool InputHandler::getMouseButtonState(int buttonNumber){
	return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition()
{
	return m_mousePosition;
}