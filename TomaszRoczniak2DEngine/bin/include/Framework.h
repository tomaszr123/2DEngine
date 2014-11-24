////////////////////////////////////////////////////////////
//	Creator: Tomasz Roczniak
//	Date: 29-10-2014
//	Description: this is just a wrapper for the framework 
//				 so then you can call function
//				 Tomasz Roczniak Static OpenGL Framework
////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//	this is just a very Basic framework and you would most 
//	likely want to start looking at OpenGL and how to create
//	own one once you have an understanding of how to code
////////////////////////////////////////////////////////////


#ifndef FRAMEWORK_H_
#define FRAMEWORK_H_

#define FRAMEWORK2D __declspec(dllexport)

// KeyBoard and Mouse Button Input //////////////////////////
typedef enum
{
	MOUSE_BUTTON_1 = 0,
	MOUSE_BUTTON_2 = 1,
	MOUSE_BUTTON_3 = 2,
	KEY_SPACE	   = 32,
	KEY_SPECIAL	   = 256,
	KEY_ESC        = (KEY_SPECIAL+1),
	KEY_F1         = (KEY_SPECIAL+2),
	KEY_F2         = (KEY_SPECIAL+3),
	KEY_F3         = (KEY_SPECIAL+4),
	KEY_F4         = (KEY_SPECIAL+5),
	KEY_F5         = (KEY_SPECIAL+6),
	KEY_F6         = (KEY_SPECIAL+7),
	KEY_F7         = (KEY_SPECIAL+8),
	KEY_F8         = (KEY_SPECIAL+9),
	KEY_F9         = (KEY_SPECIAL+10),
	KEY_F10        = (KEY_SPECIAL+11),
	KEY_F11        = (KEY_SPECIAL+12),
	KEY_F12        = (KEY_SPECIAL+13),
	KEY_F13        = (KEY_SPECIAL+14),
	KEY_F14        = (KEY_SPECIAL+15),
	KEY_F15        = (KEY_SPECIAL+16),
	KEY_F16        = (KEY_SPECIAL+17),
	KEY_F17        = (KEY_SPECIAL+18),
	KEY_F18        = (KEY_SPECIAL+19),
	KEY_F19        = (KEY_SPECIAL+20),
	KEY_F20        = (KEY_SPECIAL+21),
	KEY_F21        = (KEY_SPECIAL+22),
	KEY_F22        = (KEY_SPECIAL+23),
	KEY_F23        = (KEY_SPECIAL+24),
	KEY_F24        = (KEY_SPECIAL+25),
	KEY_F25        = (KEY_SPECIAL+26),
	KEY_UP         = (KEY_SPECIAL+27),
	KEY_DOWN       = (KEY_SPECIAL+28),
	KEY_LEFT       = (KEY_SPECIAL+29),
	KEY_RIGHT      = (KEY_SPECIAL+30),
	KEY_LSHIFT     = (KEY_SPECIAL+31),
	KEY_RSHIFT     = (KEY_SPECIAL+32),
	KEY_LCTRL      = (KEY_SPECIAL+33),
	KEY_RCTRL      = (KEY_SPECIAL+34),
	KEY_LALT       = (KEY_SPECIAL+35),
	KEY_RALT       = (KEY_SPECIAL+36),
	KEY_TAB        = (KEY_SPECIAL+37),
	KEY_ENTER      = (KEY_SPECIAL+38),
	KEY_BACKSPACE  = (KEY_SPECIAL+39),
	KEY_INSERT     = (KEY_SPECIAL+40),
	KEY_DEL        = (KEY_SPECIAL+41),
	KEY_PAGEUP     = (KEY_SPECIAL+42),
	KEY_PAGEDOWN   = (KEY_SPECIAL+43),
	KEY_HOME       = (KEY_SPECIAL+44),
	KEY_END        = (KEY_SPECIAL+45),
	KEY_KP_0       = (KEY_SPECIAL+46),
	KEY_KP_1       = (KEY_SPECIAL+47),
	KEY_KP_2       = (KEY_SPECIAL+48),
	KEY_KP_3       = (KEY_SPECIAL+49),
	KEY_KP_4       = (KEY_SPECIAL+50),
	KEY_KP_5       = (KEY_SPECIAL+51),
	KEY_KP_6       = (KEY_SPECIAL+52),
	KEY_KP_7       = (KEY_SPECIAL+53),
	KEY_KP_8       = (KEY_SPECIAL+54),
	KEY_KP_9       = (KEY_SPECIAL+55),
	KEY_KP_DIVIDE  = (KEY_SPECIAL+56),
	KEY_KP_MULTIPLY= (KEY_SPECIAL+57),
	KEY_KP_SUBTRACT= (KEY_SPECIAL+58),
	KEY_KP_ADD     = (KEY_SPECIAL+59),
	KEY_KP_DECIMAL = (KEY_SPECIAL+60),
	KEY_KP_EQUAL   = (KEY_SPECIAL+61),
	KEY_KP_ENTER   = (KEY_SPECIAL+62),
	KEY_KP_NUM_LOCK= (KEY_SPECIAL+63),
	KEY_CAPS_LOCK  = (KEY_SPECIAL+64),
	KEY_SCROLL_LOCK= (KEY_SPECIAL+65),
	KEY_PAUSE      = (KEY_SPECIAL+66),
	KEY_LSUPER     = (KEY_SPECIAL+67),
	KEY_RSUPER     = (KEY_SPECIAL+68),
	KEY_MENU       = (KEY_SPECIAL+69),
	KEY_LAST       = KEY_MENU
};
///////////////////////////////////////////////////////////
//	Call this function to Initialise the Framework and for 
//	it to create a window
///////////////////////////////////////////////////////////
FRAMEWORK2D int		Initialise(int a_iWidth, int a_iHeight, bool a_bFullScreen = false, const char* a_pWWindowTiltle = nullptr);
///////////////////////////////////////////////////////////
//	This function is called at the end when you close the framework
///////////////////////////////////////////////////////////
FRAMEWORK2D void	Shutdown();
///////////////////////////////////////////////////////////
//	this function is updated once every frame
///////////////////////////////////////////////////////////
FRAMEWORK2D bool	FrameworkUpdate();
///////////////////////////////////////////////////////////
//	this function clears the frame from the previouse frame
///////////////////////////////////////////////////////////
FRAMEWORK2D void	ClearScreen();
///////////////////////////////////////////////////////////
//	Basic Sprite Creation 
///////////////////////////////////////////////////////////
FRAMEWORK2D unsigned int CreateTexture(const char *filename);
FRAMEWORK2D void DestroyTexture(unsigned int textureID);
FRAMEWORK2D void DrawTexture(unsigned int textureID, float xPos, float yPos, float width = 0, float height = 0, float rotation = 0, float xOrigin = 0.5f, float yOrigin = 0.5f);
///////////////////////////////////////////////////////////
//	Draw a Basic String to the screen using a font
///////////////////////////////////////////////////////////
FRAMEWORK2D unsigned int CreateFont(const char *filename, unsigned int size);
FRAMEWORK2D void DestroyFont(unsigned int fontID);
FRAMEWORK2D void DrawString(unsigned int fontID, const char *text, float xPos, float yPos, float xOrigin = 0.0f, float yOrigin = 0.0f);
FRAMEWORK2D void MeasureString( unsigned int fontID, const char *text, float &outWidth, float outHeight);
//FRAMEWORK2D void DrawStringSpecial(unsigned int fontID, const char *text, float xPos, float yPos); // calculates tab and other special characters
///////////////////////////////////////////////////////////
//	Create a basic render texture
///////////////////////////////////////////////////////////
//FRAMEWORK2D unsigned int CreateRenderTexture(unsigned int width, unsigned int height);
//FRAMEWORK2D void DestroyRenderTexture(unsigned int renderTextureID);
//FRAMEWORK2D void SetRenderTexture( unsigned int renderTextureID );
///////////////////////////////////////////////////////////
//	Basic Line Drawing
///////////////////////////////////////////////////////////
FRAMEWORK2D void	DrawLine(int a_iStartX, int a_iStartY, int a_iEndX, int a_iEndY);
///////////////////////////////////////////////////////////
//	Handles Input from the Mouse or KeyBoard
///////////////////////////////////////////////////////////
FRAMEWORK2D bool	IsKeyDown(int a_iKeyID);
FRAMEWORK2D void	GetMouseLocation(int& a_iMouseX, int& a_iMouseY);
FRAMEWORK2D bool	GetMouseButtonDown(int a_iMouseButton);
///////////////////////////////////////////////////////////
//	Gets the Delta Time for the framework
///////////////////////////////////////////////////////////
FRAMEWORK2D float GetDeltaTime();
///////////////////////////////////////////////////////////
#endif // FRAMEWORK_H_
///////////////////////////////////////////////////////////