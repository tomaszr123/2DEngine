#include "Framework.h"
#include <iostream>
#include <crtdbg.h>

unsigned int texture;


int main(int argc, char **argv)
{
	Initialise(800, 600, false);

	texture = CreateTexture("./crate_sideup.png");
	while(FrameworkUpdate())
	{
		ClearScreen();

		DrawTexture(texture, 10, 10, 32, 32);
	}

	DestroyTexture(texture);

	Shutdown();

	_CrtDumpMemoryLeaks();

	return 0;
}