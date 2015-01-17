#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <map>

using namespace std;

class TextureManager
{
private:
	TextureManager();
public:
	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
		}
		return s_pInstance;
	}
	~TextureManager();
	bool load(string fileName, string id, SDL_Renderer *SDLRenderer);
	void draw(string id, int x, int y, int width, int height, SDL_Renderer* pRender, SDL_RendererFlip flip);
	void drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRender, SDL_RendererFlip flip);
	void clearFromTextureMap(string id);
	map<string, SDL_Texture *> m_textureMap;
	void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
private:
	static TextureManager* s_pInstance;

};

#endif

