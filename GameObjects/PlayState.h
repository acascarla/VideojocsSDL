#ifndef __PLAY_STATE__
#define __PLAY_STATE__


typedef void(*Callbacks)();

#include "GameState.h"
#include "GameObject.h"
#include "FelipPuig.h"
#include "Cranc.h"
#include "Cargol.h"
#include "Level.h"

class PlayState : public GameState
{
public:
	void update();
	void render();
	bool onEnter();
	bool onExit();
	virtual string getStateID() const { return s_menuID; }
private:
	static const string s_menuID;

	std::vector<GameObject *> m_gameObjects;
	std::vector<std::string> m_TextureIDs;
	std::vector<void(*)()> m_callbacks;
	virtual void setCallbacks();
	static void s_pause();

	Level* pLevel;
};


#endif
