#include "Framework.h"
#include <iostream>
#include "Application.h"


int Initialise(int a_iWindowWidth, int a_iWindowHeight, bool a_bFullScreen /*= false*/, const char* a_pWWindowTiltle /*= nullptr*/)
{
	//Application::InitialseWindow(a_iWindowWidth, a_iWindowHeight, a_bFullScreen);
	Application::CreateSingleton();
	return Application::GetInstance()->InitialseWindow(a_iWindowWidth, a_iWindowHeight, a_bFullScreen);
}

void Shutdown()
{
	Application::GetInstance()->Shutdown();
}

bool FrameworkUpdate()
{
	return Application::GetInstance()->FrameworkUpdate();
}

void ClearScreen()
{
	Application::GetInstance()->ClearScreen();
}

float GetDeltaTime()
{
	return Application::GetInstance()->GetDeltaTime();
}

bool IsKeyDown(int a_key)
{
	return true;
}