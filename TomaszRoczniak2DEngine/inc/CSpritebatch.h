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
#include <glm.hpp>
#include <gl\glew.h>
#include <gl\glfw.h>
#include <ext.hpp>

class CTexture;

class FRAMEWORK2D CSpritebatch
{
public:
	CSpritebatch(unsigned int windowwidth, unsigned int windowheight);
	~CSpritebatch();

	void DrawTexture(unsigned int textureID, float xPos, float yPos, float width = 0, float height = 0, float rotation = 0, float xOrigin = 0.5f, float yOrigin = 0.5f);
	void InitShader();

private:

	// this function is to load the shaders in for all the textures
	unsigned int LoadShader(const char *filename, unsigned int type);
	unsigned char* fileToBuffer(const char* sPath);
	unsigned int CreateProgram(unsigned int a_vertexShader, unsigned int a_geometryShader, unsigned int a_fragmentShader,
								  unsigned int a_inputAttributeCount  = 0 , const char** a_inputAttributes = nullptr,
								  unsigned int a_outputAttributeCount = 0 , const char** a_outputAttributes = nullptr );

	// this function is to draw the shader 
	void DrawShader();

	glm::vec2 TransformPoint(const glm::vec2 &vect) const;

	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	unsigned int m_uiProgramID;
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

	float m_vertex[4];
	unsigned short m_indices[6];

	glm::mat4 m_projection;

};
#endif