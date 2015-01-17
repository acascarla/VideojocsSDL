#include "GameObjectFactory.h"

#include "MenuButton.h"
#include "FelipPuig.h"
#include "Cranc.h"
#include "Cargol.h"

GameObjectFactory* GameObjectFactory::s_pInstance = 0;

GameObjectFactory::GameObjectFactory(void){
	Register("MenuButton", &MenuButton::Create);
	Register("FelipPuig", &FelipPuig::Create);
	Register("Cranc", &Cranc::Create);
	Register("Cargol", &Cargol::Create);
}

GameObjectFactory::~GameObjectFactory(void){

}

void GameObjectFactory::Register(const std::string & gameObjectName, CreateGameObjectFn pCreate){
	m_FactoryMap[gameObjectName] = pCreate;
}
GameObject* GameObjectFactory::CreateGameObject(const std::string & gameObjectName){
	//GameObject *go = (*m_FactoryMap[gameObjectName])();
	return m_FactoryMap[gameObjectName]();
	//return go;
}