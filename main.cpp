#include "display.h"
#include "game.h"

#include <iostream>

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;
static const char* TITLE_NAME = "Alpha32.exe";

int main(int argc, char* argv[])
{
	Display display(TITLE_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (!display.init())
	{
		std::cout << "Could not initialize display!\nStopping...." << std::endl;
		return -1;
	}

	Game game(WINDOW_WIDTH, WINDOW_HEIGHT);

	if (!game.init())
	{
		std::cout << "Game could not start!\nStopping..." << std::endl;
		return -1;
	}

	while (display.isRunning())
	{
		game.update();

		display.clear();
		game.render();
		
		display.update();
	}

	return 0;
}