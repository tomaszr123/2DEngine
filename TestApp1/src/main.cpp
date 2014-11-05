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
		
	}

	DestroyTexture(texture);

	Shutdown();

	_CrtDumpMemoryLeaks();

	return 0;
}