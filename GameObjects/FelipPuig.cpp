#include "FelipPuig.h"
#include "Game.h"

FelipPuig::FelipPuig(){
	m_isJumping = false;
	m_canJump = true;
	m_jumpForce = 9;
	m_jumpHeight = 120;
	m_initJumpHeight = 0;
	m_endJumpHeight = 0;
	m_isFacingRight = true;
	s_gameObjectID = "FelipPuig";
}

void FelipPuig::update()
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) && posicio.getX() <= 730){
		moveRight();
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A) && posicio.getX() >= 0){
		moveLeft();
	}
	else {
		if (m_currentRow == 1) m_currentFrame = 7;
	}

	// Check space
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && posicio.getX() >= -10){
		jump();
	}

	// Actualitzar estat del salt
	if (m_isJumping)
	{
		increaseJump();
	}
	else{
		// Aplicar Gravetat
		applyGravity();
	}
	// Actualizar Rect
	m_pBoundingBox.x = posicio.getX();
	m_pBoundingBox.y = posicio.getY();
	m_pBoundingBox.h = m_height;
	m_pBoundingBox.w = m_width;
}
void FelipPuig::clean()
{

}

void FelipPuig::moveRight()
{
	Vector2D newPos;
	newPos.setX(posicio.getX() + velocitat.getX());
	newPos.setY(posicio.getY());

	if (!PlataformerObject::checkCollideTile(newPos))
	{
		posicio.setX(posicio.getX() + velocitat.getX());
	}
	flip = SDL_FLIP_NONE;
	if (m_currentRow == 1) m_currentFrame = int(((SDL_GetTicks() / 100) % 8));
}
void FelipPuig::moveLeft()
{
	Vector2D newPos;
	newPos.setX(posicio.getX() - velocitat.getX());
	newPos.setY(posicio.getY());

	if (!PlataformerObject::checkCollideTile(newPos))
	{
		posicio.setX(posicio.getX() - velocitat.getX());
	}
	flip = SDL_FLIP_HORIZONTAL;
	if (m_currentRow == 1) m_currentFrame = int(((SDL_GetTicks() / 100) % 8));
}

void FelipPuig::jump()
{
	if (m_canJump)
	{
		m_initJumpHeight = posicio.getY();
		m_endJumpHeight = posicio.getY() - m_jumpHeight;
		m_isJumping = true;
		m_canJump = false;
		m_currentRow = 3;
		m_currentFrame = 1;
	}
}

void FelipPuig::increaseJump()
{
	Vector2D newPos;
	if (m_endJumpHeight <= posicio.getY())
	{
		newPos.setX(posicio.getX());
		newPos.setY(posicio.getY() - m_jumpForce);
		if (!PlataformerObject::checkCollideTile(newPos))
		{
			posicio.setY(newPos.getY());
			m_currentFrame = 0;
		}
	}
	else{
		m_isJumping = false;
	}
}

void FelipPuig::applyGravity()
{
	Vector2D newPos;
	newPos.setX(posicio.getX());
	newPos.setY(posicio.getY() + m_gravity);
	if (!PlataformerObject::checkCollideTile(newPos))
	{
		if (posicio.getY() + m_gravity < Game::Instance()->getGameHeight() - m_height)
		{
			posicio.setY(posicio.getY() + m_gravity);
		}
		else
		{
			flip = SDL_FLIP_VERTICAL;
		}
		m_canJump = false;
	}
	else{
		m_canJump = true; // si xoca amb el terra caient amb la gravetat podrà tornar a saltar
		m_currentRow = 1;
	}
}


void FelipPuig::onCollision(GameObject* go)
{
	string tipo = go->type();
	if (tipo == "Cargol")
	{
		flip = SDL_FLIP_VERTICAL;
	}
	if (tipo == "Cranc")
	{
		flip = SDL_FLIP_VERTICAL;
	}
}