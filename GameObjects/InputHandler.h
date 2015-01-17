#pragma once

#include "SDL.h"
#include "Vector2D.h"
#include <vector>
#include <iostream>


using namespace std;

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
	~InputHandler();
	void update();
	void clean();

	bool isKeyDown(SDL_Scancode key);//Funcio per llegir "state" y saber si una tecla esta premuda
	bool getMouseButtonState(int buttonNumber); // Per saber quins botons del ratoli estan premuts
	Vector2D *getMousePosition(); // Per saber la posicio del ratoli

	

private:
	InputHandler();
	static InputHandler* s_pInstance;
	SDL_Event event;//Variable que guarda els events d'entrada a l'ordinador, els inputs	
	Vector2D *m_mousePosition;// Variable que conté la posició del ratolí
	vector<bool> m_mouseButtonStates;// Variable que conté l'estat dels buttons del ratolí, quins estan apretats

	const Uint8 *state;// Variable que guarda l'estat del teclat (quines tecles estan apretades)
	
};