////////////////////////////////////////////////////////////
//	Creator: Tomasz Roczniak
//	Date: 29-10-2014
//	Description:This class is for the main section of the 
//				framework and this is were the window is created
//				and it is updated and the drawing happens
////////////////////////////////////////////////////////////

#ifndef APPLICATION_H_
#define APPLICATION_H_

#ifndef FRAMEWORK2D_EXPORT
#define FRAMEWORK2D __declspec(dllexport)
#else 
#define FRAMEWORK2D __declspec(dllexport)
#endif

#include <gl\glew.h>
#include <gl\glfw.h>
#include "Framework.h"

class CTexture;
class CSpritebatch;

class FRAMEWORK2D Application
{
public:
	// a struct for delta time and game time 
	struct SGameTime
	{
	public:
		float DeltaTime;
		float elapsedGameTime;
	}gametime;

	// singleton functions
	//--------------------------
	static void CreateSingleton();
	static void DestroySingleton();
	static Application *GetInstance();
	//--------------------------

	// Update function for the framework and clearscreen so then the back buffer is clean for each frame
	bool FrameworkUpdate();
	void ClearScreen();

	// this function will init the application
	bool InitialseWindow(unsigned int a_uiWindowWidth, unsigned int a_uiWindowHeight, bool a_bFullScreen);

	// this is for the application to close
	void Shutdown();

	// this is to enable vsync for the monitor
	void EnableVSync(bool a_bEnabled);

	// gets the windows width and height
	unsigned int GetWindowWidth();
	unsigned int GetWindowHeight();

	// returns the time that has passed
	float GetDeltaTime();

	// Creates the texture
	unsigned int CreateTexture(const char *filename);
	void DestroyTexture(unsigned int textureID);
	// Draws a Texture to the screen 
	void DrawTexture(unsigned int textureID, float xPos, float yPos, float width = 0, float height = 0, float rotation = 0, float xOrigin = 0.5f, float yOrigin = 0.5f);

	// Creates a Font and Destroys a Font
	unsigned int CreateFont();
	void DestroyFont(unsigned int fontID);
	// Draws the font to the screen
	void DrawFont(const char* text, float xPos, float yPos, float size);

private:

	// singleton ptr;
	static Application *ms_singleton;

private:

	// Constructor / Destructors private for singleton
	Application();
	~Application();

	// these are for the window width and the window height 
	unsigned int m_uiWindowWidth;
	unsigned int m_uiWinidowHeight;

	// this is to check if the framework is closed or not 
	bool m_bFrameworkClosed;

	// a bool to check if it is full screen or not 
	bool m_bFullScreen;
	// a bool  for vsync
	bool m_bVSyncEnabled;

	// Pointers to the classes that have been created so then everything works 
	CTexture *m_texture;
	CSpritebatch* m_spriteBatch;
};
////////////////////////////////////////////////////////////
#endif // APPLICATION_H_
////////////////////////////////////////////////////////////