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

#include <glm.hpp>
#include <ext.hpp>
#include <gl\glew.h>
#include <gl\glfw.h>


class CTexture;
class CFont;

class FRAMEWORK2D CSpritebatch
{
public:
	CSpritebatch(unsigned int windowwidth, unsigned int windowheight);
	~CSpritebatch();

	void DrawTexture(unsigned int textureID, float xPos, float yPos, float width = 0, float height = 0, float rotation = 0, float xOrigin = 0.5f, float yOrigin = 0.5f);
	void Begin();
	void End();

	//// Draw a string 
	//void DrawString(CFont* font, unsigned int fontID, const char* text, float xPos, float yPos);
private:

	// this function is to load the shaders in for all the textures
	unsigned int LoadShader(const char *filename, unsigned int type);
	unsigned int CreateProgram(unsigned int a_vertexShader, unsigned int a_geometryShader, unsigned int a_fragmentShader,
								  unsigned int a_inputAttributeCount  = 0 , const char** a_inputAttributes = nullptr,
								  unsigned int a_outputAttributeCount = 0 , const char** a_outputAttributes = nullptr );



	// doing a calculation for rotating the sprite
	glm::vec2 RotateAround(glm::vec2 Position, float rotation);

	glm::vec4 m_sorcRect;

	unsigned int m_activeBuffer;

protected:

	// a struct for all the vertex and index
	struct SBVertex
	{
		SBVertex() : pos(), texcoord(){}
		SBVertex(const glm::vec2 &a_pos, const glm::vec2 &a_texcoord) : pos(a_pos), texcoord(a_texcoord)
		{
		
		}
		glm::vec2 pos;
		glm::vec2 texcoord;
	};

	SBVertex m_vertex[4];
	unsigned short m_indices[6];

	int m_currentVert;
    int m_currentIndex;

	unsigned int m_uiProgramID;
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	
	glm::mat4 m_projection;

};
#endif