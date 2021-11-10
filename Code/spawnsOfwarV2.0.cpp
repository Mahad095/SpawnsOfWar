#include"game.h"
#include<windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	game& Game = game::get();
	while (Game.running())
	{
		//update
		Game.update();

		//render

		Game.render();
	}
	return 0;
}