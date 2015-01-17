#ifndef __CRANC_H__
#define __CRANC_H__

#include "PlataformerObject.h"
class Cranc : public PlataformerObject
{
public:
	Cranc();
	void update();
	void clean();
	static GameObject * Create() { return new Cranc(); }
	virtual string type() { return s_gameObjectID; }
	virtual void onCollision(GameObject* other) {};
};

#endif