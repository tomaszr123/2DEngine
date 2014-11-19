
#include "CSpritebatch.h"
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

const char * gs_vertexShader =
" \
#version 330 \r\n\
in vec3 position; \
in vec2 texCoords; \
\
uniform mat4 projectionView; \
\
out vec2 textureCoords; \
\
void main() \
{\
	textureCoords	= texCoords; \
	gl_Position     = projectionView * vec4(position.x, position.y, 0.0f, 1.0); \
} \
";


const char * gs_fragmentShader = 
"\
#version 330 \r\n\
\
in vec2 textureCoords; \
\
uniform sampler2D	diffuseMap; \
\
void main() \
{ \
    vec4 color = texture2D(diffuseMap, textureCoords); \
	\
}";

CSpritebatch::CSpritebatch(unsigned int windowwidth, unsigned int windowheight)
{
	
	// init the vbo vao and ibo to 0
	m_vao = 0;
	m_ibo = 0; 
	m_vbo = 0;

	m_activeBuffer = 0;

	// creating the corce rect from the init 
	m_sorcRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// load the shader with alll the inputs
	const char* aszInputs[] = {"position", "texCoords"};

	// load shader internally call gl create shader
	unsigned int vertexShader	= LoadShader(gs_vertexShader, GL_VERTEX_SHADER);
	unsigned int fragShader		= LoadShader(gs_fragmentShader, GL_FRAGMENT_SHADER);

	// creating the shader program and giving it what it needs
	m_uiProgramID = CreateProgram(vertexShader, 0, fragShader, 2, aszInputs);

	// deleting the shaders as it is already stored
	glDeleteShader(vertexShader); glDeleteShader(fragShader);

	glUseProgram(m_uiProgramID);

	if(m_uiProgramID == NULL)
	{
		printf("Error: There is no program created! \n");
		return;
	}

	// create the vao vbo and ibo buffers
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	// set the projection to ortho and pass the wid and hight to the view
	m_projection = glm::ortho<float>(0.0f, windowwidth, windowheight, 0.0f);
}

CSpritebatch::~CSpritebatch()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_vao);
	glDeleteBuffers(1, &m_ibo);

	glDeleteProgram(m_uiProgramID);
}

void CSpritebatch::Begin()
{
	m_activeBuffer	= 0;
	m_currentIndex      = 0;
	m_currentVert       = 0;

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_uiProgramID);

	glUniformMatrix4fv(glGetUniformLocation(m_uiProgramID, "projectionView"), 1, false, glm::value_ptr(m_projection));
}

void CSpritebatch::End()
{
	glUseProgram(0);
}

void CSpritebatch::DrawTexture(unsigned int textureID, float xPos, float yPos, float width /*= 0*/, float height /*= 0*/, float rotation /*= 0*/, float xOrigin /*= 0.5f*/, float yOrigin /*= 0.5f*/)
{
	if(textureID == -1) return;

	// making the single floats into vector 2
	glm::vec2 position;
	glm::vec2 origin;
	glm::vec2 size;

	position.x	= xPos;		position.y	= yPos;
	origin.x	= xOrigin;	origin.y	= yOrigin;
	size.x		= width;	size.y		= height;

	glm::vec2 tl(0.0f,0.0f);
	glm::vec2 tr(1.0f,0.0f);
	glm::vec2 br(1.0f,1.0f);
	glm::vec2 bl(0.0f,1.0f);

	tl = RotateAround( (tl *size) - (size * origin), rotation) + position;
	tr = RotateAround( (tr *size) - (size * origin), rotation) + position;
	br = RotateAround( (br *size) - (size * origin), rotation) + position;
	bl = RotateAround( (bl *size) - (size * origin), rotation) + position;

	int index = m_currentVert;

	m_vertex[m_currentVert++] = SBVertex(tl, glm::vec2(m_sorcRect.x, m_sorcRect.y), textureID);
	m_vertex[m_currentVert++] = SBVertex(tr, glm::vec2(m_sorcRect.x + m_sorcRect.z, m_sorcRect.y), textureID);
	m_vertex[m_currentVert++] = SBVertex(br, glm::vec2(m_sorcRect.x + m_sorcRect.z, m_sorcRect.y + m_sorcRect.w), textureID);
	m_vertex[m_currentVert++] = SBVertex(bl, glm::vec2(m_sorcRect.x, m_sorcRect.y + m_sorcRect.w), textureID);

	m_indices[m_currentIndex++] = (index + 0);
	m_indices[m_currentIndex++] = (index + 2);
	m_indices[m_currentIndex++] = (index + 3);

	m_indices[m_currentIndex++] = (index + 0);
	m_indices[m_currentIndex++] = (index + 1);
	m_indices[m_currentIndex++] = (index + 2);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER, m_currentVert * sizeof(SBVertex), m_vertex, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_currentIndex * sizeof(unsigned short), m_indices, GL_STATIC_DRAW);
          
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
          
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SBVertex), (char *)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SBVertex), (char *)12);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SBVertex), (char *)28);

    glDrawElements(GL_TRIANGLES, m_currentIndex, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);

	m_currentIndex = 0;
    m_currentVert = 0;
}
glm::vec2 CSpritebatch::RotateAround(glm::vec2 Position, float rotation)
{
    glm::vec2 newPos = glm::vec2();
		
	newPos.x = Position.x * (float)cos(rotation) - Position.y * (float)sin(rotation);
	newPos.y = Position.x * (float)sin(rotation) + Position.y * (float)cos(rotation);

	return newPos;
}

// creates a shader program, links the specified shader stages to it, and binds the specified input/output attributes
unsigned int CSpritebatch::CreateProgram(unsigned int a_vertexShader, unsigned int a_geometryShader, unsigned int a_fragmentShader,
								  unsigned int a_inputAttributeCount /* = 0 */, const char** a_inputAttributes /* = nullptr */,
								  unsigned int a_outputAttributeCount /* = 0 */, const char** a_outputAttributes /* = nullptr */)
{
	int success = GL_FALSE;

	// create a shader program and attach the shaders to it
	unsigned int handle = glCreateProgram();
	glAttachShader(handle, a_vertexShader);
	glAttachShader(handle, a_geometryShader);
	glAttachShader(handle, a_fragmentShader);

	// specify vertex input attributes
	for ( unsigned int i = 0 ; i < a_inputAttributeCount ; ++i )
		glBindAttribLocation(handle, i, a_inputAttributes[i]);

	// specify fragment shader outputs
	for ( unsigned int i = 0 ; i < a_outputAttributeCount ; ++i )
		glBindFragDataLocation(handle, i, a_outputAttributes[i]);

	// link the program together and log errors
	glLinkProgram(handle);

	glGetProgramiv(handle, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;		
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(handle, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s",infoLog);
		printf("\n");
		delete[] infoLog;
		return 0;
	}

	return handle;
}

unsigned int CSpritebatch::LoadShader(const char *filename, unsigned int type)
{
	int success = GL_FALSE;

	unsigned int handle = glCreateShader(type);

	glShaderSource(handle, 1, &filename, 0);
	glCompileShader(handle);

	glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(handle, infoLogLength, 0, infoLog);
		printf("Error: Failed to compile shader! \n");
		printf("%s", infoLog);
		printf("\n");
		delete[] infoLog;
		return 0;
	}
	return handle;
}

unsigned char* CSpritebatch::fileToBuffer(const char* sPath)
{
	// open the file for text reading
	FILE* pFile = fopen(sPath,"rb");
	if(pFile == nullptr)
	{
		printf("Error: Unable to open file ' %s ' for reading! \n", sPath);
		return nullptr;
	}
	// gets the number of byts in the file
	fseek(pFile, 0, SEEK_END);
	unsigned int uiLength = (unsigned int)ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	// allocate buffer and read file contents
	unsigned char* acBuffer = new unsigned char[uiLength + 1];
	memset(acBuffer,0,uiLength +1);
	fread(acBuffer, sizeof(unsigned int), uiLength, pFile);

	fclose(pFile);
	return acBuffer;
}