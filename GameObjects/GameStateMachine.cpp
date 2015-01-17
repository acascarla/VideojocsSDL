#include "GameStateMachine.h"


GameStateMachine::GameStateMachine(){
	MenuState *menu = new MenuState();
	m_gameStates.push_back(menu);
	currentGameState = m_gameStates.back();
	currentGameState->onEnter();
}
GameStateMachine::~GameStateMachine(){

}


void GameStateMachine::start(){
	
}
void GameStateMachine::pushState(GameState* pState){
	m_gameStates.push_back(pState);
	pState->onEnter();
}
void GameStateMachine::changeState(GameState* pState){
	while(!m_gameStates.empty()){
		m_statesToDelete.push_back(m_gameStates.back());
		m_gameStates.pop_back();
	}
	m_gameStates.push_back(pState);
	pState->onEnter();
}
void GameStateMachine::popState(){
	m_statesToDelete.push_back(m_gameStates.back());
	m_gameStates.pop_back();
}
void GameStateMachine::update(){
	if (!m_gameStates.empty())
	{
		currentGameState = m_gameStates.back();
		currentGameState->update();
		clear_VectorStatesDelete();
	}
}
void GameStateMachine::render(){
	if (!m_gameStates.empty())
	{
		currentGameState->render();
	}
}

void GameStateMachine::clear_VectorStatesDelete(){
	//Borro primer els que tenen mes antiguitat
	while (!m_statesToDelete.empty()){
		m_statesToDelete.front()->onExit();
		m_statesToDelete.erase(m_statesToDelete.begin());
	}
}
