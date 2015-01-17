#include "PlayState.h"
#include "Game.h"
#include "StateParser.h"
#include "LevelParser.h"

const string PlayState::s_menuID = "PLAY";

void PlayState::update(){
	pLevel->update();
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for each (GameObject *GO in m_gameObjects)
	{
		GO->update(); 
	}

}
void PlayState::render(){
	pLevel->render();
	for each (GameObject *GO in m_gameObjects)
	{
		GO->draw(Game::Instance()->getRenderer());
	}
}
bool PlayState::onEnter(){
	
	StateParser stateParser;
	stateParser.parseState("../data/xmldata.xml", s_menuID, &m_gameObjects, &m_TextureIDs);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("../data/level1.tmx");
	
	m_callbacks.push_back(0);
	setCallbacks();

	return true;
}
bool PlayState::onExit(){
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

void PlayState::s_pause(){

}

void PlayState::setCallbacks()
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