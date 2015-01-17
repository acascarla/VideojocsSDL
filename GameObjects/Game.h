#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "GameObject.h"
#include "FelipPuig.h"
#include "Cranc.h"
#include "Cargol.h"
#include <vector>
#include <iostream>
#include "Vector2D.h"

#include "MenuState.h"

using namespace std;

class Game {
private:
	Game();
public:
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
		}
		return s_pInstance;
	}
	~Game();
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();
	void gameStop();
	SDL_Renderer* getRenderer() const { return SDLRenderer; }
	int getGameWidth() const{return m_gameWidth;}
	int getGameHeight() const{return m_gameHeight;}

	GameStateMachine* getStateMachine();
private:
	static Game* s_pInstance;
	GameStateMachine* GSM;
	SDL_Window* SDLWindow;
	SDL_Renderer *SDLRenderer;
	bool is_running = true;
	vector<GameObject*> gameObjects;

	int m_gameWidth;
	int m_gameHeight;
	
};

#endif
