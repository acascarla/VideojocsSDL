#pragma once

#include <iostream>
#include "TileLayer.h"

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID, int callbackID, int numFrames, float velocitat) :
		m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_callbackID(callbackID), m_numFrames(numFrames), m_velocitat(velocitat) {}
	LoaderParams(int x, int y, int width, int height, std::string textureID, int callbackID, int numFrames, float velocitat, vector< TileLayer* >* collisionLayers) :
		m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_callbackID(callbackID), m_numFrames(numFrames), m_velocitat(velocitat), m_collisionLayers(collisionLayers) {}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
	int getCallbackID() const { return m_callbackID; }
	int getNumFrames() const { return m_numFrames; }
	float getVelocitat() const { return m_velocitat; }
	vector< TileLayer* >* getCollisionLayers() const { return m_collisionLayers; }
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	std::string m_textureID;
	int m_callbackID;
	int m_numFrames;
	float m_velocitat;
	vector< TileLayer* >* m_collisionLayers;
};