#include "MenuState.h"
#include "MenuButton.h"
#include "Game.h"
#include "StateParser.h"

const string MenuState::s_menuID = "MENU";

//typedef void(*Callbacks)();


void MenuState::update(){
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}
void MenuState::render(){
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw(Game::Instance()->getRenderer());
	}
}
bool MenuState::onEnter(){
	StateParser stateParser;
	stateParser.parseState("../data/xmldata.xml", s_menuID, &m_gameObjects, &m_TextureIDs);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	setCallbacks();

	return true;
}
bool MenuState::onExit(){

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
void MenuState::s_menuToPlay(){
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}
void MenuState::s_exitFromMenu(){
	Game::Instance()->gameStop();
}



void MenuState::setCallbacks()
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