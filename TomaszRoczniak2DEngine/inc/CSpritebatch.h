////////////////////////////////////////////////////////////
//	Creator: Tomasz Roczniak
//	Date: 5-11-2014
//	Description:This class is so you can Draw the textures to 
//				 the screen and it will be using shaders.
////////////////////////////////////////////////////////////


#ifndef CSPRITEBATCH_H_
#define CSPRITEBATCH_H_

#ifndef FRAMEWORK2D_EXPORT
#define FRAMEWORK2D __declspec(dllexport)
#else 
#define FRAMEWORK2D __declspec(dllexport)
#endif

#include <iostream>
#include <gl\glew.h>
#include <gl\glfw.h>

class FRAMEWORK2D CSpritebatch
{
public:
	CSpritebatch();
	~CSpritebatch();

	void DrawTexture(unsigned int textureID, float xPos, float yPos, float width = 0, float height = 0, float rotation = 0, float xOrigin = 0.5f, float yOrigin = 0.5f);


private:

	void DrawShader();

};
#endif