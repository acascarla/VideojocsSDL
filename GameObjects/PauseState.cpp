#include "PauseState.h"
#include "Game.h"
#include "StateParser.h"

const string PauseState::s_menuID = "PAUSE";

void PauseState::update(){
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void PauseState::render(){
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw(Game::Instance()->getRenderer());
	}
}
bool PauseState::onEnter(){
	StateParser stateParser;
	stateParser.parseState("../data/xmldata.xml", s_menuID, &m_gameObjects, &m_TextureIDs);
	
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_resume);
	m_callbacks.push_back(s_returnMainMenu);

	setCallbacks();
	return true;
}
bool PauseState::onExit(){
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	for (int i = 0; i < m_TextureIDs.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_TextureIDs[i]);
	}
	m_TextureIDs.clear();

	return true;
}

void PauseState::s_resume(){
	Game::Instance()->getStateMachine()->popState();
}

void PauseState::s_returnMainMenu(){
	Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::setCallbacks()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(m_callbacks[pButton->getCallbackID()]);
		}
	}
}