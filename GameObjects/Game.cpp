#include "Game.h"

Game* Game::s_pInstance = 0;

Game::Game(){}

Game::~Game()
{

}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	m_gameWidth = width;
	m_gameHeight = height;
	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		if (fullscreen) {
			SDLWindow = SDL_CreateWindow(title,
				xpos, ypos,
				width, height,
				SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else{
			SDLWindow = SDL_CreateWindow(title,
				xpos, ypos,
				width, height,
				SDL_WINDOW_SHOWN);
		}

		// if the window creation succeeded create our renderer
		if (SDLWindow != 0)
		{
			//initialize
			SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, 0);
			// Alpha as color values
			SDL_SetRenderDrawColor(SDLRenderer, 58, 176, 199, 255);

			// CREAR GameStateMachine
			GSM = new GameStateMachine();

			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}void Game::handleEvents()
{
	// Captura d'events
	InputHandler::Instance()->update();
}

void Game::update()
{
	GSM->update();
}

void Game::render()
{
	// Netejar tot el que hi hagi
	SDL_RenderClear(SDLRenderer);

	GSM->render();

	// show the window
	SDL_RenderPresent(SDLRenderer);
}

void Game::clean()
{
	SDL_DestroyWindow(SDLWindow);
	SDL_DestroyRenderer(SDLRenderer);
	SDL_Quit();
}

bool Game::isRunning()
{
	return is_running;
}

GameStateMachine* Game::getStateMachine()
{
	return GSM;
}


void Game::gameStop()
{
	is_running = false;
}
