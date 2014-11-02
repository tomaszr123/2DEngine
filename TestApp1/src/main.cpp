#include "Framework.h"
#include <iostream>
int main(int argc, char **argv)
{
	Initialise(800, 600, false);

	while(FrameworkUpdate())
	{
		ClearScreen();
		std::cout << "time passed /f \n" << GetDeltaTime() << std::endl;

		// blah blah blah just checking if this works 
	}
	Shutdown();

	return 0;
}