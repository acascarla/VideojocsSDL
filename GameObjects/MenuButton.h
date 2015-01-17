#ifndef __MENU_BUTTON__
#define __MENU_BUTTON__

#include "GameObject.h"
#include "LoaderParams.h"

class MenuButton : public GameObject
{
public:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};
	MenuButton(int x, int y, int width, int height, string textureID, void(*callback)());
	MenuButton(void(*callback)());
	MenuButton();
	virtual ~MenuButton() {};
	virtual void load(LoaderParams *loadParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	static GameObject * Create() { return new MenuButton(); }
	void setCallback(void(*callback)()) { m_callback = callback; }
	int getCallbackID() { return m_callbackID; }
	virtual string type() { return s_gameObjectID; }
	virtual void onCollision(GameObject* other) {};


protected:
	void(*m_callback)();
	bool m_bReleased;
};

#endif