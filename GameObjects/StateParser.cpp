#include "StateParser.h"
#include "tinyxml.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"
#include "Game.h"
#include "LoaderParams.h"


bool StateParser::parseState(const char *stateFile, string stateID, vector<GameObject *>* pObjects, 
	std::vector<std::string> *pTextureIDs)
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile(stateFile))
	{
		cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	TiXmlElement* pStateRoot = 0;
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
		e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;
		}
	}

	TiXmlElement* pTextureRoot = 0;
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("TEXTURES"))
		{
			pTextureRoot = e;
			string p = e->Value();
		}
	}
	parseTextures(pTextureRoot, pTextureIDs);


	TiXmlElement* pObjectRoot = 0;
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("GAMEOBJECTS"))
		{
			pObjectRoot = e;
			string p = e->Value();
		}
	}
	parseObjects(pObjectRoot, pObjects);
	return true;
}void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=NULL; e = e->NextSiblingElement())
	{
		string filenameAttribute = e->Attribute("filename");
		string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute);
		TextureManager::Instance()->load(filenameAttribute,idAttribute, Game::Instance()->getRenderer());
	}
}




void StateParser::parseObjects(TiXmlElement *pStateRoot,
	std::vector<GameObject *>* pObjects)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=NULL; e = e->NextSiblingElement())
	{
		// TODO: ANIMSPEED SE PARSEA A INT, HAY QUE PARSEARLO A FLOAT
		int x, y, width, height, numFrames, callbackID, animSpeed;
		string textureID;
		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);
		textureID = e->Attribute("textureID");
		
		GameObject* pGameObject;
		pGameObject = GameObjectFactory::Instance()->CreateGameObject(e->Attribute("type"));
		pGameObject->load(new LoaderParams(x, y, width, height, textureID, callbackID, numFrames, animSpeed));
		pObjects->push_back(pGameObject);
	}
}