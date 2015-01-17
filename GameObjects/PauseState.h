#ifndef __PAUSE_STATE__
#define __PAUSE_STATE__

typedef void(*Callbacks)();

#include "GameState.h"

class PauseState : public GameState
{
public:
	void update();
	void render();
	bool onEnter();
	bool onExit();

	virtual string getStateID() const { return s_menuID; }

	static const string s_menuID;
	std::vector<GameObject *> m_gameObjects;
	std::vector<std::string> m_TextureIDs;
	std::vector<void(*)()> m_callbacks;
	virtual void setCallbacks();
private:
	static void s_resume();
	static void s_returnMainMenu();

};


#endif
