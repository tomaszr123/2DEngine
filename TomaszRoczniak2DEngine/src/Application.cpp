
#include <stdio.h>
#include <stdlib.h>
#include "Application.h"
#include <assert.h>
#include "CTexture.h"
#include "CSpritebatch.h"
#include "CFontManager.h"

void APIENTRY glErrorCallback(GLenum source,
	GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message,
	GLvoid* userParam)
{
	(void)source;
	(void)type;
	(void)id;
	(void)severity;
	(void)length;
	(void)userParam;

	printf((std::string(message) + std::string("\n\n")).c_str());
}

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
}
Application::~Application()
{
	delete m_texture;
	delete m_spriteBatch;

	m_texture		= nullptr;
	m_spriteBatch	= nullptr;
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

	glewExperimental = true;
	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	// Setup OpenGL error callbacks if supported
	if (glewIsSupported("GL_ARB_debug_output"))
	{
		glDebugMessageCallbackARB(glErrorCallback, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
	}
	else
	{
		printf("OpenGL error callbacks are not supported");
	}

	const char* fontName = "./arial.png";
	const char* xmlName = "./arial.xml";

	m_font = new CFontManager();
	m_texture = new CTexture();
	m_spriteBatch = new CSpritebatch(m_uiWindowWidth, m_uiWinidowHeight);
	m_spriteBatch->Begin();

	// sets the colour for the screen
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	//Enable some Blending.
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable(GL_CULL_FACE);

	return true;
}
// closes th window and shuts down the full framework 
void Application::Shutdown()
{
	m_spriteBatch->End();
	glfwCloseWindow();
	glfwTerminate();
	
	delete m_font;
	m_font = nullptr;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float Application::GetDeltaTime()
{
	float lastTime = 0.0;

	gametime.elapsedGameTime = glfwGetTime();
	gametime.DeltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();

	return gametime.DeltaTime;
}
// Create and Draw a Texture to the screen also Destroy a Texture functions
unsigned int Application::CreateTexture(const char *filename)
{
	return m_texture->CreateTexture(filename);
}

void Application::DestroyTexture(unsigned int textureID)
{
	m_texture->DestroyTexture(textureID);
}

void Application::DrawTexture(unsigned int textureID, float xPos, float yPos, float width /*= 0*/, float height /*= 0*/, float rotation /*= 0*/, float xOrigin /*= 0.5f*/, float yOrigin /*= 0.5f*/)
{
	m_spriteBatch->DrawTexture(textureID, xPos, yPos, width, height, rotation, xOrigin, yOrigin);
}

// Create, Draw and Destroy a Font Function
void Application::CreateFont()
{
	m_font->LoadFont("arial.png", "arial.xml");
}
void Application::DestroyFont(unsigned int fontID)
{
	//m_font->DestroyFont(fontID);
}

void Application::DrawFont(const char* text, float xPos, float yPos, float size)
{
	m_font->DrawString(text, xPos, yPos, size);
}