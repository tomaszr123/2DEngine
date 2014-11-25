#include "Framework.h"
#include <iostream>

unsigned int texture;
unsigned int font;

int main(int argc, char **argv)
{
	Initialise(800, 750, false);

	texture = CreateTexture("crate_sideup.png");
	font = CreateFont("Arcade.ttf", 32);
	while(FrameworkUpdate())
	{
		ClearScreen();

		DrawString(font, "This works fine i hope", 550, 550);
		DrawTexture(texture, 100, 100, 128, 128);
	}

	DestroyTexture(texture);

	Shutdown();

	return 0;
}