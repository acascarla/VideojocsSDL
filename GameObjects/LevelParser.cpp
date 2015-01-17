#include "LevelParser.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "zlib.h"
#include "base64.h"

Level* LevelParser::parseLevel(const char *levelFile)
{
	// Obrim el document
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);
	// Creem el level que tornarem al State
	Level* pLevel = new Level();
	// Agafem el primer element
	TiXmlElement* pRoot = levelDocument.RootElement(); 
	// I guardem el tamany del tileset i de cada tile
	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);
	// recorrem tots els childs i comprovem que siguin "tileset", si ho son passem l'element a la funcio parseTileset
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}
	// the same pero amb les layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			parseTileLayer(e, pLevel->getLayers(), pLevel->getCollisionLayers(), pLevel->getTilesets());
		}
	}
	// parse any object layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers(), pLevel->getObjectLayers(), pLevel->getCollisionLayers(), pLevel);
			}
		}
	}
	return pLevel; //rotrna level al State
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	// Load del tileset al texturemanager
	TextureManager::Instance()->load(pTilesetRoot ->FirstChildElement()->Attribute("source"), pTilesetRoot ->Attribute("name"), Game::Instance()->getRenderer());
	// nou tileset (struct) per guardar les dades
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width",&tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height",&tileset.height);
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
	pTilesets->push_back(tileset); // add al vector de tilesets del Level
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, std::vector<TileLayer*> *pCollisionLayers, const std::vector<Tileset>*pTilesets)
{
	// variable per si es collision
	int isCollision = 0;
	// create nova TileLayer
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
	// crear vector 2d
	std::vector<std::vector<int>> data;
	std::string decodedIDs; //string per el node amb la data del tiled
	TiXmlElement* pDataNode =0; // element que conte la data del tiled
	TiXmlElement* pPropertyNode = 0; // element que conte la propietat collision
	// get element que conte la info del mapeig
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	// Saber si la capa es collision o no
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* property = e->FirstChildElement();
				property != NULL; property = property->NextSiblingElement())
			{
				if (property->Value() == std::string("property"))
				{
					if (property->Attribute("name") == std::string("collision"))
					{
						property->Attribute("value", &isCollision);
					}
				}
			}
		}
	}


	// DATA

	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();// pasaru a text
		std::string t = text->Value(); // amb value es passa a string
		decodedIDs = base64_decode(t); //decode
	}

	// Descomprimir
	uLongf numGids = m_width * m_height * sizeof(int); 
	std::vector<unsigned> gids(numGids);
	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());
	// omplir de vectors buits el vector 2d
	std::vector<int> layerRow(m_width);
	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}
	// Passar la info descomprimida al vector 2d
	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = gids[rows * m_width + cols];
		}
	}
	//Passar el vector2d al TileLayer
	pTileLayer->setTileIDs(data);
	// Ficar si es collision o no
	if (isCollision)
	{
		pTileLayer->setIsCollider(isCollision);
		pCollisionLayers->push_back(pTileLayer);
	}
	//Passar el TileLayer al vector de Layers del level
	pLayers->push_back(pTileLayer);
}


void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, std::vector<ObjectLayer*> *pObjectLayers, std::vector<TileLayer*> *pCollisionLayers, Level* pLevel)
{
	// variable per saber si es el player o no
	int isPlayer = 0;
	// Variable per guardar el player
	FelipPuig* Player;
	// create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();
	//std::cout << pObjectElement->FirstChildElement()->Value();
	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e !=NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("object"))
		{
			int animSpeed, x, y, width, height, numFrames, callbackID;
			std::string textureID;
			// get the initial node values type, x and y
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			
			GameObject* pGameObject = GameObjectFactory::Instance()->CreateGameObject(e->Attribute("name"));
			// get the property values
			
			for (TiXmlElement* properties = e->FirstChildElement();
				properties != NULL; properties = properties ->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* property = properties ->FirstChildElement(); property != NULL; property = property ->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames"))
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Attribute("name") == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Attribute("name") == std::string("height"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == std::string("width"))
							{
								property->Attribute("value", &width);
							}
							else if (property->Attribute("name") == std::string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}
							else if (property->Attribute("name") == std::string("animSpeed"))
							{
								property->Attribute("value", &animSpeed);
							}
							else if (property->Attribute("name") == std::string("isPlayer"))
							{
								property->Attribute("value", &isPlayer);
							}
						}
					}
				}
			}
			pGameObject->load(new LoaderParams(x, y, width, height, textureID, callbackID, numFrames, animSpeed, pCollisionLayers));
			pObjectLayer->getGameObjects()->push_back(pGameObject);
			
			if (isPlayer)
			{
				if (dynamic_cast<FelipPuig*>(pGameObject))
				{
					Player = dynamic_cast<FelipPuig*>(pGameObject);
					pLevel->setPlayer(Player);
				}
			}
		}
	}
	pLayers->push_back(pObjectLayer);
	pObjectLayers->push_back(pObjectLayer);
}