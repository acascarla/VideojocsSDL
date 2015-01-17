#ifndef __FELIP_PUIG_H__
#define __FELIP_PUIG_H__

#include "PlataformerObject.h"

class FelipPuig : public PlataformerObject{
public:
	FelipPuig();
	void update();
	void clean();
	void jump();
	void moveRight();
	void moveLeft();
	void increaseJump();
	void applyGravity();
	static GameObject * Create() { return new FelipPuig(); }
	virtual string type() { return s_gameObjectID; }
	virtual void onCollision(GameObject* other);
private:
	bool m_isJumping;
	bool m_canJump;
	float m_jumpForce;
	int m_jumpHeight;
	float m_initJumpHeight;
	float m_endJumpHeight;
	bool m_isFacingRight;
};

#endif