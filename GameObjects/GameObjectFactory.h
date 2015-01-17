#pragma once

#include "GameObject.h"
#include <iostream>

#define TheGameObjectFactory GameObjectFactory::Instance()

typedef GameObject* (*CreateGameObjectFn)();

class GameObjectFactory
{
public:
	virtual ~GameObjectFactory(void);
	static GameObjectFactory* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new GameObjectFactory();
		}
		return s_pInstance;
	}
	void Register(const std::string & gameObjectName, CreateGameObjectFn pCreate);
	GameObject* CreateGameObject(const std::string & gameObjectName);
private:
	GameObjectFactory(void);
	static GameObjectFactory* s_pInstance;
	std::map< std::string, CreateGameObjectFn > m_FactoryMap;
};