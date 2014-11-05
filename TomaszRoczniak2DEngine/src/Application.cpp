
#include <stdio.h>
#include <stdlib.h>
#include "Application.h"
#include <assert.h>
#include "CTexture.h"

// initialise static variables
Application * Application::ms_singleton = nullptr;

void Application::CreateSingleton()
{
	ms_singleton = new Application();
}
void Application::DestroySingleton()
{
	delete ms_singleton;
	ms_singleton = nullptr;
}
Application *Application::GetInstance()
{
	assert( ms_singleton && "Application be Created First - use CreateSingleton(...)");
	return ms_singleton;
}

Application::Application()
{
	m_uiWindowWidth = 800;
	m_uiWinidowHeight = 600;
	m_bFullScreen = false;
	m_bFrameworkClosed = false;
	m_bVSyncEnabled = false;

	m_texture = new CTexture();
}
Application::~Application()
{
	delete m_texture;
	m_texture = nullptr;
}
bool Application::InitialseWindow(unsigned int a_uiWindowWidth, unsigned int a_uiWindowHeight, bool a_bFullScreen /*= false*/)
{
	m_uiWindowWidth		= a_uiWindowWidth;
	m_uiWinidowHeight	= a_uiWindowHeight;
	m_bFullScreen		= a_bFullScreen;

	if(!glfwInit())
	{
		return false;
	}

	// this creates the window to the size that was passed in and checks if full screen or not 
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
	glfwOpenWindow(m_uiWindowWidth, m_uiWinidowHeight, 8,8,8,8, 24, 8,(m_bFullScreen) ? GLFW_FULLSCREEN:GLFW_WINDOW);

	glfwDisable(GLFW_AUTO_POLL_EVENTS);

	glfwSetWindowTitle("Application");

	// enable / disable vSync
	EnableVSync(m_bVSyncEnabled);

	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}
	
	// sets the colour for the screen
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	// this framework will only be used in orthographic projection
	// we will set this up only to use that view
	// this means everything will be done 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, m_uiWindowWidth, m_uiWinidowHeight, 0.0f, 0.0f, 100.0f);

	//Enable some Blending.
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// enable for 3D rendering, not needed for 2D rendering
	//		glEnable(GL_DEPTH);
	//		glDepthFunc(GL_LEQUAL);

	return true;
}
// closes th window and shuts down the full framework 
void Application::Shutdown()
{
	glfwCloseWindow();
	glfwTerminate();
}

void Application::EnableVSync(bool a_bEnabled)
{
	m_bVSyncEnabled = a_bEnabled;
	glfwSwapInterval( (m_bVSyncEnabled)?0:1 );

}
// gets the window width
unsigned int Application::GetWindowWidth()
{
	return m_uiWindowWidth;
}
// gets the window height
unsigned int Application::GetWindowHeight()
{
	return m_uiWinidowHeight;
}
// framework update and checks if its still running or been closed
bool Application::FrameworkUpdate()
{
	glfwSwapBuffers();
    glfwPollEvents();


	m_bFrameworkClosed = glfwGetWindowParam( GLFW_OPENED );

	return m_bFrameworkClosed;
}
// clears the back buffer
void Application::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

float Application::GetDeltaTime()
{
	float lastTime = 0.0;

	gametime.elapsedGameTime = glfwGetTime();
	gametime.DeltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();

	return gametime.DeltaTime;
}

unsigned int Application::CreateTexture(const char *filename)
{
	return m_texture->CreateTexture(filename);
}

void Application::DestroyTexture(unsigned int textureID)
{
	m_texture->DestroyTexture(textureID);
}