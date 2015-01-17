#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for (map < string, SDL_Texture* >::const_iterator itr = m_textureMap.begin();
		itr != m_textureMap.end();
		itr++)
	{
		SDL_Texture * pTextureTemp = itr->second;
		SDL_DestroyTexture(pTextureTemp);
	}
	m_textureMap.clear();
}

bool TextureManager::load(string fileName, string id, SDL_Renderer *SDLRenderer)
{
	string name_concat = "../assets/" + fileName;

	SDL_Surface* SDLSurface = IMG_Load(name_concat.c_str());
	if (!SDLSurface) {
		cout << "IMG_Load: %s\n", IMG_GetError();
	}
	// 2. convertir Surface 2 Texture
	SDL_Texture* SDLTexture = SDL_CreateTextureFromSurface(SDLRenderer, SDLSurface);

	// 3. alliberar la Surface
	SDL_FreeSurface(SDLSurface);

	// 4. afegir la textura al map
	if (SDLTexture != 0)
	{
		m_textureMap[id] = SDLTexture;
		return true;
	}
	
	return false;
}

void TextureManager::draw(string id, int x, int y, int width, int height, SDL_Renderer* pRender, SDL_RendererFlip flip ){

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopyEx(pRender, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = width;
	srcRect.h = height;
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
		&destRect, 0, 0, SDL_FLIP_NONE);
}



void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}