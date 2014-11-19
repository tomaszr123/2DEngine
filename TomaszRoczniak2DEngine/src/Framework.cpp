#include "Framework.h"
#include <iostream>
#include "Application.h"


int Initialise(int a_iWindowWidth, int a_iWindowHeight, bool a_bFullScreen /*= false*/, const char* a_pWWindowTiltle /*= nullptr*/)
{
	Application::CreateSingleton();
	return Application::GetInstance()->InitialseWindow(a_iWindowWidth, a_iWindowHeight, a_bFullScreen);
}
// closes the application
void Shutdown()
{
	Application::GetInstance()->Shutdown();
}
// checks if the framework is closed or not 
bool FrameworkUpdate()
{
	return Application::GetInstance()->FrameworkUpdate();
}
// clears the screens 
void ClearScreen()
{
	Application::GetInstance()->ClearScreen();
}
// Create your texture so then you can point draw it later
unsigned int CreateTexture(const char *filename)
{
	return Application::GetInstance()->CreateTexture(filename);
}
void DestroyTexture(unsigned int textureID)
{
	Application::GetInstance()->DestroyTexture(textureID);
}
void DrawTexture(unsigned int textureID, float xPos, float yPos, float width /*= 0*/, float height /*= 0*/, 
				 float rotation /*= 0*/, float xOrigin /*= 0.5f*/, float yOrigin /*= 0.5f*/)
{
	Application::GetInstance()->DrawTexture(textureID, xPos, yPos, width, height, rotation, xOrigin, yOrigin);
}

// checks if a key is down or not 
bool IsKeyDown(int a_key)
{
	return true;
}
// gets the deltaTime that has passed
float GetDeltaTime()
{
	return Application::GetInstance()->GetDeltaTime();
}