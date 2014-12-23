#include "Framework.h"
#include <iostream>

unsigned int texture;


int main(int argc, char **argv)
{
	Initialise(800, 750, false);

	texture = CreateTexture("crate_sideup.png");
	CreateFont();
	while(FrameworkUpdate())
	{
		ClearScreen();

   		DrawString("This works fine i hope", 550, 550, 16);
		DrawTexture(texture, 100, 100, 128, 128);
	}

	DestroyTexture(texture);

	Shutdown();

	return 0;
}