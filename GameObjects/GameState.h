#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <vector>
#include "GameObject.h"

using namespace std;

class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual string getStateID() const = 0;
};

#endif