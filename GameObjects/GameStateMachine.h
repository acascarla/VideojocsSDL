#ifndef __GAME_STATE_MACHINE__
#define __GAME_STATE_MACHINE__


#include "GameState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"

class GameStateMachine
{
public:

	GameStateMachine();
	~GameStateMachine();
	void start();
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();
	void clear_VectorStatesDelete();
	
	GameState * currentGameState;
private:
	vector<GameState*> m_gameStates;
	vector<GameState*> m_statesToDelete;
};

#endif