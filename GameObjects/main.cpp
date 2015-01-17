#include "Game.h"
#include "tinyxml.h"
#include "base64.h"
#include "zlib.h"



using namespace std;

int main(int argc, char* args[])
{
	
	int frameStart;
	int frameEnd;
	int frameTime;
	int FIXED_TIME = 20; // Cada loop per segon seran 20 ms, que * 50 = 1000ms (50fps)
	Game::Instance()->init("Game", 30, 30, 800, 600, false);

	while (Game::Instance()->isRunning())
	{
		frameStart = SDL_GetTicks();

		Game::Instance()->handleEvents();
		Game::Instance()->update();
		Game::Instance()->render();
		
		frameEnd = SDL_GetTicks();
		frameTime = frameEnd - frameStart;
		if(frameTime < FIXED_TIME)
		{
			SDL_Delay((int)(FIXED_TIME - frameTime));
		}
	}
	
	Game::Instance()->clean();
	return 0;
	
}